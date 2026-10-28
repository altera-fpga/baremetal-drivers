#!/bin/bash 

#################################################
# Internals
SELF=$(basename $0)
SELFPATH=$(dirname $0)

#################################################
# constants
CONST_1K=1024
CONST_1M=$((${CONST_1K} * ${CONST_1K}))
CONST_1G=$((${CONST_1M} * ${CONST_1K}))
CONST_RFS_TYPE=ext4

# partition table settings
# unit = bytes. adjustments to satisfy the partitioner tool done below

# let's make A2 boot partition size configurable
# CONST_PT_BOOT_SIZE removed
# CONST_PT_BOOT_OFFSET removed

CONST_PT_BOOT_TYPE=0xa2
# CONST_PT_BOOT_NUM=3

# 1/ Root file System partition, Type 83 = Linux EXT
CONST_PT_RFS_TYPE=0x83
# CONST_PT_RFS_NUM=2

# 2/ Parition for the kernel, Device tree, etc. 
CONST_PT_LX_TYPE=0x0b
# CONST_PT_LX_NUM=1

#################################################
# defaults
DEF_IMAGE_SIZE="2G"
DEF_IMAGE_NAME="image_blk_demo.bin"
DEF_RFS_TYPE=${CONST_RFS_TYPE}
DEF_DEBUG=0

#################################################
# functions
function usage() {
    echo "usage: ${SELF} [-h] [-k f1,f2] [[-p preloader |-rp preloader] -b bootloader] [-r <rfs_dir|rfs_tar> [-m merge_dir]] [-o image] [-g size] [-t tool]"
    echo "-k f1,f2,...   comma separated list of OS files  (i.e. zImage,dtb)"
    echo "-p preloader   preloader file with mkpimage header (i.e preloader-mkpimage.bin). Mutually exclusive with -rp."
    echo "-rp preloader  raw preloader file (i.e u-boot-spl.bin). Specify your preloader header tool with -t option. Mutually exclusive with -p."
    echo "-b bootloader  bootloader file (i.e. u-boot.img)"
    echo "-r rfs_dir/tar contents to copy into root filesystem. May be a directory containing the files or a .tar/.tgz/.tar.(gz|bz2|xz)"
    echo "-strip dirname strip away directory in provided rfs_dir/tar"
    echo "-o image       name of generated image file. Default filename is ${DEF_IMAGE_NAME}"
    echo "-m merge_dir   copy files located in dir/ to rfs."
    echo "-mr merge_dir  copy files located in dir/ to rfs, converting all merged files to be root-owned."
    echo "-g size[K/M/G] size of generated image, in unit KB, MB or GB (i.e 2000M). Default size is ${DEF_IMAGE_SIZE}B"
    echo "-pg size       size (in MBytes) of A2 bootloader partition. Default size is 1"
    echo "-t tool        tool to geneate preloader with header (i.e <path-to>/mkpimage). Use this with -rp option."
    echo "-h             this message"
}

guestfish_fail_hook () {
    guestfish --remote -- exit >/dev/null 2>&1 || :
}

guestfish_start () {
    GUESTFISH_PID=
    local IMAGE_FILE=$1
    local -a guestfish_cmd=( "guestfish"
                             "--listen"
                             "-a" "${IMAGE_FILE}" )

    set -e
    eval $("${guestfish_cmd[@]}")

    if [ -z "${GUESTFISH_PID}" ]; then
        echo "error: guestfish didn't start"
        exit -1
    fi

    trap guestfish_fail_hook EXIT ERR

    guestfish --remote -- run
}

guestfish_stop () {
    guestfish --remote -- sync
    guestfish --remote -- exit
    trap - EXIT ERR
    set +e
}

#  create a sparse image
#! input:
#!   $1 = image name
#!   $2 = image size
#! output:
#!   none
#! return
#!   0 on success
function create_sparse_image() {

    local image_name="$1"
    local image_size=$2

    #  here we allocate the space, without actually writing any byte to the file
    #! this speeds it up!
    dd if=/dev/zero of=${image_name} bs=1 seek=${image_size} count=0 >/dev/null 2>&1
    return $?
 
}

#  add a partition table to an image
#! input
#!  none; assumes guestfish is running with an attached image on /dev/sda
#! output
#!  none
#! return
#!  0 on success
function make_partition_table() {
    local sector_size=$(guestfish --remote -- blockdev-getss /dev/sda)

    guestfish --remote -- part-init /dev/sda mbr

    # Order of part-add commands determines partition number.
    # TODO - order these commands by value of partitions' CONST_PT_*_NUM values.
    # The / 1024 * 1024 bit is to truncate to a 1K boundary.
    # TODO - cleanup these calculations.
    guestfish --remote -- part-add /dev/sda p $((${CONST_PT_LX_OFFSET} / ${sector_size})) $(( (${CONST_PT_LX_OFFSET} + ${CONST_PT_LX_SIZE}) / 1024 * 1024 / ${sector_size} - 1))
    guestfish --remote -- part-set-mbr-id /dev/sda 1 "${CONST_PT_LX_TYPE}"

    guestfish --remote -- part-add /dev/sda p $((${CONST_PT_RFS_OFFSET} / ${sector_size})) $(( (${CONST_PT_RFS_OFFSET} + ${CONST_PT_RFS_SIZE}) / 1024 * 1024 / ${sector_size} - 1))
    guestfish --remote -- part-set-mbr-id /dev/sda 2 "${CONST_PT_RFS_TYPE}"

    guestfish --remote -- part-add /dev/sda p $((${PT_BOOT_OFFSET} / ${sector_size})) $(( (${PT_BOOT_OFFSET} + ${PT_BOOT_SIZE}) / 1024 * 1024 / ${sector_size} - 1))
    guestfish --remote -- part-set-mbr-id /dev/sda 3 "${CONST_PT_BOOT_TYPE}"

    guestfish --remote -- sync

    return 0
}

#  format a partition
#! input:
#!  $1 = block device
#!  $2 = type. 
#! output:
#!  none
#! return
#!  0 on success, !0 on sucksess
#! note:
#!  - valid types are: ext2, ext3, ext4, fat
function format_partition() {
    local block_dev=$1
    local ptype=$2
    local features=

    case ${ptype} in
        ext4)
            # kernel must be built with CONFIG_LBDAF to allow mounting ext4
            # filesystem with this option enabled:
            features="^huge_file"
            ;;
        *)
            ;;
    esac

    guestfish --remote -- mkfs "${ptype}" "${block_dev}" ${features:+"features:${features}"}

    return 0
}

#  copy list of files to a partition
#! input:
#!  $1: block device
#!  $2: filesystem type
#!  ${3,4,5,...}: file/dir
#! output:
#!  none
#! return
#!  0 on success
function copy_to_partition() {
    local block_dev=$1
    local fstype=$2
    # The rest of the args are the files to copy. Use "$@" to access.
    shift; shift

    # need to mount the partition
    guestfish --remote -- mount-vfs "" "${fstype}" "${block_dev}" /

    guestfish --remote -- copy-in "$@" /

    # umount
    guestfish --remote -- umount /

    return 0
}

#  determine compression type based on filename extension
#! input:
#!  $1: filename
#! output:
#!  gzip, bzip2, or xz if detected or empty string if not detected/understood
function detect_compression() {
    local filename="$1"
    local compression=

    case "${filename}" in
        *.gz|*.tgz) compression=gzip ;;
        *.bz2) compression=bzip2 ;;
        *.xz) compression=xz ;;
    esac

    echo -n "${compression}"
}

#  untar a .tar file to a partition
#! input:
#!  $1: block device
#!  $2: filesystem type
#!  ${3,4,5,...}: one or more .tar files
#! output:
#!  none
#! return
#!  0 on success
function untar_to_partition() {
    local block_dev=$1
    local fstype=$2
    # The rest of the args are the files to copy. Use "$@" to access.
    shift; shift

    # need to mount the partition
    guestfish --remote -- mount-vfs "" "${fstype}" "${block_dev}" /

    for tarfile in "$@"; do
        local compression=$(detect_compression "${tarfile}")

        guestfish --remote -- tar-in "${tarfile}" / ${compression:+"compress:${compression}"}
    done

    # umount
    guestfish --remote -- umount /

    return 0
}

#  do a raw copy to a block device
#! input
#!  $1=block device
#!  $2=source file
#!  $3=offset into block device (optional - default to start of block device)
#! output
#!  none
#! return 
#!  0 on success
function raw_copy_to_blk() {
    local block_dev=$1
    local image=$2
    local offset=${3:-0}

    guestfish --remote -- upload-offset "${image}" "${block_dev}" ${offset}

    return 0
}

#  formats and copies the RFS files into the partition
#! input:
function init_rfs() {
    local block_dev=$1
    local rfs_src=$2
    local rfs_type=$3

    [ ${DEBUG} -eq 1 ] && echo "${SELF}: ${FUNCNAME}: info: formatting partition..."
    format_partition "${block_dev}" "${rfs_type}"

    [ ${DEBUG} -eq 1 ] && echo "${SELF}: ${FUNCNAME}: info: mounting partition..."
    guestfish --remote -- mount-vfs "" "${rfs_type}" "${block_dev}" /
    
    [ ${DEBUG} -eq 1 ] && echo "${SELF}: ${FUNCNAME}: info: copying RFS files from ${rfs_src}..."
    if [ -d "${rfs_src}" ]; then
        guestfish --remote -- glob copy-in "${rfs_src}/\*" /
    elif [ -f "${rfs_src}" ]; then
        local compression=$(detect_compression "${rfs_src}")

        guestfish --remote -- tar-in "${rfs_src}" / ${compression:+"compress:${compression}"}
    else
        echo "${SELF}: ${FUNCNAME}: error: don't know what to do with file \"${rfs_src}\"."
        return 1
    fi

    # strip away directory level named STRIP_RFS_DIR if specified
    if [ "${DO_STRIP_RFS}" = "yes" ]; then
        echo "${SELF}: info: strip away /${STRIP_RFS_DIR} dir"
        guestfish --remote -- glob mv "/${STRIP_RFS_DIR}/*" /
        guestfish --remote -- rmdir "/${STRIP_RFS_DIR}"
    fi
    # ls is here for debug purposes. You can comment this out
    #guestfish --remote -- ls /

    [ ${DEBUG} -eq 1 ] && echo "${SELF}: ${FUNCNAME}: info: unmounting..."
    guestfish --remote -- umount /

    return 0
}
  
#  take a path and make it absolute
#! input:
#!  $1 = path to "absolutize"
#! output:
#!  absolute path
#! return
#!  0 on success
function make_path_absolute() {
    local path="$1"
    local abs_path

    # check if path starts with /
    echo $path | egrep -e '^/' >/dev/null 2>&1
    if [ $? -eq 0 ] ; then
        abs_path=${path}
    else
        # may start with ~
        echo ${path} | egrep -e '^~' >/dev/null 2>&1
        if [ $? -eq 0 ] ; then
            abs_path=$(echo $path | sed -e 's,^~,'${HOME}',')
        else
            abs_path=$(pwd)/${path}
        fi
    fi

    echo ${abs_path}

    # not really necessary, just for deedee the monster
    return 0  
}

#  check if a file exists and returns an absolute path to it
#! input
#!  $1=message
#!  $2=type of $3. Either d or f
#!  $3=file/dir to check
#! output
#!  absolute path to file
#! return
#!  0 on success, exit otherwise
function check_file () {
    local message="$1"
    local type=$2
    local file=$3

    if [ -z ${file} ] ; then
        echo "${SELF}: ${FUNCNAME}: error: ${message}"
        usage
        exit -1
    fi
    file=$(make_path_absolute "${file}")
    case ${type} in 
        f) 
            if [ ! -f ${file} ] ; then
                echo "${SELF}: ${FUNCNAME}: error: ${file}: no such file."
                exit -1
            fi
            ;;
        d)
            if [ ! -d ${file} ] ; then
                echo "${SELF}: ${FUNCNAME}: error: ${file}: no such directory."
                exit -1
            fi
            ;;
 
    esac

    echo ${file}

    return 0
}

#  extract the list of files and check each file exists
#! input
function get_os_file_list() {

    local raw_list=""
    local raw_a_list=""

    raw_list=$(echo $1 | sed -e 's/,/ /g')

    for f in ${raw_list} ; do
        f=$(check_file f "no such file or directory" ${f})
        raw_a_list="$(echo ${f} ${raw_a_list})"
    done

    echo ${raw_list}

    return 0
}

#################################################
# script starts here
# Here we parse options
IMAGE_NAME=${DEF_IMAGE_NAME}
IMAGE_SIZE=${DEF_IMAGE_SIZE}
A2_PT_SIZE=1
RFS_TYPE=${DEF_RFS_TYPE}
RFS_SRC=
STRIP_RFS_DIR=
MERGE_DIR=
MERGE_DIR_UID0=
PRELOADER=
BOOTLOADER=
OS_FILES=
DEBUG=${DEF_DEBUG}
DO_CMD_MKPIMAGE=no
CMD_MKPIMAGE=

if [ $# -eq 0 ]; then
    usage
    exit 0
fi

while [ $# -gt 0 ] ; do
    case $1 in
        -h) usage ; exit 0 ;;
        -k) OS_FILES=$2 ; DO_OS=yes ; shift ;;
        -r) RFS_SRC=$2 ; DO_RFS=yes ; shift ;;
        -o) IMAGE_NAME=$2 ; shift ;;
        -m) MERGE_DIR=$2 ; DO_RFS=yes ; shift ;;
        -mr) MERGE_DIR_UID0=$2 ; DO_RFS=yes ; shift ;;
        -strip) STRIP_RFS_DIR=$2 ; DO_STRIP_RFS=yes ; shift ;;
        -s) DEBUG=1 ;;
        -p) PRELOADER=$2 ; DO_PRELOADER=yes ; PRELOADER_MKPIMAGE=yes ; shift ;;
        -rp) PRELOADER=$2 ; DO_PRELOADER=yes ; DO_GEN_PRELOADER=yes ; shift ;;
        -b) BOOTLOADER=$2 ; DO_PRELOADER=yes ; shift ;;
        -g) IMAGE_SIZE=$2 ; shift ;;
        -pg) A2_PT_SIZE=$2 ; shift ;;
        -t) CMD_MKPIMAGE=$2 ; DO_CMD_MKPIMAGE=yes ; shift ;;
        *)  echo "${SELF}: error: unknown option ${1}" ; usage ; exit ;;
    esac
    shift
done

#################################################
# root no longer necessary
if [ ${UID} -eq 0 ] ; then
    echo "${SELF}: warning: script uses libguestfs, so it no longer needs to run as root."
fi

# image exists?
if [ -f ${IMAGE_NAME} ] ; then
    echo "${SELF}: warning: image ${IMAGE_NAME} exists. Remove? [y|n]"
    read yes_or_no;
    if [ "${yes_or_no}" == "y" ] ; then
        rm ${IMAGE_NAME}
    else
        exit -1
    fi
fi

#fixme
#if [ ${A2_PT_SIZE} -lt 1 ] || [ ${A2_PT_SIZE} -gt 64 ]; then
if [ ${A2_PT_SIZE} -lt 1 ] || [ ${A2_PT_SIZE} -gt 256 ]; then
    echo "${SELF}: error: Illegal A2 partition size. Specify 1 to 256 MiB."
    exit -1
fi

PT_BOOT_SIZE=$((${CONST_1M} * ${A2_PT_SIZE}))
PT_BOOT_OFFSET=${PT_BOOT_SIZE}

# Calculates image size based on user input or use default image size
# delete trailing character
IMAGE_SIZE_NUMERIC=$(echo $IMAGE_SIZE | sed s/[GMK]$//g)

# delete leading numeric characters and get unit K/M/G
IMAGE_UNIT=$(echo $IMAGE_SIZE | sed 's/[0-9]\+\.\?[0-9]*//g')

# Convert size of image to bytes
if [ $IMAGE_UNIT == "K" ] ; then
    IMAGE_SIZE=$((${IMAGE_SIZE_NUMERIC} * ${CONST_1K}))
elif [ $IMAGE_UNIT == "M" ] ; then
    IMAGE_SIZE=$((${IMAGE_SIZE_NUMERIC} * ${CONST_1M}))
elif [ $IMAGE_UNIT == "G" ] ; then
    IMAGE_SIZE=$((${IMAGE_SIZE_NUMERIC} * ${CONST_1G}))
else
    echo "${SELF}: invalid unit of size. Valid units are K, M or G."
    exit -1
fi

# The following happens no matter how many tasks have to be executed.
# We start by creating a sparse image
echo "${SELF}: info: creating image file..."
create_sparse_image ${IMAGE_NAME} ${IMAGE_SIZE}
if [ $? -ne 0 ] ; then
    echo "${SELF}: create_sparse_image: error: could not create sparse image"
    exit -1
fi

# Calculate EXT and FAT partition size based on image size. Preloader partition size is set by PT_BOOT_SIZE
# Root file System partiton, Type 83 = Linux EXT, 50% of image size
CONST_PT_RFS_SIZE=$((${IMAGE_SIZE} * 50 / 100))
CONST_PT_RFS_OFFSET=$((${PT_BOOT_OFFSET} + ${PT_BOOT_SIZE} + 5*${CONST_1M}))

# FAT file system, 40% of image size
CONST_PT_LX_SIZE=$((${IMAGE_SIZE} * 40 / 100))
CONST_PT_LX_OFFSET=$((${CONST_PT_RFS_OFFSET} + ${CONST_PT_RFS_SIZE} + 5 * ${CONST_1M}))


echo "Starting guestfish to format image."
guestfish_start "${IMAGE_NAME}"

# we now create the partition table
echo "${SELF}: info: creating partition table..."
make_partition_table
if [ $? -ne 0 ] ; then
    echo "${SELF}: error: could not create partition table"
    exit -1
fi

# create the preloader image + bootloader
if [ "X${DO_PRELOADER}" == "Xyes" ] ; then

    echo "${SELF}: info: creating preloader/bootloader image..."

    if [ -n "${BOOTLOADER}" ]; then
        BOOTLOADER=$(check_file f "no bootloader specified" ${BOOTLOADER})
    fi
    PRELOADER=$(check_file f "no bootloader specified" ${PRELOADER})

    # Check if both "-p" and "-rp" options are enabled. If yes, error out.
    if [ "X${PRELOADER_MKPIMAGE}" == "Xyes" ] && [ "X${DO_GEN_PRELOADER}" == "Xyes" ] ; then
        echo "${SELF}: error: both '-p' and '-rp' options are enabled. They should mutually exclusive enable."
        exit -1
    fi

    if [ "X${DO_GEN_PRELOADER}" == "Xyes" ] ; then
        if [ "X${DO_CMD_MKPIMAGE}" == "Xyes" ] ; then
            # Call to mkpimage tool set by user.
            PRELOADER_MKPIMAGE=preloader_image.bin
            rm -f ${PRELOADER_MKPIMAGE}
            # BootROM can support up to 4 preloader images.
            # Use same preloader for 4 images by default.
            # It is good to have 4 preloader images. This is because BootROM
            # will use the next preloader image if warm reset.
            ${CMD_MKPIMAGE} -o ${PRELOADER_MKPIMAGE} ${PRELOADER} ${PRELOADER} ${PRELOADER} ${PRELOADER}
            if [ ! -f ${PRELOADER_MKPIMAGE} ] ; then
                echo "${SELF}: error: could not create preloader image."
                exit -1
            fi
        else
            # User needs to specify preloader header generation tool if using raw preloader.
            echo "${SELF}: error: no preloader header tool is specified. Please use -t option to specify."
            exit -1
        fi
    else
        # Preloader passed in by user is with mkpimage header.
        # We can use it directly.
        PRELOADER_MKPIMAGE=${PRELOADER}
    fi

    # TODO - don't depend on the boot partition number.
    echo "${SELF}: info: copying preloader image and bootloader to A2 partition (size=${PT_BOOT_SIZE})..."
    raw_copy_to_blk "/dev/sda3" ${PRELOADER_MKPIMAGE}

    if [ -n "${BOOTLOADER}" ]; then
        PRELOADER_IMAGE_SIZE=$((256 * ${CONST_1K}))
        raw_copy_to_blk "/dev/sda3" "${BOOTLOADER}" "${PRELOADER_IMAGE_SIZE}"
    else
        echo "${SELF}: info: skipping bootloader..."
    fi

    guestfish --remote -- sync

fi      # if [ ! -z ${DO_PRELOADER} ]


# here we should copy the kernel, etc.
if [ "X${DO_OS}" == "Xyes" ] ; then
    echo "${SELF}: info: copying OS files, etc..."    

    # get the list of files and check it
    OS_FILE_LIST_RAW="$(get_os_file_list ${OS_FILES})"

    # TODO - don't depend on the FAT partition number.
    #format_partition "/dev/sda1" vfat
    format_partition "/dev/sda1" vfat

    #copy_to_partition "/dev/sda1" vfat ${OS_FILE_LIST_RAW}
    copy_to_partition "/dev/sda1" vfat ${OS_FILE_LIST_RAW}

    guestfish --remote -- sync

fi    # if [ "X${D_OS}" == "Xyes" ]

# copy the RFS
if [ "X${DO_RFS}" == "Xyes" ] ; then

    echo "${SELF}: info: creating root file system..."

    # TODO - don't depend on the rootfs partition number.
    init_rfs "/dev/sda2" "${RFS_SRC}" "${RFS_TYPE}"
    
    # add merge if required
    if [ ! -z "${MERGE_DIR}" ] ; then
        echo "${SELF}: info: merging files..."
        if [ ! "$(ls -A ${MERGE_DIR})" ]; then
             echo "${SELF}: warning: merge ${MERGE_DIR} is empty. Skip"
        else
            copy_to_partition "/dev/sda2" "${RFS_TYPE}" "${MERGE_DIR}"/*
            if [ $? -ne 0 ] ; then
                echo "{$SELF}: error: failed to merge."
                exit -1
            fi
        fi    
    fi

    if [ ! -z "${MERGE_DIR_UID0}" ] ; then
        echo "${SELF}: info: merging files..."
        if [ ! "$(ls -A ${MERGE_DIR_UID0})" ]; then
             echo "${SELF}: warning: merge ${MERGE_DIR_UID0} is empty. Skip"
        else
            TMPFILE=$(mktemp -t merge.tar.XXXXXXXXXX) || {
                echo "{$SELF}: error: couldn't create merge tarfile"
                exit -1
            }

            # Force all these files to root owner/group:
            gtar c -C "${MERGE_DIR_UID0}" --owner=0 --group=0 . >"${TMPFILE}"
            
            untar_to_partition "/dev/sda2" "${RFS_TYPE}" "${TMPFILE}"

            if [ $? -ne 0 ] ; then
                rm "${TMPFILE}"
                echo "{$SELF}: error: failed to merge."
                exit -1
            fi

            rm "${TMPFILE}"
        fi    
    fi

    guestfish --remote -- sync

fi    # if [ "X${DO_RFS}" == "Xyes" ]

guestfish_stop

exit 0
