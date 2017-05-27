#pragma once

#include <iostream>
#include <string>
#include <allegro5/allegro.h>

// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_ttf.h>

#include "alx.hpp"

using namespace std;
using namespace alx;


const int SCREEN_W = 640*1.25;
const int SCREEN_H = 480;


extern int yourScore;
extern int evilScore;


class Sprite {

protected:

	int width;
	int hight;

	Point<int> position;

	Point<int> velocity;

	// Bitmap bitmap;

	// ALLEGRO_COLOR sprite_color = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR sprite_color = al_map_rgb(255, 255, 255);

public:

	Point<int> getPosition() const;/*const метод т.к.
	юзаеться в конст obj в методе Ball::colision*/
	//void setPosition(Point<int> _position){ position = _position; }

	//Point<int> getVelocity(){ return velocity; }
	void setVelocity(Point<int> _velocity);

	//ALLEGRO_COLOR getSprite_color(){ return sprite_color; }
	void setSprite_color(ALLEGRO_COLOR _sprite_color);


	int getHight() const;
	int getWidth() const;


	/*Sprite(const Point<int> &pos, const Bitmap &bmp) 
		: position(pos), bitmap(bmp) {
	}

	//draws the bitmap
	void draw() const {
			bitmap.draw(position.getX(), position.getY());
	}
*/
	
	//get rect
	Rect<int> getRect() const;

	Sprite(const Point<int> &pos, int _width, int _hight);

	//Sprite(const Point<int> &pos) : position(pos) {
	//}


	void draw();

	// hitTest(const Sprite& sprite){ // getRect() ?? 
	// }
	


};