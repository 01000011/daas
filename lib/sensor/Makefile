obj-m += sensor_manager.o 
obj-m += temperature_sensor.o
#sensors-objs := sensor_manager.o temperature_sensor.o
modules:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
