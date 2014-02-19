#include "sensor.h"
#include <linux/module.h>
static float* read(void);
static int kill(char reason[32]);
static unsigned short min_read_delay(void);
static struct sensor tmp_sensor =
{
        .name = "tmp sensor",
        .read = read,
        .kill = kill, 
	.min_read_delay = min_read_delay
};

static int __init init(void)
{
        struct reg_info* ri;	
	int status;	
	if(!(ri = reg_dev(&tmp_sensor, &status)))
	{
		//do something	
	}
	
	return status;
}

static void __exit clean(void)
{

}

static float* read(void)
{
        float *u; 
	float result = 5.5;
	u = &result; 
        return u;
}

static int kill(char reason[32])
{
	return KILL_ERROR;
}

static unsigned short min_read_delay(void)
{
        return 1;
}

module_init(init);
module_exit(clean);
