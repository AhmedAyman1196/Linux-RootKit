Obj-m := rooty.o
KERNEL_DIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell PWD)
all:
 $(MAKE) -C $(KERNEL_DIR) SUBDIRS=$(PWD)
clean:
 rm -rf *.o *.ko *.symvers *.mod.* *.order
# The first line of this Makefile is called a goal definition and it defines the module to be built (hello.o).
# obj-m defines a loadable module goal, whereas obj-y indicates a built-in object goal.
# The $(shell uname -r) is a useful call to return the current kernel build version — this ensures a degree of portability for the Makefile.
# The -C option switches the directory to the kernel directory before performing any make tasks.
# The M=$(PWD) variable assignment tells the make command where the actual project files exist.
# The modules target is the default target for external kernel modules.
# An alternative target is modules_install which would install the module (the make command would have to be executed with superuser permissions and the module installation path is required).
 