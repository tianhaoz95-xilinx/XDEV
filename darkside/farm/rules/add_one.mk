SOURCE_FILES = ../../../../third_party/XRT/tests/unit_test/cdma/addone.cl

KERNEL_BANK_OPTION = --nk add0:1:add00 \
					--nk add1:1:add10 \
					--nk add2:1:add20 \
					--nk add3:1:add30 \
					--sp add00.m_axi_gmem:bank0 \
					--sp add10.m_axi_gmem:bank1 \
					--sp add20.m_axi_gmem:bank2 \
					--sp add30.m_axi_gmem:bank3

default: all

add_one_kernel.xo : $(SOURCE_FILES)
	xocc -o add_one_kernel.xo -c $(SOURCE_FILES) $(XOCC_OPT_ALL) --target hw --platform $(TARGET_PLATFORM)

add_one_kernel_no_profile.xo : $(SOURCE_FILES)
	xocc -o add_one_kernel.xo -c $(SOURCE_FILES) --target hw --platform $(TARGET_PLATFORM)

add_one_kernel_hw_all.xclbin : add_one_kernel.xo
	xocc -o add_one_kernel_hw_all.xclbin -l add_one_kernel.xo $(XOCC_OPT_ALL) --target hw --platform $(TARGET_PLATFORM)

add_one_kernel_hw_no_profile.xclbin : add_one_kernel_no_profile.xo
	xocc -o add_one_kernel_hw_all.xclbin -l add_one_kernel.xo --target hw --platform $(TARGET_PLATFORM)

add_one_kernel_hw_all_banks.xclbin : add_one_kernel_no_profile.xo
	xocc -o add_one_kernel_hw_all.xclbin -l add_one_kernel.xo --target hw --platform $(TARGET_PLATFORM) $(KERNEL_BANK_OPTION)

clean:
	rm -rf _x
	rm -rf .Xil
	rm -rf *.log
	rm -rf add_one_kernel.xo
	rm -rf add_one_kernel_hw_all.xclbin
	rm -rf add_one_kernel_hw_no_profile.xclbin
	rm -rf add_one_kernel_hw_all_banks.xclbin