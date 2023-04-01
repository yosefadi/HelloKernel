kmodname = HelloKernel
obj-m += $(kmodname).o

all:
	make -C ~/raspi/raspi-linux-kernel/build M="$(PWD)" modules
	# rm *.o *.symvers *.order *.mod.c

clean:
	make -C ~/raspi/raspi-linux-kernel/build M=$(PWD) clean

