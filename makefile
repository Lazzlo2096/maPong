All:
	g++ -I ./src/ALX/include/ ./src/maPong.cpp ./src/Sprite.cpp ./src/PingPong.cpp ./src/Rectangle.cpp -lboost_program_options -lallegro -lallegro_primitives -lallegro_font -lallegro_ttf -std=c++11 -o maPong
	#-lallegro_image -lallegro_dialog

run:
	./maPong

clean:
	rm ./maPong