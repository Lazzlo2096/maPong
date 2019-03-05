.PTHONY: all linux windows windows4profiling run clean linux_old

IS_DEBUG= # -g

CFLAGS=-I./ALX/include/ #INCLUDES ?
CFLAGS2=-c -Wall

CPPFLAGS=-std=c++11

BOOST_LIBS=-pthread -lboost_system -lboost_program_options # -pthread 
ALLEGRO_LIBS=-lallegro -lallegro_primitives -lallegro_font -lallegro_ttf #LDFLAGS ? 
ALLEGRO_WIN_LIBS=-lallegro-5.0.10-monolith-md -lallegro_primitives-5.0.10-md -lallegro_font-5.0.10-md -lallegro_ttf-5.0.10-md

SOURCES_DIR=./src
SOURCES_NAMES=main.cpp Sprite.cpp PingPongItems.cpp Rectangle.cpp
SOURCES = $(patsubst %,$(SOURCES_DIR)/%,$(SOURCES_NAMES))

EXECUTABLE=maPong

MKDIR_P=mkdir -p
OUT_DIR=./bin


all: linux

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

linux: ${OUT_DIR} ./bin/main.o ./bin/server.o ./bin/client.o ./bin/Sprite.o ./bin/PingPongItems.o ./bin/Rectangle.o 
	g++ ./bin/main.o ./bin/server.o ./bin/client.o ./bin/Sprite.o ./bin/PingPongItems.o ./bin/Rectangle.o $(BOOST_LIBS) $(ALLEGRO_LIBS) -std=c++11 $(IS_DEBUG) -o ./bin/maPong
./bin/server.o: ./src/server/server.cpp 
	g++ ./src/server/server.cpp -pthread -std=c++11 $(IS_DEBUG) -c -o ./bin/server.o
./bin/client.o: ./src/server/client.cpp
	g++ ./src/server/client.cpp -std=c++11 $(IS_DEBUG) -c -o ./bin/client.o
./bin/Sprite.o: ./src/Sprite.cpp
	g++ -I./ALX/include/ ./src/Sprite.cpp -std=c++11 $(IS_DEBUG) -c -o ./bin/Sprite.o
./bin/PingPongItems.o: ./src/PingPongItems.cpp
	g++ -I./ALX/include/ ./src/PingPongItems.cpp -std=c++11 $(IS_DEBUG) -c -o ./bin/PingPongItems.o
./bin/Rectangle.o: ./src/Rectangle.cpp
	g++ -I./ALX/include/ ./src/Rectangle.cpp -std=c++11 $(IS_DEBUG) -c -o ./bin/Rectangle.o
./bin/main.o: ./src/main.cpp
	g++ -I./ALX/include/ ./src/main.cpp -std=c++11 $(IS_DEBUG) -c -o ./bin/main.o



linux_old: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	g++ $(CFLAGS) $(SOURCES) $(ALLEGRO_LIBS) $(CPPFLAGS) $(IS_DEBUG) -o $(EXECUTABLE)
		#-lallegro_image -lallegro_dialog

windows: $(SOURCES)
	g++ $(CFLAGS) $(SOURCES) $(ALLEGRO_WIN_LIBS) $(CPPFLAGS) -o $(EXECUTABLE)

windows4profiling: $(SOURCES)
	g++ $(CFLAGS) $(SOURCES) $(ALLEGRO_WIN_LIBS) $(CPPFLAGS) -p $(IS_DEBUG) -o $(EXECUTABLE)


maPong_with_server_lin:
	g++ $(CFLAGS) ./src/maPong.cpp ./src/server/server.cpp ./src/server/client.cpp ./src/Sprite.cpp ./src/PingPong.cpp ./src/Rectangle.cpp -lboost_system -lboost_program_options -lallegro -lallegro_primitives -lallegro_font -lallegro_ttf $(CPPFLAGS) -o $(EXECUTABLE)

maPong_with_server_win:
	прописать путь к бинарникам и бииблам Boost
	g++ $(CFLAGS) ./src/maPong.cpp ./src/server/server.cpp ./src/server/client.cpp ./src/Sprite.cpp ./src/PingPong.cpp ./src/Rectangle.cpp -lboost_system -lboost_program_options-5.0.10-monolith-md -lallegro -lallegro_primitives-5.0.10-md -lallegro_font-5.0.10-md -lallegro_ttf-5.0.10-md $(CPPFLAGS) -o $(EXECUTABLE)


run:
	./bin/$(EXECUTABLE)

clean:
	rm ./bin/$(EXECUTABLE) ./bin/*.o

#http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
#IDIR =../include
#_DEPS = hellomake.h
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
#test:
#	echo $(DEPS) # ../include/hellomake.h

