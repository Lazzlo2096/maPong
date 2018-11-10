#include "Sprite.h"


Sprite::Sprite(const alx::Point<int> &pos, int _width, int _hight) : 
	position(pos), width(_width), hight(_hight) {}

//Sprite(const alx::Point<int> &pos) : position(pos) {
//}

Sprite::~Sprite(){};


alx::Point<int> Sprite::getPosition() const
	{ return position; }/*const метод т.к.
юзаеться в конст obj в методе Ball::colision*/

//void setPosition(alx::Point<int> _position){ position = _position; }

//alx::Point<int> getVelocity(){ return velocity; }
void Sprite::setVelocity(alx::Point<int> _velocity){ velocity = _velocity; }

int Sprite::getHight() const { return hight; }
int Sprite::getWidth() const { return width; }

/*Sprite(const alx::Point<int> &pos, const Bitmap &bmp) 
	: position(pos), bitmap(bmp) {
}

//draws the bitmap
void draw() const {
		bitmap.draw(position.getX(), position.getY());
}
*/

//get rect
alx::Rect<int> Sprite::getRect() const 
{

	alx::Point<int> _position = - alx::makePoint(width/2, hight/2) + position;
	return alx::Rect<int>(_position, alx::makeSize(width, hight));
}

/*
void Sprite::draw() {

	alx::Point<int> _position = position - alx::makePoint(width/2, hight/2);
	// alx::Point<int> _position = position ;

	// al_draw_rectangle(
	al_draw_filled_rectangle(
		_position.getX(), 
		_position.getY(), 
		width+_position.getX(), 
		hight+_position.getY(), 
		sprite_color );

}
*/
