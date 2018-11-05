#include "Rectangle.h"

Rectangle::Rectangle(const Point<int> &pos, int _width, int _hight):
		Sprite(pos, _width, _hight){};

// Rectangle::~Rectangle(){};


void Rectangle::draw()
{
	Point<int> _position = position - makePoint(width/2, hight/2);
	// Point<int> _position = position ;

	// al_draw_rectangle(
	al_draw_filled_rectangle(
		_position.getX(), 
		_position.getY(), 
		width+_position.getX(), 
		hight+_position.getY(), 
		rectangle_color );

}

//ALLEGRO_COLOR getRectangle_color(){ return rectangle_color; }

void Rectangle::setRectangle_color(ALLEGRO_COLOR _rectangle_color)
	{ rectangle_color = _rectangle_color; }
