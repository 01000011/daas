#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/vmalloc.h>
#define KILL_ERROR -1
#define REG_SUC     0
#define REG_UNSUC  -1
#define SUCCESS     0
#define APPLICATION_NAME "DAAS"
#define DEVICE_NAME 'Sensor'
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
static dev_t first;  
static struct cdev c_dev; 
static struct class *clss; 
inline struct reg_info* reg_dev(struct sensor* sensor, int *status)
{
	if (alloc_chrdev_region(&first, 0, 1, APPLICATION_NAME) < 0)
  	{
    		return -1;
  	}
	
	if ((clss = class_create(THIS_MODULE, DEVICE_NAME)))
  	{
    		unregister_chrdev_region(first, 1);
    		return -1;
  	}
    	
	if (device_create(clss, NULL, first, NULL, sensor->name))
  	{
    		class_destroy(cl);
    		unregister_chrdev_region(first, 1);
    		return -1;
  	}
    	
	cdev_init(&c_dev, &pugs_fops);
    	
	if (cdev_add(&c_dev, first, 1) == -1)
  	{
    		device_destroy(cl, first);
    		class_destroy(cl);
    		unregister_chrdev_region(first, 1);
    		return -1;
  	}	

/*printk(KERN_INFO "Registering device %s", sensor->name);	
	if((major = register_chrdev(0, sensor->name, &fops)) < 0)
	{
		printk(KERN_ALERT "Registering sensor device failed with %d\n", major);
	  	*(status) = (int) REG_UNSUC;
		return NULL;
	}	
 	reg_info = (struct reg_info*) vmalloc(sizeof(struct reg_info));
        reg_info->sensor = sensor;

	*(status) = (int)REG_SUC;
	return reg_info*/
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
