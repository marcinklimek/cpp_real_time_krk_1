#include <linux/init.h>
#include <linux/fs.h>
#include <linux/major.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/blkdev.h>
#include <linux/uaccess.h>
#include <linux/spinlock.h>


static ssize_t char_read(struct file* file, char __user *buf,
                         size_t count, loff_t *ppos)
{
    printk( KERN_INFO "char_test, called char_read");
    return 0;
}

/*

static ssize_t char_write(struct file* file, const char __user *buf, size_t count, loff_t *ppos)
{
    printk( KERN_INFO "char_test, called char_write");
    return 0;
}

static struct file_operations char_fops =
{
    .read = char_read,
    .write = char_write
};

*/


static struct file_operations char_fops =
{
    .read = char_read,
};

static int __init char_init(void)
{
    printk( KERN_INFO "char_test, called char_init");
    return 0;
}

static void __exit char_exit(void)
{
    printk( KERN_INFO "char_test, called char_init");
}

module_init(char_init);
module_exit(char_exit);

MODULE_AUTHOR("module author");
MODULE_DESCRIPTION("description");
MODULE_VERSION("1.0");
MODULE_LICENSE("gpl");

