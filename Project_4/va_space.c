#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/pid.h>
#include <linux/moduleparam.h>

static int pid;

module_param(pid, int, 0644);
MODULE_PARM_DESC(pid, "Process ID");

static int __init va_space_init(void)
{
    struct pid *proc_pid;
    struct task_struct *task;
    struct mm_struct *mm;
    unsigned long total_size = 0;

    proc_pid = find_get_pid(pid);
    if (!proc_pid) {
        printk(KERN_INFO "Invalid PID\n");
        return -ESRCH;
    }

    task = pid_task(proc_pid, PIDTYPE_PID);
    if (!task) {
        printk(KERN_INFO "Cannot find task for PID %d\n", pid);
        return -ESRCH;
    }

    mm = task->mm;
    if (mm) {
        struct vm_area_struct *vma = mm->mmap;
        while (vma) {
            total_size += vma->vm_end - vma->vm_start;
            vma = vma->vm_next;
        }
    }

    printk(KERN_INFO "Total virtual address space size for PID %d is %lu bytes\n", pid, total_size);
    return 0;
}

static void __exit va_space_exit(void)
{
    printk(KERN_INFO "Exiting va_space module\n");
}

module_init(va_space_init);
module_exit(va_space_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kenyou Teoh");
MODULE_DESCRIPTION("Virtual Address Space Size Module");
