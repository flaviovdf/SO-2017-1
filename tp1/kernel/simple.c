#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

int
simple_init(void)
{
  printk("Loading module\n");
  return 0;
}

void simple_exit(void)
{
  printk("Removing module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
