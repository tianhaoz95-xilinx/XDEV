SOURCE_FILE := ../../kernel/vadd/vadd_kernel.cl

vadd_kernel.xo : $(SOURCE_FILES)
	xocc -o vadd_kernel.xo -c $(SOURCE_FILES) $(XOCC_OPT_ALL) --target hw --platform $(TARGET_PLATFORM)

vadd_kernel_hw_all.xclbin : vadd_kernel.xo
	xocc -o vadd_kernel_hw_all.xclbin -l vadd_kernel.xo $(XOCC_OPT_ALL) --target hw --platform $(TARGET_PLATFORM)