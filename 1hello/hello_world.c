#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/ctype.h>
#include <linux/smp.h>

MODULE_LICENSE("GPL");
static int __init hello_world_init(void)
{
    printk("hello_world_init\n");
   return 0;
}


static void __exit hello_world_exit(void)
{
	printk("hello_world_exit\n");
	return;
}


module_init(hello_world_init);
module_exit(hello_world_exit);

