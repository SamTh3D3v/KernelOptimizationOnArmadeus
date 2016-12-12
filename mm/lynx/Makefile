obj-m := moduleko.o
moduleko-objs :=  TransitionTableOperations.o PageLinkedListOperations.o FileLinkedListOperations.o TransitionLinkedListOperations.o  TransitionTableOperations.o LynxJprobs.o


KDIR=/home/armadeus/qemu/linux-2.6.29.6
ARCH=arm
CROSS_COMPILE=arm-linux- 
all:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) clean
