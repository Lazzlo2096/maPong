.PTHONY: all linux windows windows4profiling run clean

CFLAGS=-I./ALX/include/ #INCLUDES ?
CFLAGS2=-c -Wall

CPPFLAGS=-std=c++11

LIBS=-lallegro -lallegro_primitives -lallegro_font -lallegro_ttf #LDFLAGS ?
LIBS_WIN=-lallegro-5.0.10-monolith-md -lallegro_primitives-5.0.10-md -lallegro_font-5.0.10-md -lallegro_ttf-5.0.10-md

SOURCES_DIR=./src
SOURCES_NAMES=main.cpp Sprite.cpp PingPongItems.cpp Rectangle.cpp
SOURCES = $(patsubst %,$(SOURCES_DIR)/%,$(SOURCES_NAMES))

EXECUTABLE=maPong

all: linux

linux: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	g++ $(CFLAGS) $(SOURCES) $(LIBS) $(CPPFLAGS) -g -o $(EXECUTABLE)
		#-lallegro_image -lallegro_dialog

windows: $(SOURCES)
	g++ $(CFLAGS) $(SOURCES) $(LIBS_WIN) $(CPPFLAGS) -o $(EXECUTABLE)

windows4profiling: $(SOURCES)
	g++ $(CFLAGS) $(SOURCES) $(LIBS_WIN) $(CPPFLAGS) -pg -o $(EXECUTABLE)

run:
	./$(EXECUTABLE)

clean:
	rm ./$(EXECUTABLE)

#http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
#IDIR =../include
#_DEPS = hellomake.h
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
#test:
#	echo $(DEPS) # ../include/hellomake.h

