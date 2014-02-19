#include <linux/kernel.h>
#include <linux/vmalloc.h>
#define KILL_ERROR -1
#define REG_SUC     1
struct reg_info
{
	struct sensor* s;
};

struct sensor 
{
	char name[32];
	int (*kill)(char[32]);
	unsigned short (*min_read_delay)(void);
	float* (*read)(void);
};

inline struct reg_info* reg_dev(struct sensor* dev, int *status)
{
 	struct reg_info* ri = (struct reg_info*) vmalloc(sizeof(struct reg_info));
	printk(KERN_INFO "Registering device %s", dev->name);
	ri->s = dev; 
	*(status) = (int)REG_SUC;
	return ri;
} 
