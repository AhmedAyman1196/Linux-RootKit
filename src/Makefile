MAKEFLAGS = -s
obj-m += lkm.o

all: compile
	gcc root.c -o root
	chmod +x root
	./root

compile:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
