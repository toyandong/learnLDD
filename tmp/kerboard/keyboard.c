/*
 *  yandong 2016-10-04
 *  chardev.c -- create a new char dev
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>

#define MAJOR_NUM 168

struct mycdev {
	unsigned char buffer[50];
	struct cdev cdev;
};

struct mycdev dev_fifo;


static int dev_fifo_open(struct inode * inode, struct file * file)
{
	printk("dev_fifo_open\n");
	return 0;
}


static ssize_t dev_fifo_read(struct file * file, char __user * buf, size_t size, loff_t * ppos)
{
	printk("dev_fifo_read\n");
	return 0;
}

static ssize_t dev_fifo_write(struct file * file, const char __user * buf, size_t size, loff_t * ppos)
{
	printk("dev_fifo_write\n");
	return size;
}


static const struct file_operations fifo_operations = {
	.owner = THIS_MODULE,
	.open = dev_fifo_open,
	.read = dev_fifo_read,
	.write = dev_fifo_write,
};




static int __init chardev_init(void)
{
	int ret;
	dev_t dev_num;
	
	printk("hello world\n");
	
	dev_num = MKDEV(MAJOR_NUM, 0);
	
	cdev_init(&dev_fifo.cdev, &fifo_operations);
	
	ret = register_chrdev_region(dev_num, 1, "dev_filo");
	if(ret < 0) {
		printk("Fail to register_chrdev_region\n");
		return -EIO;
	}
	
	ret = cdev_add(&dev_fifo.cdev, dev_num, 1);
	if(ret < 0) {
		printk("Fail to cdev_add\n");
		goto unregister_chardev;
	}
	
	printk("register_chrdev_region OK\n");
	return 0;
unregister_chardev:
	unregister_chrdev_region(dev_num, 1);
	return -1;
	
	
}

static void __exit chardev_exit(void)
{
	printk("Goodbye world\n");
	cdev_del(&dev_fifo.cdev);
	unregister_chrdev_region(MKDEV(MAJOR_NUM, 0), 1);
}

module_init(chardev_init);
module_exit(chardev_exit);


MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("yandong");
MODULE_VERSION("v1.0");
MODULE_DESCRIPTION("chardev.c -- create a new char dev");


