#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

// src http://turbochaos.blogspot.com/2013/09/linux-rootkits-101-1-of-3.html

// A driver template is as simple as a normal C program template with a few additions. A driver requires a module_init(), module_exit(), a MODULE_LICENSE(), and a few header files to start off with.
//  I named the rootkit rooty, so that convention will remain. Here's a simple skeleton for the driver:

MODULE_LICENSE("GPL");
int rooty_init(void);
void rooty_exit(void);
module_init(rooty_init);
module_exit(rooty_exit);

int rooty_init(void) {
 printk("rooty: module loaded\n");
 return 0;
}

void rooty_exit(void) {
 printk("rooty: module removed\n");
}
