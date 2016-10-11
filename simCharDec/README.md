1. insmod: ERROR: could not insert module hello.ko: Required key not available
bios支持关闭UEFI Secure Boot

http://askubuntu.com/questions/762254/why-do-i-get-required-key-not-available-when-install-3rd-party-kernel-modules

2.
chardev: module license 'unspecified' taints kernel.
Disabling lock debugging due to kernel taint

MODULE_LICENSE("Dual BSD/GPL");


3.  测试
sudo mknod /dev/dev_fifo c 168 0
sudo chmod 666 /dev/dev_fifo 

cat /dev/dev_fifo
echo "sss" > /dev/dev_fifo

4.mknod 是干嘛的呢？
chardev.ko 只是驱动
而mknod创建的则是设备，虽然只是一个文件，叫它设备文件也好。

5.udev sys dev proc的区别