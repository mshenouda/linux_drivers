/***************************************************************************//**
*  \file       driver.c
*
*  \details    Simple linux driver (Dynamically allocating the Major and Minor number)
*
*  \author     EmbeTronicX
*
* *******************************************************************************/
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/device.h>
 
dev_t dev = 0;
static struct class *dev_class;

/*
** Module Init function
*/
static int __init hello_world_init(void)
{
        /*Allocating Major number*/
        if((alloc_chrdev_region(&dev, 0, 1, "etx_dev")) <0){
                pr_info("Cannot allocate major number for device 1\n");
                return -1;
        }
        pr_info("Major = %d Minor = %d \n",MAJOR(dev), MINOR(dev));
	/*Creating struct class*/
	if((dev_class = class_create(THIS_MODULE, "etx_class")) == NULL) {
		pr_err("Cannot crate the struct class for device\n");
		goto r_class;
	}

	/*Creating device */
	if((device_create(dev_class, NULL, dev, NULL, "etx_device")) == NULL) {
		pr_err("Cannot create the device\n");
	        goto r_device;
	}
	pr_info("Kernel Module Inserted Successfully...\n");
        return 0;

r_device:
	class_destroy(dev_class);
r_class:
	unregister_chrdev_region(dev, 1);
	return -1;
}

/*
** Module exit function
*/
static void __exit hello_world_exit(void)
{
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
        unregister_chrdev_region(dev, 1);
        pr_info("Kernel Module Removed Successfully...\n");
}

module_init(hello_world_init);
module_exit(hello_world_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("EmbeTronicX <embetronicx@gmail.com>");
MODULE_DESCRIPTION("Simple linux driver (Dynamically allocating the Major and Minor number)");
MODULE_VERSION("1.1");
