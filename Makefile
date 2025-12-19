ccflags-y := -I$(PWD)/inc

obj-m += hello1.o hello2.o

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean