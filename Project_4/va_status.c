#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/pid.h>
#include <linux/moduleparam.h>
#include <linux/highmem.h>
#include <linux/spinlock.h>

static int pid;
static char *addr_str;

module_param(pid, int, 0644);
module_param(addr_str, charp, 0644);
MODULE_PARM_DESC(pid, "Process ID");
MODULE_PARM_DESC(addr_str, "Virtual Address");

static int __init va_status_init(void)
{
    struct pid *proc_pid;
    struct task_struct *task;
    struct mm_struct *mm;
    unsigned long addr;
    int ret;

    ret = kstrtoul(addr_str, 16, &addr);
    if (ret) {
        printk(KERN_INFO "Error converting address\n");
        return ret;
    }

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
        pgd_t *pgd;
        pud_t *pud;
        pmd_t *pmd;
        pte_t *pte;
        spinlock_t *ptl;

        pgd = pgd_offset(mm, addr);
        pud = pud_offset(pgd, addr);
        pmd = pmd_offset(pud, addr);
        pte = pte_offset_map_lock(mm, pmd, addr, &ptl);

        if (pte_present(*pte)) {
            printk(KERN_INFO "Address %lx is in memory\n", addr);
        } else {
            printk(KERN_INFO "Address %lx is not in memory\n", addr);
        }

        pte_unmap_unlock(pte, ptl);
    }

    return 0;
}

static void __exit va_status_exit(void)
{
    printk(KERN_INFO "Exiting va_status module\n");
}

module_init(va_status_init);
module_exit(va_status_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Page Table Walk Module");
