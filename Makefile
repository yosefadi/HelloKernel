kmodname = HelloKernel
obj-m += $(kmodname).o

all:
	make -C ~/raspi/raspi-linux-kernel/build M="$(PWD)" modules
	# rm *.o *.symvers *.order *.mod.c

clean:
	make -C ~/raspi/raspi-linux-kernel/build M=$(PWD) clean

insmod:
	sudo insmod ./$(kmodname).ko

rmmod:
	sudo rmmod $(kmodname)

modinfo:
	modinfo $(kmodname).ko

showmessage:
	cat /var/log/syslog

mknodNIM :
	sudo mknod /dev/NIM c 235 0
mknodNama :
	sudo mknod /dev/Nama c 234 0

rmnodNIM:
	sudo rm /dev/NIM
rmnodNama:
	sudo rm /dev/Nama

