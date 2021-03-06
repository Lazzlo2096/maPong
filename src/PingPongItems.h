#pragma once

#include <iostream>
#include <string>

#include <allegro5/allegro.h>
// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_ttf.h>

#include "alx.hpp"
#include "Rectangle.h"

using namespace std;
//using namespace alx;

namespace maPong{


class Ball : public Rectangle
{
	int color = 0;

public:

	// Ball();
	~Ball();

	Ball(alx::Point<int> pos, int _width, int _hight);
	// Ball(int pos_x, int pos_y, int _width, int _hight);

	void setRandomColor();

	void fly();
	/*
	Проверка на столкновение с краями идеёт после прибавления к координатам скорости.
	Это может вызвать глюк, когда отталкивание
	совершаеться за стенами, при большом velocity.
	*/


	//check collision between two sprites
	// bool collision(const Sprite& obj)
	void collision(const Sprite& obj);
		
};


class Board : public Rectangle
{
public:

	// Board();
	~Board();

	Board(const alx::Point<int> &pos, int _width, int _hight);

	void move_down();

	void move_up();

	void autoCatch(alx::Point<int> point);
		
};

}//namespace maPong