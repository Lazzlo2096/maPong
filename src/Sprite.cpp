#include "Sprite.h"


Sprite::Sprite(const Point<int> &pos, int _width, int _hight) : 
	position(pos), width(_width), hight(_hight) {}

//Sprite(const Point<int> &pos) : position(pos) {
//}

Sprite::~Sprite(){};


Point<int> Sprite::getPosition() const
	{ return position; }/*const метод т.к.
юзаеться в конст obj в методе Ball::colision*/

//void setPosition(Point<int> _position){ position = _position; }

//Point<int> getVelocity(){ return velocity; }
void Sprite::setVelocity(Point<int> _velocity){ velocity = _velocity; }

int Sprite::getHight() const { return hight; }
int Sprite::getWidth() const { return width; }

/*Sprite(const Point<int> &pos, const Bitmap &bmp) 
	: position(pos), bitmap(bmp) {
}

//draws the bitmap
void draw() const {
		bitmap.draw(position.getX(), position.getY());
}
*/

//get rect
Rect<int> Sprite::getRect() const 
{

	Point<int> _position = - makePoint(width/2, hight/2) + position;
	return Rect<int>(_position, makeSize(width, hight));
}

/*
void Sprite::draw() {

	Point<int> _position = position - makePoint(width/2, hight/2);
	// Point<int> _position = position ;

	// al_draw_rectangle(
	al_draw_filled_rectangle(
		_position.getX(), 
		_position.getY(), 
		width+_position.getX(), 
		hight+_position.getY(), 
		sprite_color );

}
*/
