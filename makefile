all : src/*
	mkdir -p build
	cd build && cmake ..
	cd build && cmake --build . --config Release
	cp build/lofiAscii lofiAscii
	./lofiAscii

build : src/*
	mkdir -p build
	cd build && cmake ..
	cd build && cmake --build . --config Release
	cp build/lofiAscii lofiAscii

start : src/*
	./lofiAscii

remove:
	rm -rf build