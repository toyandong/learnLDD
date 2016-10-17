#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/sched.h>
#include <linux/kernel.h>	/* printk() */
#include <linux/fs.h>		/* everything... */
#include <linux/errno.h>	/* error codes */
#include <linux/delay.h>	/* udelay */
#include <linux/kdev_t.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/poll.h>
#include <linux/wait.h>

#include <asm/io.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>

#define MAJOR_NUM 250

struct simpp_cdev_t {
	unsigned char buffer[50];
	struct cdev cdev;
};

struct simpp_cdev_t simpp;
unsigned long short_base = 0x378;

ssize_t simpp_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	int retval = count;
	unsigned long port = short_base;
	unsigned char *kbuf = kmalloc(count, GFP_KERNEL), *ptr;
    
	if (!kbuf)
		return -ENOMEM;
	ptr = kbuf;
	
	while (count--) {
		*(ptr++) = inb(port);
		rmb();
	}
		
	if ((retval > 0) && copy_to_user(buf, kbuf, retval))
		retval = -EFAULT;
	kfree(kbuf);
	return retval;

}

ssize_t simpp_write(struct file *filp, const char __user *buf, size_t count,
		loff_t *f_pos)
{
	unsigned char *kbuf = kmalloc(count, GFP_KERNEL), *ptr;
	unsigned long port = short_base;
	if (!kbuf)
		return -ENOMEM;
	if (copy_from_user(kbuf, buf, count))
		return -EFAULT;
	ptr = kbuf;
	
	while (count--) {
		outb(*(ptr++), port);
		wmb();
	}
	return count;
}

int simpp_open (struct inode *inode, struct file *filp)
{
	printk("%s(): OK\n", __func__);
	return 0;
}

int simpp_release (struct inode *inode, struct file *filp)
{
	printk("%s(): OK\n", __func__);
	return 0;
}

struct file_operations simpp_fops = {
	.owner	 = THIS_MODULE,
	.read	 = simpp_read,
	.write	 = simpp_write,
	.open	 = simpp_open,
	.release = simpp_release,
};

static int __init short_init(void)
{
	int ret;
	dev_t dev_num;
	dev_num = MKDEV(MAJOR_NUM, 0);
	
	if (! request_region(short_base, 8, "simpp")) {
		printk(KERN_INFO "short: can't get I/O port address 0x%lx\n",
				short_base);
		return -ENODEV;
	}
	
	ret = register_chrdev_region(dev_num, 1, "simpp");
	if(ret < 0) {
		printk("Fail to register_chrdev_region\n");
		return -EIO;
	}
	
	cdev_init(&simpp.cdev, &simpp_fops);
	ret = cdev_add(&simpp.cdev, dev_num, 1);
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

static void __exit short_cleanup(void)
{
	cdev_del(&simpp.cdev);
	unregister_chrdev_region(MKDEV(MAJOR_NUM, 0), 1);
}


module_init(short_init);
module_exit(short_cleanup);
MODULE_LICENSE("Dual BSD/GPL");




























