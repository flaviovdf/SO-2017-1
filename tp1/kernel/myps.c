#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>

int
ps_init(void)
{
  struct task_struct *task;
  printk(KERN_INFO "Loading module myps\n");
  for_each_process(task) {
    printk("Name: %s PID: [%d]\n", task->comm, task->pid);
  }
  return 0;
}

void ps_exit(void)
{
  printk(KERN_INFO "Removing module myps\n");
}

module_init(ps_init);
module_exit(ps_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
