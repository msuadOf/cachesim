# BUILD_TOOL?=ninja
BUILD_TOOL?=make
all:init
	@ cd build && ${BUILD_TOOL}

run:init
	@ cd build && ${BUILD_TOOL} run

init:${BUILD_TOOL}_init
ninja_init:
	mkdir -p build 
	cd build && cmake .. -G Ninja 
make_init:
	mkdir -p build 
	cd build && cmake .. 

clean:
	rm -rf ./build