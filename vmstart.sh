#!/bin/sh
#doa 154100
/home/rip/Documents/qemu-2.7.0/build/x86_64-softmmu/qemu-system-x86_64 \
--enable-kvm \
-smp 4 \
-m 2048M \
-hda /home/rip/Documents/xubuntu_12_x64.img \

