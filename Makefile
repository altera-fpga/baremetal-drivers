# Wrapper Makefile for CMake build
# Usage:
#   make PLAT=agilex5 BUILD_MODE=DDR
#   make PLAT=agilex3 BUILD_MODE=DDR
#   make DEBUG=1 PLAT=agilex5 BUILD_MODE=DDR
#   make clean

DEBUG      			?= 0
BUILD_MODE 			?= OCRAM
PLAT       			?=
ATF_DIRECT_BOOT 	?= 0

SRC_DIR := $(abspath .)

# -------------------------
# Toolchain Selection
# -------------------------
ifeq ($(PLAT),agilex5)
  TOOLCHAIN := $(SRC_DIR)/cmake/toolchain-agilex5.cmake
else ifeq ($(PLAT),agilex3)
  TOOLCHAIN := $(SRC_DIR)/cmake/toolchain-agilex3.cmake
endif

# -------------------------
# Build Directory
# -------------------------
ifeq ($(DEBUG),1)
  BUILD_DIR := build/$(PLAT)/debug
else
  BUILD_DIR := build/$(PLAT)/release
endif

.PHONY: all build clean print docs docs-clean check-plat

all: check-plat
	cmake -S $(SRC_DIR) -B $(BUILD_DIR) \
	-DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN) \
	-DPLAT=$(PLAT) \
	-DDEBUG=$(DEBUG) \
	-DBUILD_MODE=$(BUILD_MODE) \
	-DATF_DIRECT_BOOT=$(ATF_DIRECT_BOOT)

	cmake --build $(BUILD_DIR) -j

build: all

check-plat:
	@if [ -z "$(TOOLCHAIN)" ]; then \
		echo "PLAT='$(PLAT)' is not supported. Use PLAT=agilex5 or PLAT=agilex3."; \
		exit 1; \
	fi

clean:
	rm -rf build

print:
	@echo "PLAT=$(PLAT)"
	@echo "TOOLCHAIN=$(TOOLCHAIN)"
	@echo "BUILD_DIR=$(BUILD_DIR)"
	@echo "DEBUG=$(DEBUG)"
	@echo "ATF_DIRECT_BOOT=$(ATF_DIRECT_BOOT)"
	@echo "BUILD_MODE=$(BUILD_MODE)"

# -------------------------
# Natural Docs Documentation
# -------------------------
ND ?= NaturalDocs
ND_CONFIG := docs/ndconfig

docs:
	@command -v "$(ND)" >/dev/null 2>&1 || { \
		echo "Natural Docs 2 was not found. Set ND to the NaturalDocs executable."; \
		exit 1; \
	}
	mkdir -p docs/naturaldocs/html
	"$(ND)" "$(ND_CONFIG)"

docs-clean:
	rm -rf docs/naturaldocs "docs/ndconfig/Working Data"
