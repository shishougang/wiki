
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/version.h>
#include <linux/list.h>
#include <sys/malloc.h>

MODULE_LICENSE("GPL");



#define init_name_hash()		0
#define IFNAMSIZ 16

#define NETDEV_HASHBITS	8
#define NETDEV_HASHENTRIES (1 << NETDEV_HASHBITS)
/* partial hash update function. Assume roughly 4 bits per character */
static inline unsigned long
partial_name_hash(unsigned long c, unsigned long prevhash)
{
  return (prevhash + (c << 4) + (c >> 4)) * 11;
}
/*
 * Finally: cut down the number of bits to a int value (and try to avoid
 * losing bits)
 */
static inline unsigned long end_name_hash(unsigned long hash)
{
  return (unsigned int) hash;
}
/* Compute the hash for a name string. */
static inline unsigned int
full_name_hash(const unsigned char *name, unsigned int len)
{
  unsigned long hash = init_name_hash();
  while (len--)
    hash = partial_name_hash(*name++, hash);
  return end_name_hash(hash);
}

struct net {
  struct hlist_head       *dev_name_head;
};

static inline struct hlist_head *dev_name_hash(struct net *net, const char *name)
{
  unsigned hash = full_name_hash(name, strnlen(name, IFNAMSIZ));
  return &net->dev_name_head[hash & ((1 << NETDEV_HASHBITS) - 1)];
}  


static struct hlist_head *netdev_create_hash(void)
{
  int i;
  struct hlist_head *hash;
  
  hash = kmalloc(sizeof(*hash) * NETDEV_HASHENTRIES, GFP_KERNEL);
  if (hash != NULL)
    for (i = 0; i < NETDEV_HASHENTRIES; i++)
      INIT_HLIST_HEAD(&hash[i]);

  return hash;
}

struct net_device {
  char name[IFNAMSIZ];
  struct hlist_node name_hlist;
  int net_num;
};

struct net_device *dev_get_by_name(struct net *net, const char *name) {
  struct hlist_node *p;
  hlist_for_each(p, dev_name_hash(net, name)) {
    struct net_device *dev
        = hlist_entry(p, struct net_device, name_hlist);
    if (!strncmp(dev->name, name, IFNAMSIZ))
      return dev;
  }
  return NULL;
}

static struct net net_space;
static struct net_device *devices;
static int hlist_module_init(void) {
  const int dev_num = 10;
  int i;
  net_space.dev_name_head = netdev_create_hash();
  if (net_space.dev_name_head == NULL) {
    goto err_name;
  }
  devices = kmalloc(sizeof(struct net_device) * dev_num, GFP_KERNEL);
  if (devices == NULL) {
    goto err_dev;
  }
  for (i = 0; i < dev_num; ++i) {
    sprintf(devices[i].name, IFNAMSIZ, "eth%d", i); 
    devices[i].net_num = i;
    hlist_add_head(&devices[i].name_hlist, dev_name_hash(&net_space, devices[i].name));
  }

  
  return 0;
  
err_dev:
  kfree(net_space.dev_name_head);
err_name:
  return -ENOMEM;
}


static void hlist_module_exit(void) {
  kfree(net_space.dev_name_head);
}

module_init(hlist_module_init);
module_exit(hlist_module_exit);
