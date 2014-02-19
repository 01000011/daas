#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/vmalloc.h>
#define KILL_ERROR -1
#define REG_SUC     0
#define REG_UNSUC  -1
#define SUCCESS     0
static int sensor_open(struct inode *, struct file *);
static int sensor_release(struct inode *, struct file *);
static ssize_t sensor_read(struct file *, char *, size_t, loff_t *);
static struct file_operations fops = 
{
	.read = sensor_read,
	.open = sensor_open,
	.release = sensor_release
};

struct reg_info
{
	struct sensor* sensor;
};

struct sensor 
{
	char name[32];                          //name or sensor
	int (*kill)(char[32]);                  //function to kill sensor
	unsigned short (*min_read_delay)(void); //delay between sensor reads
	float* (*read)(void);                   //sensor reading value(s)
};
int major;
static struct reg_info* reg_info;
inline struct reg_info* reg_dev(struct sensor* sensor, int *status)
{
	printk(KERN_INFO "Registering device %s", sensor->name);	
	if((major = register_chrdev(0, sensor->name, &fops)) < 0)
	{
		printk(KERN_ALERT "Registering sensor device failed with %d\n", major);
	  	*(status) = (int) REG_UNSUC;
		return NULL;
	}	
 	reg_info = (struct reg_info*) vmalloc(sizeof(struct reg_info));
        reg_info->sensor = sensor;

	*(status) = (int)REG_SUC;
	return reg_info;
}

inline void unreg_dev(struct reg_info *reg_info)
{

}

static int sensor_open(struct inode *inode, struct file *file)
{
	return SUCCESS;
}

static int sensor_release(struct inode *inode, struct file *file)
{
	return SUCCESS;
}

static ssize_t sensor_read(struct file *file, char *buffer, size_t length, loff_t *offset)
{
        float *results = reg_info->sensor->read();
	put_user(*(results), buffer);	
	return sizeof(*results);
}

EXPORT_SYMBOL(reg_dev);
