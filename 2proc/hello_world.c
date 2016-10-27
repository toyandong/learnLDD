#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>


static int hello_proc_show(struct seq_file *m, void *v) {
 seq_printf(m, "Hello proc!\n");
 return 0;
}

static int hello_proc_open(struct inode *inode, struct file *file) {
	return single_open(file, hello_proc_show, NULL);
}



static const struct file_operations hello_proc_fops = {
 .owner = THIS_MODULE,
 .open = hello_proc_open,
 .read = seq_read,
 .llseek = seq_lseek,
 .release = single_release,
};
 
static int __init hello_world_init(void) {
 proc_create("hello_proc", 0, NULL, &hello_proc_fops);
 return 0;
}


static void __exit hello_world_exit(void)
{
	printk("hello_world_exit\n");
	remove_proc_entry("hello_proc", NULL);
	return;
}


module_init(hello_world_init);
module_exit(hello_world_exit);


MODULE_LICENSE("GPL");


/*
1.  proc_create是新的接口，create_proc_read_entry是旧的接口
	3.10 version: http://lxr.free-electrons.com/source/include/linux/proc_fs.h?v=3.10
	3.9 version: http://lxr.free-electrons.com/source/include/linux/proc_fs.h?v=3.9

2  TODO proc seq_file是什么关系？

*/


























