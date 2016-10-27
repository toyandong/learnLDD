#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x28950ef1, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x2296f507, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0x9c3df9b4, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x1685c91c, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x887de448, __VMLINUX_SYMBOL_STR(tty_unregister_driver) },
	{ 0xfa981f7, __VMLINUX_SYMBOL_STR(tty_unregister_device) },
	{ 0xb4b43690, __VMLINUX_SYMBOL_STR(put_tty_driver) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x6d7f09ee, __VMLINUX_SYMBOL_STR(tty_port_destroy) },
	{ 0x394a795c, __VMLINUX_SYMBOL_STR(tty_port_register_device) },
	{ 0x97aec59e, __VMLINUX_SYMBOL_STR(tty_port_init) },
	{ 0x9a025cd5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x2b038aa5, __VMLINUX_SYMBOL_STR(tty_register_driver) },
	{ 0x219840ab, __VMLINUX_SYMBOL_STR(tty_set_operations) },
	{ 0x67b27ec1, __VMLINUX_SYMBOL_STR(tty_std_termios) },
	{ 0xff1a716d, __VMLINUX_SYMBOL_STR(__tty_alloc_driver) },
	{ 0x1aeda9f9, __VMLINUX_SYMBOL_STR(tty_flip_buffer_push) },
	{ 0x46884167, __VMLINUX_SYMBOL_STR(tty_insert_flip_string_flags) },
	{ 0xeea2b688, __VMLINUX_SYMBOL_STR(tty_buffer_request_room) },
	{ 0xf0fdf6cb, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0xb5dcab5b, __VMLINUX_SYMBOL_STR(remove_wait_queue) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x5860aad4, __VMLINUX_SYMBOL_STR(add_wait_queue) },
	{ 0xffd5a395, __VMLINUX_SYMBOL_STR(default_wake_function) },
	{ 0xb8c7ff88, __VMLINUX_SYMBOL_STR(current_task) },
	{ 0x71de9b3f, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x41ec4c1a, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x98ab5c8d, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xbe2c0274, __VMLINUX_SYMBOL_STR(add_timer) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x7a1541d0, __VMLINUX_SYMBOL_STR(tty_port_open) },
	{ 0x195b380a, __VMLINUX_SYMBOL_STR(tty_port_close) },
	{ 0x4ed12f73, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x8f64aa4, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x9327f5ce, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x9abdea30, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x409873e3, __VMLINUX_SYMBOL_STR(tty_termios_baud_rate) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x74df1d4, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x16a5a12f, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0xc996d097, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "F7C291EC2DA943285B79A7F");
MODULE_INFO(rhelversion, "7.2");
