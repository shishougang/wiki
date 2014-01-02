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

/* The procfs read entry point */
/*
static int proctest_read(char *page, char **start, off_t offset,
                         int count, int *eof, void *data)
{
  int i = 0;
  off_t len = 0;
  struct info_struct *p;

  list_for_each_entry(p, &data_list, list) {
    len += sprintf(page + len, p->info);
  }

  *eof = 1;
  return len;
}*/

static int proctest_large_read(char *page, char **start, off_t offset,
                               int count, int *eof, void *data)
{
  off_t start_point = 0;
  off_t len = 0;

  struct info_struct *p;

  list_for_each_entry(p, &data_list, list){
    len += sprintf(page + len, p->info);

    if(start_point + len <= offset){
      start_point += len;
      len = 0;
    }else if(start_point + len >= offset + count){
      break;
    }
  }

  /* Actual start */
  *start = page + (offset - start_point);

  len -= (offset - start_point);
  if(len > count)
    len = count;
  else
    *eof = 1;
  return len;
}
   
static int seq_test_init(void)
{
  int i;
  static struct proc_dir_entry *entry = NULL;
  struct info_struct *pinfo;
  entry = create_proc_entry("seqtest", 0, NULL);
  if(entry)
    //entry->read_proc = proctest__read;
    entry->read_proc = proctest_large_read;

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
  remove_proc_entry("seqtest",NULL);
  empty_list();
}
module_init(seq_test_init);
module_exit(seq_test_exit);
