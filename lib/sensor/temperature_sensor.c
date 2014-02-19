#include "sensor.h"
#include <linux/module.h>
static float* temperature_read(void);
static int temperature_kill(char reason[32]);
static unsigned short temperature_min_read_delay(void);
static struct sensor temperature_sensor =
{
        .name = "temperature sensor",
        .read = temperature_read,
        .kill = temperature_kill, 
	.min_read_delay = temperature_min_read_delay
};

static int __init init(void)
{
        struct reg_info* ri;	
	int status;	
	if(!(ri = reg_dev(&temperature_sensor, &status)))
	{
		//do something	
	}
	
	return status;
}

static void __exit clean(void)
{

}

static float* temperature_read(void)
{
        float *u; 
	float result = 5.5;
	u = &result; 
        return u;
}

static int temperature_kill(char reason[32])
{
	return KILL_ERROR;
}

static unsigned short temperature_min_read_delay(void)
{
        return 1;
}

module_init(init);
module_exit(clean);
