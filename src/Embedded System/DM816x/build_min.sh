#!/bin/sh
rm MLO
make CROSS_COMPILE=arm-none-linux-gnueabi- ARCH=arm distclean
make CROSS_COMPILE=arm-none-linux-gnueabi- ARCH=arm ti8168_evm_min_sd
make CROSS_COMPILE=arm-none-linux-gnueabi- ARCH=arm u-boot.ti
mv u-boot.min.sd MLO
