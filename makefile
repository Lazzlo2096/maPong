.PTHONY: all windows run clean

all:
	g++ -I ./ALX/include/ ./src/maPong.cpp ./src/Sprite.cpp ./src/PingPong.cpp ./src/Rectangle.cpp -lallegro -lallegro_primitives -lallegro_font -lallegro_ttf -std=c++11 -o maPong
	#-lallegro_image -lallegro_dialog

maPong_with_server_lin:
	g++ -I ./ALX/include/ ./src/maPong.cpp ./src/server/server.cpp ./src/server/client.cpp ./src/Sprite.cpp ./src/PingPong.cpp ./src/Rectangle.cpp -lboost_system -lboost_program_options -lallegro -lallegro_primitives -lallegro_font -lallegro_ttf -std=c++11 -o maPong

maPong_with_server_win:
	#прописать путь к бинарникам и бииблам Boost
	g++ -I ./ALX/include/ ./src/maPong.cpp ./src/server/server.cpp ./src/server/client.cpp ./src/Sprite.cpp ./src/PingPong.cpp ./src/Rectangle.cpp -lboost_system -lboost_program_options-5.0.10-monolith-md -lallegro -lallegro_primitives-5.0.10-md -lallegro_font-5.0.10-md -lallegro_ttf-5.0.10-md -std=c++11 -o maPong

windows:
	g++ -I ./ALX/include/ ./src/maPong.cpp ./src/Sprite.cpp ./src/PingPong.cpp ./src/Rectangle.cpp -lallegro-5.0.10-monolith-md -lallegro_primitives-5.0.10-md -lallegro_font-5.0.10-md -lallegro_ttf-5.0.10-md -std=c++11 -o maPong

run:
	./maPong

clean:
	rm ./maPong