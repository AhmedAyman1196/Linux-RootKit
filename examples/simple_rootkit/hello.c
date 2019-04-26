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
    printk("Hello World!\n");
    return 0;
}

void close(void)
{
    printk("Bye World!\n");
}
