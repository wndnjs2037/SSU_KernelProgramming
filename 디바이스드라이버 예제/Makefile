O_TARGET	:=	driver.ko
obj-m	:=	driver.o

KERNEL_DIR	:=	/lib/modules/$(shell uname -r)/build
PWD	:=	$(shell pwd)

default:
	make	-C	$(KERNEL_DIR)	M=$(PWD)	modules
install:
	mkdir	-p	/lib/modules/$(shell uname -r)/kernel/driver
	cp	-f	$(O_TARGET)	/lib/modules/$(shell uname -r)/kernel/driver
clean:
	make	-C	$(KERNEL_DIR)	M=$(PWD)	clean
