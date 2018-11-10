#pragma once

#include <iostream>
#include <string>

#include <allegro5/allegro.h>
// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_ttf.h>

#include "alx.hpp"
#include "Sprite.h"

using namespace std;
//using namespace alx;


class Rectangle: public Sprite
{
protected:

	ALLEGRO_COLOR rectangle_color = al_map_rgb(255, 255, 255);

public:

	Rectangle(const alx::Point<int> &pos, int _width, int _hight);
	
	// ~Rectangle(); //? on and virt?

	//ALLEGRO_COLOR getSprite_color(){ return sprite_color; }
	void setRectangle_color(ALLEGRO_COLOR _sprite_color);

	void draw();

};