#Makefile

obj-m	:= test.o					>> module name

KDIR	:= /lib/modules/$(shell uname -r)/build		>> kernel source directory

PWD 	:= $(shell pwd)					>> module source directory

default:						>> module compile
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:							>> file delete
	rm -rf *.ko
	rm -rf *.mod.*
	rm -rf .*.cmd
	rm -rf *.o
