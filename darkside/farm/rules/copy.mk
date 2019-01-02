SOURCE_FILES = ../../../kernel/copy/copy_kernel.cl

default: all

copy_kernel.xo : $(SOURCE_FILES)
	xocc -o copy_kernel.xo -c $(SOURCE_FILES) $(XOCC_OPT_ALL) --target hw --platform $(TARGET_PLATFORM)

copy_kernel_hw_all.xclbin : copy_kernel.xo
	xocc -o copy_kernel_hw_all.xclbin -l copy_kernel.xo $(XOCC_OPT_ALL) --target hw --platform $(TARGET_PLATFORM)

clean:
	rm -rf _x
	rm -rf .Xil
	rm -rf *.log
	rm -rf copy_kernel.xo
	rm -rf copy_kernel_hw_all.xclbin