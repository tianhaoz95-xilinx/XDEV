all: build/sanity_check.exe

build/sanity_check.exe: build/sanity_check.o
	g++ -std=c++14 build/sanity_check.o -L $(XILINX_XRT)/lib -lxrt_core -lxdp -o build/sanity_check.exe

build/sanity_check.o: sanity_check.cpp
	mkdir -p build
	g++ -std=c++14 -c sanity_check.cpp -I $(XILINX_XRT)/include -I $(XDP_SRC) -o build/sanity_check.o

clean:
	rm -rf build