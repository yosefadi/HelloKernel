#!/bin/bash

if [ $1 == "install" ]; then
	insmod HelloKernel.ko
	mknod /dev/HelloName c 237 0
	mknod /dev/HelloNIM c 238 0
elif [ $1 == "remove" ]; then
	rm -rf /dev/HelloName
	rm -rf /dev/HelloNIM
	rmmod HelloKernel
elif [ $1 == "hello_name" ]; then
	cat /dev/HelloName
elif [ $1 == "hello_nim" ]; then
	cat /dev/HelloNIM
fi

