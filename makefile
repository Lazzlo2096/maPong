.PTHONY: all windows run clean

all:
	g++ -I ./ALX/include/ ./src/maPong.cpp ./src/Sprite.cpp ./src/PingPong.cpp ./src/Rectangle.cpp -lallegro -lallegro_primitives -lallegro_font -lallegro_ttf -std=c++11 -o maPong
	#-lallegro_image -lallegro_dialog
	
windows:
	g++ -I ./ALX/include/ ./src/maPong.cpp ./src/Sprite.cpp ./src/PingPong.cpp ./src/Rectangle.cpp -lallegro-5.0.10-monolith-md -lallegro_primitives-5.0.10-md -lallegro_font-5.0.10-md -lallegro_ttf-5.0.10-md -std=c++11 -o maPong

windows4prof:
	g++ -I ./ALX/include/ ./src/maPong.cpp ./src/Sprite.cpp ./src/PingPong.cpp ./src/Rectangle.cpp -lallegro-5.0.10-monolith-md -lallegro_primitives-5.0.10-md -lallegro_font-5.0.10-md -lallegro_ttf-5.0.10-md -std=c++11 -pg -o maPong

run:
	./maPong

clean:
	rm ./maPong