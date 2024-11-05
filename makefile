all : src/main.cpp src/asciiLofi.h src/fileBrowser.cpp src/video.cpp
	mkdir -p build
	cd build && cmake ..
	cd build && cmake --build . --config Release
	cp build/lofiAscii lofiAscii
	./lofiAscii

build : src/main.cpp src/asciiLofi.h src/fileBrowser.cpp src/video.cpp
	mkdir -p build
	cd build && cmake ..
	cd build && cmake --build . --config Release
	cp build/lofiAscii lofiAscii

start : src/main.cpp src/asciiLofi.h src/fileBrowser.cpp src/video.cpp
	./lofiAscii