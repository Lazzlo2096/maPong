#pragma once

#include <iostream>
#include <string>
#include <allegro5/allegro.h>

// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_ttf.h>

#include "alx.hpp"

using namespace std;
//using namespace alx;

const int SCREEN_W = 640*1.25;
const int SCREEN_H = 480;

extern int yourScore;
extern int enemyScore;
extern string yourScore_str;
extern string enemyScore_str;

class Sprite
{
protected:

	int width;
	int hight; //to Point?
	// а что если я хочу чтобы качание осязалось как круг?

	alx::Point<int> position;
	alx::Point<int> velocity;

public:

	Sprite(const alx::Point<int> &pos, int _width, int _hight);

	//Sprite(const Point<int> &pos) : position(pos) {}

	/*
	Sprite(const Point<int> &pos, const Bitmap &bmp) :
		position(pos),
		bitmap(bmp) 
	{}
	*/

	virtual ~Sprite();

	alx::Point<int> getPosition() const;/*const метод т.к.
	юзаеться в конст obj в методе Ball::colision*/
	//void setPosition(Point<int> _position){ position = _position; }

	//Point<int> getVelocity(){ return velocity; }
	void setVelocity(alx::Point<int> _velocity);

	int getHight() const;
	int getWidth() const;

	alx::Rect<int> getRect() const;

	virtual void draw() = 0;
	/*
	//draws the bitmap
	void draw() const {
			bitmap.draw(position.getX(), position.getY());
	};
	*/

	// hitTest(const Sprite& sprite){}; // getRect() ??
};