#!/bin/sh
#
# Build a bootable SD card image that carries the FIP (BL31 + the baremetal
# application) in the A2 boot partition.
#
# guestfish must already be installed on the host (for example, from the
# libguestfs-tools package on common Linux distributions).
#
# Usage:
#   sh sdimage_build.sh                 # uses ./fip.bin -> ./sd_image.img
#   FIP=fip.bin OUT=sd_image.img SD_SIZE=128M A2_SIZE=1 sh sdimage_build.sh
#
# A2_SIZE is in MiB. make_sdimage.sh must sit next to this script (both ship
# in the baremetal repo tools/ directory).

set -e

if ! command -v guestfish >/dev/null 2>&1; then
    echo "sdimage_build.sh: error: guestfish is required but was not found on PATH." >&2
    echo "                  Install libguestfs-tools (or your distribution's equivalent) and retry." >&2
    exit 1
fi

SELFDIR="$(cd "$(dirname "$0")" && pwd)"

# Overridable inputs (defaults mirror the documented manual flow).
FIP="${FIP:-fip.bin}"
OUT="${OUT:-sd_image.img}"
SD_SIZE="${SD_SIZE:-128M}"
A2_SIZE="${A2_SIZE:-1}"

if [ ! -f "$FIP" ]; then
    echo "sdimage_build.sh: error: FIP '$FIP' not found in $(pwd)." >&2
    exit 1
fi

chmod +x "$SELFDIR/make_sdimage.sh" 2>/dev/null || true

# make_sdimage.sh -p <fip> -o <image> -g <total size> -pg <A2 partition MB>
"$SELFDIR/make_sdimage.sh" -p "$FIP" -o "$OUT" -g "$SD_SIZE" -pg "$A2_SIZE"
