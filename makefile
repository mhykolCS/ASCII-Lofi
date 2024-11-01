CFLAGS = -std=c++11 $(shell pkg-config --cflags opencv4)
LIBS = $(shell pkg-config --libs opencv4 ncurses)
CLIBS = -I.lib/portaudio/include .lib/portaudio/lib/.libs/libportaudio.a -lrt -lasound -ljack -pthread

all : main.cpp
	clear
	g++ $(CFLAGS) $(LIBS) -o lofiAscii main.cpp video.cpp fileBrowser.cpp $(CLIB)
	clear
	./lofiAscii

install : 
	mkdir -p lib
	curl http://files.portaudio.com/archives/pa_stable_v190700_20210406.tgz | tac | tac | tar -zxf -C lib
	cd lib/portaudio && ./configure && $(MAKE) -j

uninstall : 
	cd lib/portaudio && $(MAKE) uninstall
	rm -rf /lib/portaudio