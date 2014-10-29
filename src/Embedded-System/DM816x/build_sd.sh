#!/bin/sh
make CROSS_COMPILE=arm-none-linux-gnueabi- ARCH=arm distclean
make CROSS_COMPILE=arm-none-linux-gnueabi- ARCH=arm ti8168_evm_config
make CROSS_COMPILE=arm-none-linux-gnueabi- ARCH=arm u-boot.ti
