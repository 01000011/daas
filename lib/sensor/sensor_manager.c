#include <linux/completion.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/cdev.h>

#include <linux/vmalloc.h>
#include <asm/uaccess.h>
#include "sensor_manager.h"

static struct reg_info *reginfo;
static dev_t devt;
static struct cdev c_dev;
static struct class *clss;
static struct reg_info *reginfo;

static int sensor_open(struct inode *, struct file *);
static int sensor_release(struct inode *, struct file *);
static ssize_t sensor_read(struct file *, char *, size_t, loff_t *);
static struct sensor_info
{
	char name[32];
	struct sensor sensor;
	struct sensor_info* sensor_info;
};

static struct file_operations fops = 
{
	.read = sensor_read,
	.open = sensor_open,
	.release = sensor_release
};

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
        float *results = reginfo->sensor->read();
	put_user(*(results), buffer);	
	return sizeof(*results);
}

int reg_device(struct sensor* sensor)
{
	printk(KERN_INFO "Registering sensor '%s'", sensor->name);
	if (device_create(clss, NULL, devt, NULL, sensor->name) == NULL)
	{
		class_destroy(clss);
		unregister_chrdev_region(devt, 1);
		return -1;
	}
	cdev_init(&c_dev, &fops);
	c_dev.owner = THIS_MODULE;
	if (cdev_add(&c_dev, devt, 1) == -1)
	{
		device_destroy(clss, devt);
		class_destroy(clss);
		unregister_chrdev_region(devt, 1);
		return -1;
	}
	reginfo = (struct reg_info*)vmalloc(sizeof(struct reg_info));
	reginfo->sensor = sensor;	
	return 0;	
}
EXPORT_SYMBOL(reg_device);

static int __init constructor(void)
{
        printk(KERN_INFO "Sensor manager start");
        if (alloc_chrdev_region(&devt, 0, 1, DEVICE_NAME) < 0)
        {
                return -1;
        }

        if ((clss = class_create(THIS_MODULE, CLASS)) == NULL)
        {
                unregister_chrdev_region(devt, 1);
                return -1;
        }
        printk(KERN_INFO "Sensor manager complete");
        return 0;
}

static void __exit deconstructor(void)
{

}

module_init(constructor);
module_exit(deconstructor);
