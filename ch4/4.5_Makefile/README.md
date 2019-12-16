# Makefile

#### - module name
obj-m	:= test.o					

#### - kernel source directory
KDIR	:= /lib/modules/$(shell uname -r)/build		

#### - module source directory
PWD 	:= $(shell pwd)					

#### - module compile
default:  						
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

#### - file delete
clean:    							
	rm -rf *.ko
	rm -rf *.mod.*
	rm -rf .*.cmd
	rm -rf *.o
