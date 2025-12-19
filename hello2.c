#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include "hello1.h" 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("IO-31 Student");
MODULE_DESCRIPTION("Lab 5: Hello2 Module (Caller)");

static uint howmany = 1;
module_param(howmany, uint, 0644);
MODULE_PARM_DESC(howmany, "Number of times to print Hello World");

static int __init hello2_init(void)
{
    if (howmany == 0 || (howmany >= 5 && howmany <= 10)) {
        pr_warn("WARNING: howmany is %u\n", howmany);
    } else if (howmany > 10) {
        pr_err("ERROR: howmany is > 10\n");
        return -EINVAL; 
    }

    print_hello(howmany);
    
    return 0;
}

static void __exit hello2_exit(void)
{
    pr_info("Module hello2 unloaded.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);