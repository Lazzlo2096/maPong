//==================
//#include <iostream>
#include <string>

#include <allegro5/allegro.h>
// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_ttf.h>

#include "alx.hpp"

// #include "Sprite.h"
#include "PingPongItems.h"

#include "GameInterfaceElements/Menu.hpp"
#include "MainScene.hpp"
//==================

int yourScore = 0;
int enemyScore = 0;
string yourScore_str = to_string(yourScore);
string enemyScore_str = to_string(enemyScore);

const float FPS = 60;
// const int BOUNCER_SIZE = 32;

void allegro_init()
{

}


void qwerty()
{

	

}


class MyGame
{

	alx::Timer timer;
	alx::EventQueue eventQueue; // нужно сначало init allegro

	mainScene myMainScene;

public:
	MyGame() :
		timer(1./FPS)
		//,eventQueue()
	{};
	
	~MyGame(){};
	



void init()
{


	//Мб начиная от сюдова всё запихнуть в объект сцены
	alx::Display display(SCREEN_W, SCREEN_H);
	display.setWindowTitle("Ma Pong :-)");

	//--------------
	
	//alx::Timer timer(1./FPS);
	alx::UserEventSource ues;

	//bind the resources to the event queue
	eventQueue << alx::Keyboard::getEventSource() 
	/*<< Mouse::getEventSource()*/ << display << timer << ues;
	//--------------

	
	myMainScene.init();

	/*
	cout << ball.position.getX() << endl;
	cout << ball.position.getY() << endl;
	*/

	// float offset = 5.5;
	// ALLEGRO_COLOR color_orange = al_map_rgb(255, 0, 0);

	/*al_draw_rectangle(
		offset, 
		offset, 
		height+offset, 
		width+offset, 
		color_orange,
		1 );*/

	//ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	//event_queue = al_create_event_queue();
 
 	//Запихнуть в метод run() сцены
	//event loop // event обработчик

}

void run()
{
	
	bool loop = true;
	bool is_redraw = false;
	timer.start();
	while (loop)
	{

		// ALLEGRO_EVENT ev;
		// al_wait_for_event(event_queue, &ev);

		// if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				// break;
		// }

		// if( al_is_event_queue_empty(event_queue)) {
		if (is_redraw and eventQueue.isEmpty()) {

			myMainScene.calcAndDrawFrame();

			al_flip_display();

			is_redraw = false;
		}

		//wait for event
		alx::Event event = eventQueue.waitForEvent();

		//process event
		switch (event.getType()) {
			
			case ALLEGRO_EVENT_KEY_DOWN: //key down pressed
					switch (event.getKeyboardKeycode()) {

						//end the loop
						case ALLEGRO_KEY_ESCAPE:
								loop = false;
							break;
					}
				break;

			case ALLEGRO_EVENT_KEY_CHAR:
				switch (event.getKeyboardKeycode()) {

							// ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT,
							// ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN,


					case ALLEGRO_KEY_DOWN :
							myMainScene.onKeyDown();
						break;

					case ALLEGRO_KEY_UP :
							myMainScene.onKeyUp();
						break;
				}
				break;

			//mouse
			/*case ALLEGRO_EVENT_MOUSE_AXES:
					paddle.position.setX(std::max(0, 
						std::min(event.getMouseX() - 
						paddle.bitmap.getWidth()/2, display.getWidth() - 
						paddle.bitmap.getWidth())));
					if (ball.velocity == Point<int>(0, 0)) {
							ball.position.setX(paddle.position.getX() + 
								paddle.bitmap.getWidth()/2 - 
								ball.bitmap.getWidth()/2);
					}
					break;

			//button down
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
					// if (ball.velocity == Point<int>(0, 0)) {
							// ball.velocity.set(2, -2);
							ball.sprite_color = al_map_rgb(0, 255, 0);
							cout << "hello" << endl;
					// }
					break;
					*/

			//timer
			case ALLEGRO_EVENT_TIMER:
				if (event.getTimer() == timer) {
					is_redraw = true;
					// updateLogic(); //???????????????????????????????????
				}
				break;

			//display close
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				loop = false;
				break;

		}// switch end
	}// while (loop)


	// al_flip_display(); //Отрисовка
	
	// al_rest(5.0); //Задержка в секундах
	// al_destroy_display(display);

}

};


int main(int argc, char **argv)
{

al_init();
	al_install_keyboard();
	
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon(); // initialize the ttf (True Type Font) addon

	al_init_primitives_addon(); //Исправляет assertion 'addon_initialized' failed

	//Мб начиная от сюдова всё запихнуть в объект сцены
	alx::Display display(SCREEN_W, SCREEN_H);
	display.setWindowTitle("Ma Pong :-)");

	//--------------

	alx::Timer timer;
	alx::EventQueue eventQueue; // нужно сначало init allegro
	
	//alx::Timer timer(1./FPS);
	alx::UserEventSource ues;

	//bind the resources to the event queue
	eventQueue << alx::Keyboard::getEventSource() 
	/*<< Mouse::getEventSource()*/ << display << timer << ues;
	//--------------


	mainScene myMainScene;

	
	myMainScene.init();



	/*
	cout << ball.position.getX() << endl;
	cout << ball.position.getY() << endl;
	*/

	// float offset = 5.5;
	// ALLEGRO_COLOR color_orange = al_map_rgb(255, 0, 0);

	/*al_draw_rectangle(
		offset, 
		offset, 
		height+offset, 
		width+offset, 
		color_orange,
		1 );*/

	//ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	//event_queue = al_create_event_queue();
 
 	//Запихнуть в метод run() сцены
	//event loop // event обработчик

	
	bool loop = true;
	bool is_redraw = false;
	timer.start();
	while (loop)
	{

		// ALLEGRO_EVENT ev;
		// al_wait_for_event(event_queue, &ev);

		// if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				// break;
		// }

		// if( al_is_event_queue_empty(event_queue)) {
		if (is_redraw and eventQueue.isEmpty()) {

			myMainScene.calcAndDrawFrame();

			al_flip_display();

			is_redraw = false;
		}

		//wait for event
		alx::Event event = eventQueue.waitForEvent();

		//process event
		switch (event.getType()) {
			
			case ALLEGRO_EVENT_KEY_DOWN: //key down pressed
					switch (event.getKeyboardKeycode()) {

						//end the loop
						case ALLEGRO_KEY_ESCAPE:
								loop = false;
							break;
					}
				break;

			case ALLEGRO_EVENT_KEY_CHAR:
				switch (event.getKeyboardKeycode()) {

							// ALLEGRO_KEY_LEFT, ALLEGRO_KEY_RIGHT,
							// ALLEGRO_KEY_UP, ALLEGRO_KEY_DOWN,


					case ALLEGRO_KEY_DOWN :
							myMainScene.onKeyDown();
						break;

					case ALLEGRO_KEY_UP :
							myMainScene.onKeyUp();
						break;
				}
				break;

			//mouse
			/*case ALLEGRO_EVENT_MOUSE_AXES:
					paddle.position.setX(std::max(0, 
						std::min(event.getMouseX() - 
						paddle.bitmap.getWidth()/2, display.getWidth() - 
						paddle.bitmap.getWidth())));
					if (ball.velocity == Point<int>(0, 0)) {
							ball.position.setX(paddle.position.getX() + 
								paddle.bitmap.getWidth()/2 - 
								ball.bitmap.getWidth()/2);
					}
					break;

			//button down
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
					// if (ball.velocity == Point<int>(0, 0)) {
							// ball.velocity.set(2, -2);
							ball.sprite_color = al_map_rgb(0, 255, 0);
							cout << "hello" << endl;
					// }
					break;
					*/

			//timer
			case ALLEGRO_EVENT_TIMER:
				if (event.getTimer() == timer) {
					is_redraw = true;
					// updateLogic(); //???????????????????????????????????
				}
				break;

			//display close
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				loop = false;
				break;

		}// switch end
	}// while (loop)


	// al_flip_display(); //Отрисовка
	
	// al_rest(5.0); //Задержка в секундах
	// al_destroy_display(display);
	//==============


	allegro_init();

	qwerty();

	/*MyGame maPong;

	maPong.init();

	maPong.run();*/

	return 0;
}