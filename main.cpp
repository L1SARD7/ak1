#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("IO-31 Student");
MODULE_DESCRIPTION("Lab 4 Kernel Module");
MODULE_VERSION("0.1");

static uint howmany = 1;
module_param(howmany, uint, 0644);
MODULE_PARM_DESC(howmany, "Number of times to print Hello World");

struct my_struct {
    struct list_head list;
    ktime_t time;
};

static LIST_HEAD(my_list_head);

static int __init hello_init(void)
{
    int i;
    struct my_struct *ptr;

    if (howmany == 0 || (howmany >= 5 && howmany <= 10)) {
        printk(KERN_WARNING "WARNING: howmany is %u\n", howmany);
    } else if (howmany > 10) {
        printk(KERN_ERR "ERROR: howmany is > 10\n");
        return -EINVAL;
    }

    for (i = 0; i < howmany; i++) {
        ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);
        if (!ptr) {
            printk(KERN_ERR "Failed to allocate memory\n");
            return -ENOMEM;
        }
        ptr->time = ktime_get();
        list_add_tail(&ptr->list, &my_list_head);
        printk(KERN_EMERG "Hello, world!\n");
    }
    return 0;
}

static void __exit hello_exit(void)
{
    struct my_struct *ptr, *next;
    list_for_each_entry_safe(ptr, next, &my_list_head, list) {
        printk(KERN_EMERG "Time: %lld ns\n", ktime_to_ns(ptr->time));
        list_del(&ptr->list);
        kfree(ptr);
    }
    printk(KERN_EMERG "Goodbye, world!\n");
}

module_init(hello_init);
module_exit(hello_exit);
