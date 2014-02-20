#include <linux/module.h>
#define DEVICE_NAME "daas"
#define CLASS       "sensor"
#define SUCCESS     0
struct sensor
{
	char name[32];
	float* (*read)(void);
	unsigned short (*min_read_delay)(void);
};

struct reg_info
{
	struct sensor *sensor;
};
