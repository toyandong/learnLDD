#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/ctype.h>
#include <linux/smp.h>

MODULE_LICENSE("GPL");

void print_cpu_id(void * cpuid)
{
     int cpu=smp_processor_id();
	 printk("Called: myid %d\n",cpu);
     return;
}

static int __init hello_world_init(void)
{
 	int cpu=0;
    printk("hello_world_init\n");
       
    cpu=smp_processor_id();
    printk("Caller: myid is %d\n",cpu);
    smp_call_function(print_cpu_id, &cpu, 1);
    return 0;
}

static void __exit hello_world_exit(void)
{
	printk("hello_world_exit\n");
	return;
}

module_init(hello_world_init);
module_exit(hello_world_exit);

