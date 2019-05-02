#################################################################################
# GLOBALS                                                                       #
#################################################################################
MAKEFLAGS = -s


#################################################################################
# COMMANDS                                                                      #
#################################################################################
.PHONY: clean
all:
	echo "I am empty"

.PHONY: clean
## Delete all compiled kernel files
clean:
	find . -type f -name "Module.symvers" -delete
	find . -type f -name "Mkfile.old" -delete
	find . -type f -name "modules.order" -delete
	find . -type f -name "*.mod*" -delete
	find . -type f -name "*.o" -delete
	find . -type f -name "*.ko" -delete
	find . -type f -name "*.cmd" -delete
	find . -type f -name "*.mk" -delete
	find . -type d -name ".tmp_versions" -delete
