SOURCE_FILES = ../../../kernel/hello/hello_kernel.cl

default: all

hello_kernel.xo : $(SOURCE_FILES)
	xocc -o hello_kernel.xo -c $(SOURCE_FILES) $(XOCC_OPT_ALL) --target hw --platform $(TARGET_PLATFORM)

hello_kernel_hw_all.xclbin : hello_kernel.xo
	xocc -o hello_kernel_hw_all.xclbin -l hello_kernel.xo $(XOCC_OPT_ALL) --target hw --platform $(TARGET_PLATFORM) --nk hello_kernel:3

clean:
	rm -rf _x
	rm -rf .Xil
	rm -rf *.log
	rm -rf hello_kernel.xo
	rm -rf hello_kernel_hw_all.xclbin