#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include <linux/bug.h> 
#include "hello1.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("IO-31 Student");
MODULE_DESCRIPTION("Lab 6: Buggy Module");

struct my_struct {
    struct list_head list;
    ktime_t time_before;
    ktime_t time_after;
};

static LIST_HEAD(my_list_head);

void print_hello(unsigned int howmany)
{
    int i;
    struct my_struct *ptr;
    
    BUG_ON(howmany > 10);

    for (i = 0; i < howmany; i++) {
        
        if (i == 2) {
            ptr = NULL; 
            pr_info("Lab6: Simulating kmalloc failure for item #%d\n", i);
        } else {
            ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);
        }

        if (!ptr) {
            pr_err("Failed to allocate memory\n");
            continue; 
        }

        ptr->time_before = ktime_get();
        pr_info("Hello, world!\n");
        ptr->time_after = ktime_get();

        list_add_tail(&ptr->list, &my_list_head);
    }
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
    pr_info("Module hello1 loaded.\n");
    return 0;
}

static void __exit hello1_exit(void)
{
    struct my_struct *ptr, *next;

    list_for_each_entry_safe(ptr, next, &my_list_head, list) {
        ktime_t duration = ktime_sub(ptr->time_after, ptr->time_before);
        pr_info("Time spent on print: %lld ns\n", ktime_to_ns(duration));
        list_del(&ptr->list);
        kfree(ptr);
    }
    pr_info("Module hello1 unloaded.\n");
}

module_init(hello1_init);
module_exit(hello1_exit);