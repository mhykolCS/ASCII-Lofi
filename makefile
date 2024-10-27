CFLAGS = -std=c++11 $(shell pkg-config --cflags opencv4)
LIBS = $(shell pkg-config --libs opencv4 ncurses)

all : main.cpp
	clear
	g++ $(CFLAGS) $(LIBS) -o lofiAscii main.cpp
	clear
	./lofiAscii

