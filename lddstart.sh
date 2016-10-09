#!/bin/sh 
./qemu-2.7.0/build/x86_64-softmmu/qemu-system-x86_64 \
-vnc :5 \
--enable-kvm \
-smp 2 \
-m 1024M \
-hda '/home/yandong/Documents/cicada/cicada/ia32e_rhel6u6.img' \
-serial pty \
-parallel pty \
#-chardev file,id=char0,path=/home/yandong/Documents/ppdev.txt \
