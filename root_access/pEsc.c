// src http://tacxingxing.com/2018/02/15/linux-kernel-exploit-stack-smashing/

// kernel imports
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CSEN1001");
MODULE_VERSION("1.0");

static int __init privEsc_init(void);
static void __exit privEsc_exit(void);

module_init(privEsc_init);
module_exit(privEsc_exit);

// #################################
// Helpers                         #
// #################################



// #################################
// Main Functions                  #
// #################################

static int __init privEsc_init(void)
{
    printk(KERN_INFO "RootA: LKM succefully loaded!\n");

    return 0;
}

static void __exit privEsc_exit(void)
{
    printk(KERN_INFO "RootA: LKM succefully unloaded!\n");
}
