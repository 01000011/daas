#include "sensor.h"
#include <linux/module.h>
struct device 
{
	char name[32];
	float  (*read)(void);
	unsigned short (*min_read_delay)();
};
static int reg_device(struct sensor*);
static void unreg_device(struct sensor*);
static int __init init(void)
{
	return -1;
}

static void __exit clean(void)
{

}

static int reg_device(struct sensor* sensor)
{

}

static void unreg_device(struct sensor* sensor)
{

}

EXPORT_SYMBOL(reg_device);
EXPORT_SYMBOL(unreg_device);
MODULE_INIT(init);
MODULE_EXIT(clean);
