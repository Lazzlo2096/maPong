#pragma once

//=========================
//#include <iostream>
//#include <string>
//#include <allegro5/allegro.h>

// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_ttf.h>

//#include "alx.hpp"

// #include "Sprite.h"
//#include "PingPongItems.h"
//=========================

namespace GameInterfaceElements{

class Menu
{
	const int MENU_WIDTH = 200;
	// MENU_HEIGHT = 200;
	const int MENU_ITEM_HEIGHT = 40;
	const int MENU_PADDING = 10;

	alx::Point<int> menuPlace;

	vector<string> menu_items;

	int menuItemsNum; //= menu_items.size(); // size() трудоёмкий метод

public:
	Menu(){
		menu_items.push_back("New game"); //Можно ли оптимизировать чтобы стразу были встроены?
		menu_items.push_back("Online game");
		menu_items.push_back("Exit");

		menuItemsNum = menu_items.size(); // size() трудоёмкий метод

		menuPlace = alx::makePoint(
				SCREEN_W/2-MENU_WIDTH/2,
				SCREEN_H/2-(MENU_PADDING+(MENU_ITEM_HEIGHT)*menuItemsNum)
			);
	};

	void drawMenu(){

		auto drawShadesBackground = [](){
			al_draw_filled_rectangle(
				0, 
				0, 
				SCREEN_W, 
				SCREEN_H, 
				al_map_rgba_f(0.f, 0.f, 0.f, 0.45f));
		};

		drawShadesBackground();

		// cout << menuItemsNum << endl;

		ALLEGRO_COLOR menu_color = al_map_rgba_f(0.f, 0.f, 0.f, 1.f);
		ALLEGRO_COLOR item_color = al_map_rgba_f(1.f, 1.f, 1.f, 1.f);
		ALLEGRO_COLOR menu_font_color = al_map_rgba_f(0.f, 0.f, 0.f, 1.f);

		al_draw_filled_rectangle(
			menuPlace.getX(), 
			menuPlace.getY(), 
			menuPlace.getX()+MENU_WIDTH, 
			menuPlace.getY()+MENU_PADDING+(MENU_ITEM_HEIGHT)*menuItemsNum, 
			menu_color
		);

		ALLEGRO_FONT *font = al_load_ttf_font("./data/04B_03__.TTF",30,0 );

		for(int i=0; i!=menuItemsNum; i++ ){
			// cout << i << endl;
			al_draw_filled_rectangle(
				menuPlace.getX()+MENU_PADDING,
				menuPlace.getY()+MENU_PADDING+MENU_ITEM_HEIGHT*i, 
				menuPlace.getX()+MENU_WIDTH-MENU_PADDING, 
				menuPlace.getY()+MENU_ITEM_HEIGHT+MENU_ITEM_HEIGHT*i, 
				item_color
			);

			al_draw_text(
				font,
				menu_font_color,
				menuPlace.getX()+MENU_PADDING+MENU_WIDTH/2,
				menuPlace.getY()+MENU_PADDING+MENU_ITEM_HEIGHT*i,
				ALLEGRO_ALIGN_CENTRE,
				menu_items[i].c_str()
			);
		}
	};
};

} //namespace GameInterfaceElements