#include <linux/module.h>
#include <linux/vmalloc.h>
#include "sensor_manager.h"
static int __init i(void);
static void __exit e(void);
static float* temperature_read(void);
static unsigned short temperature_min_read_delay(void);
extern int reg_device(struct sensor*);
static struct sensor temperature_sensor =
{
        .name = "temperature_sensor",
        .read = temperature_read,
	.min_read_delay = temperature_min_read_delay
};

static int __init i(void)
{
	reg_device(&temperature_sensor);
	return 0;
}

static void __exit e(void)
{

}

static float* temperature_read(void)
{
        float *u; 
	float result = 5.5;
	u = &result; 
        return u;
}

static unsigned short temperature_min_read_delay(void)
{
        return 1;
}

module_init(i);
module_exit(e);
