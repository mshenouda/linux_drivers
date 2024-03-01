obj-m += driver.o
ARCH=arm64
KDIR=/lib/modules/$(shell uname -r)/build
CROSS_COMPILE=aarch64-linux-gnu-
KERN_DIR=/home/mshenouda/linux

all:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERN_DIR) M=$(shell pwd) modules
clean:	driver.c
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERN_DIR) M=$(shell pwd) clean
host:
	make -C $(KDIR) M=$(shell pwd) modules
host_clean:  driver.c
	make -C $(KDIR) M=$(shell pwd) clean
