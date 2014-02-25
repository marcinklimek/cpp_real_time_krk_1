#include <linux/init.h>
#include <linux/fs.h>
#include <linux/major.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/blkdev.h>
#include <linux/uaccess.h>
#include <linux/spinlock.h>

#define DEVICE_NAME "char_test_device"
#define CLASS_NAME "char_test"

static int dev_major;
static struct class* plp_class = NULL;
static struct device* char_dev = NULL;

#define SIZE 128

char payload[ SIZE ] = "ABC\n";

static ssize_t char_read(struct file* file, char __user *buf,
                         size_t count, loff_t *ppos)
{
    ssize_t size;
    
    printk( KERN_INFO "char_test, called char_read");
    
    
    size = simple_read_from_buffer(buf, count, ppos, payload, strlen(payload)  );
    
    printk(KERN_INFO "SIZE %d", (int)size);
    
    return size;
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
    
    dev_major = register_chrdev(0, DEVICE_NAME, &char_fops );  // cat /proc/devices 
    if ( dev_major < 0 )
    {
        return -1;
    }
    
    plp_class = class_create( THIS_MODULE, CLASS_NAME); // /sys/class
    if ( plp_class == NULL )
    {
        // unregister device
        return -1;
    }
    
    char_dev = device_create( plp_class, NULL, MKDEV(dev_major, 0), NULL, CLASS_NAME ); // 
    if ( char_dev == NULL )                                                  // /dev/char_test
    {
        //unregister
        //destroy class
        return -1;
    }
        
        
    return 0;
}

static void __exit char_exit(void)
{
    printk( KERN_INFO "char_test, called char_exit");
    
    device_destroy( plp_class, MKDEV( dev_major, 0) );
    class_unregister( plp_class );
    class_destroy( plp_class );
    unregister_chrdev( dev_major, DEVICE_NAME );
}

module_init(char_init);
module_exit(char_exit);

MODULE_AUTHOR("module author");
MODULE_DESCRIPTION("description");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL");

