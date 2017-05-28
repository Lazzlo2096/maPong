#pragma once

#include <iostream>
#include <string>
#include <allegro5/allegro.h>

// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_ttf.h>

#include "Sprite.h"

#include "alx.hpp"

using namespace std;
using namespace alx;




class Ball : public Sprite
{
	int color = 0;

public:


	// Ball();
	~Ball();

	Ball(Point<int> pos, int _width, int _hight);
	Ball(int pos_x, int pos_y, int _width, int _hight);

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


class Board : public Sprite
{
public:

	// Board();
	~Board();

	Board(const Point<int> &pos, int _width, int _hight);

	void move_down();

	void move_up();

	void autoCatch(Point<int> point);
		
};
