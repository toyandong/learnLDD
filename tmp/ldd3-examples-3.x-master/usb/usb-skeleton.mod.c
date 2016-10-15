#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
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
	{ 0xcd71858e, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xa9434d1f, __VMLINUX_SYMBOL_STR(noop_llseek) },
	{ 0xf5948e3e, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x7e6ed3ca, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0xf08242c2, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x2207a57f, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x1ad241df, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0x3f08af56, __VMLINUX_SYMBOL_STR(usb_unanchor_urb) },
	{ 0x93d8a350, __VMLINUX_SYMBOL_STR(usb_anchor_urb) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0x67ee585, __VMLINUX_SYMBOL_STR(usb_alloc_coherent) },
	{ 0x156a8a59, __VMLINUX_SYMBOL_STR(down_trylock) },
	{ 0x6dc0c9dc, __VMLINUX_SYMBOL_STR(down_interruptible) },
	{ 0x77c4f682, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x78764f4e, __VMLINUX_SYMBOL_STR(pv_irq_ops) },
	{ 0xe5815f8a, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0xddde3bca, __VMLINUX_SYMBOL_STR(usb_deregister_dev) },
	{ 0x504864b1, __VMLINUX_SYMBOL_STR(usb_autopm_put_interface) },
	{ 0xd2b09ce5, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x963089c5, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xc8d21b5e, __VMLINUX_SYMBOL_STR(usb_register_dev) },
	{ 0x2fd91e4f, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x517b354a, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0x9e88526, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x5f37af31, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xab7d6a08, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xf1669456, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xa6bbd805, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x78e739aa, __VMLINUX_SYMBOL_STR(up) },
	{ 0xa95ff151, __VMLINUX_SYMBOL_STR(usb_free_coherent) },
	{ 0x6bf1c17f, __VMLINUX_SYMBOL_STR(pv_lock_ops) },
	{ 0xe259ae9e, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0xe9cef686, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x72f6a3e4, __VMLINUX_SYMBOL_STR(usb_autopm_get_interface) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xefdb172e, __VMLINUX_SYMBOL_STR(usb_find_interface) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xc6666412, __VMLINUX_SYMBOL_STR(usb_put_dev) },
	{ 0x702f1bdc, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0xc5092e89, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x239b47c, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0x4395953e, __VMLINUX_SYMBOL_STR(usb_kill_anchored_urbs) },
	{ 0x24f45195, __VMLINUX_SYMBOL_STR(usb_wait_anchor_empty_timeout) },
	{ 0x8ca05263, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:vFFF0pFFF0d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "9E76848E2E0A7414A8072F2");
