/*
 * Simple demonstratino of the seq_file interface
 * Felix SHI <shishougang@gmail.com>
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>   /* everything... */
#include <linux/seq_file.h>
#include <linux/kernel.h>    /* printk() */
#include <linux/slab.h>        /* kmalloc() */
#include <linux/types.h>	/* size_t */
#include <linux/list.h>

MODULE_AUTHOR("Felix Shi");
MODULE_LICENSE("Dual BSD/GPL");

struct info_struct {
  struct list_head list;
  char info[10];
};

static LIST_HEAD(data_list);
void empty_list(void)
{
  struct info_struct *p, *ptmp;
  list_for_each_entry_safe(p, ptmp, &data_list, list){
    list_del(p);
    kfree(p);
  }
}

static void *
seq_iter_seq_start(struct seq_file *seq, loff_t *pos)
{
  struct info_struct *p;
  loff_t loff = 0;
  printk("start");
  list_for_each_entry(p, &data_list, list){
    if(*pos == loff++) return p;
  }
  return NULL;
}

static void *
seq_iter_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
  struct list_head *n = ((struct info_struct *)v)->list.next;
  ++*pos;
  return (n != &data_list) ? list_entry(n, struct info_struct, list) : NULL;
}

static int
seq_iter_seq_show(struct seq_file *seq, void *v)
{
  const struct info_struct *p = v;
  seq_printf(seq, p->info);
  return 0;
}
  
static void
seq_iter_seq_stop(struct seq_file *seq, void *v)
{
}

static struct seq_operations seq_iter_seq_ops = {
  .start = seq_iter_seq_start,
  .next = seq_iter_seq_next,
  .stop = seq_iter_seq_stop,
  .show = seq_iter_seq_show
};

static int seq_iter_seq_open(struct inode *inode, struct file *file)
{
  return seq_open(file, &seq_iter_seq_ops);
}

static struct file_operations seq_iter_proc_fops = {
  .owner = THIS_MODULE,
  .open = seq_iter_seq_open, /* User supplied */
  .read = seq_read,
  .llseek = seq_lseek,
  .release = seq_release
};
 
static int seq_test_init(void)
{
  int i;
  static struct proc_dir_entry *entry = NULL;
  struct info_struct *pinfo;
  entry = create_proc_entry("seqitertest", 0, NULL);
  printk("init");
  if(entry)
    entry->proc_fops = &seq_iter_proc_fops;

  for(i = 0; i < 500; ++i){
    pinfo = kmalloc(sizeof(struct info_struct), GFP_ATOMIC);
    if(!pinfo){
      empty_list();
      return ENOMEM;
    }
    sprintf(pinfo->info, "Node No: %d\n", i);
    list_add_tail(&pinfo->list, &data_list);
  }
  return 0;
}

static void seq_test_exit(void)
{
  printk("exit");
  remove_proc_entry("seqtest",NULL);
  empty_list();
}
module_init(seq_test_init);
module_exit(seq_test_exit);
