// src http://turbochaos.blogspot.com/2013/09/linux-rootkits-101-1-of-3.html
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

int wakeup(void);
void close(void);

module_init(wakeup);
module_exit(close);

int wakeup(void)
{
    //list_del_init(&__this_module.list);
    // kobject_del(&THIS_MODULE->mkobj.kobj);
    printk("rooty: module loaded\n");

    return 0;
}

void close(void)
{
    printk("rooty: module removed\n");
}
