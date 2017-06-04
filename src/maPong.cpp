
#include <iostream>
#include <string>
#include <allegro5/allegro.h>

// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_ttf.h>

#include "alx.hpp"

#include "./server/helpPage.h" //struct EnpPoint, parseArgs()
// #include "Sprite.h"
#include "PingPong.h"

using namespace std;
using namespace alx;

int yourScore = 0;
int evilScore = 0;

const float FPS = 60;
// const int BOUNCER_SIZE = 32;

void drawPingPongBackground(ALLEGRO_FONT *font){

	ALLEGRO_COLOR color_line = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR color_score = al_map_rgb(255, 255, 255);

	// Color background_color(40,40,40);
	// al_clear_to_color( background_color );
	al_clear_to_color( al_map_rgb(40,40,40) ); //заливка фона в цвет RGB

	int interval = 50;
	int indentation = 10;

	al_draw_text(
		font,
		color_score,
		SCREEN_W/2 + interval,
		0+indentation,
		ALLEGRO_ALIGN_CENTRE,
		to_string(yourScore).c_str()
	);

	al_draw_text(
		font,
		color_score,
		SCREEN_W/2 - interval,
		0+indentation,
		ALLEGRO_ALIGN_CENTRE,
		to_string(evilScore).c_str()
	);

	// al_draw_text(font, al_map_rgb(255,255,255), 640/2, (480/4),
				// ALLEGRO_ALIGN_CENTRE, score.c_str());

	//draw outline
	int hi_line = 20;
	int wi_line = 10;
	int gap = 10;
	for ( int hi = 0; hi < SCREEN_H ; hi+=gap+hi_line){
		al_draw_filled_rectangle(
				SCREEN_W/2 - wi_line/2, 
				0+hi, 
				SCREEN_W/2 + wi_line/2, 
				hi_line+hi, 
				color_line );
	}
}

class mainScene{

	const float board_hight = 25;
	const float board_width = 150;

	Ball ball;
	// ball.sprite_color = al_map_rgb(255, 0, 0);

	/*Board myBoard( makePoint( SCREEN_W-75-25/2 , SCREEN_H/2-150/2), 25,
	 150 );*/
	Board myBoard;

	Board evilBoard;

	ALLEGRO_FONT *font;

public:

	mainScene():
		ball( makePoint(SCREEN_W/2, SCREEN_H/2), 25, 25 ),
		myBoard( makePoint( SCREEN_W-75 , SCREEN_H/2), board_hight, board_width ),
		evilBoard( makePoint( 75 , SCREEN_H/2), board_hight, board_width )	
	{

		// font = al_load_ttf_font("Smirnof.ttf",72,0 );
		font = al_load_ttf_font("./data/04B_03__.TTF",72,0 );
		// ALLEGRO_FONT *font = al_load_bitmap_font("a4_font.tga");
		if (!font){
      		fprintf(stderr, "Could not load './data/04B_03__.TTF'.\n");
     		 //return -1;
   		}
	};

	~mainScene(){};

	void onInit(){

		ball.setVelocity( makePoint(1, 1) );
		myBoard.setVelocity( makePoint(5, 5) );
		// evilBoard.velocity() = makePoint(5, 5); //Багает при этом значении
		evilBoard.setVelocity( makePoint(1, 1) );

	};

	void onRun(){

		drawPingPongBackground(font);

		ball.draw();
		myBoard.draw();
		evilBoard.draw();

		//-------
		ball.fly();
		ball.collision( myBoard );
		ball.collision( evilBoard );

		evilBoard.autoCatch( ball.getPosition() );
		//-------

	}

	void onKeyDown(){ myBoard.move_down(); }
	void onKeyUp(){ myBoard.move_up(); }
};

int main(int argc, char **argv){

	struct EnpPoint ep = parseArgs(argc, argv);
	
	al_init();
	al_install_keyboard();
	
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon


	Display display(SCREEN_W, SCREEN_H);
	display.setWindowTitle("Ma Pong :-)");

	//--------------
	EventQueue eventQueue;
	Timer timer(1./FPS);
	UserEventSource ues;

	//bind the resources to the event queue
	eventQueue << Keyboard::getEventSource() 
	/*<< Mouse::getEventSource()*/ << display << timer << ues;
	//--------------


	mainScene myMainScene;
	myMainScene.onInit();



	// cout << ball.position.getX() << endl;
	// cout << ball.position.getY() << endl;
	
// 

	// float offset = 5.5;
	// ALLEGRO_COLOR color_orange = al_map_rgb(255, 0, 0);


	/*al_draw_rectangle(
		offset, 
		offset, 
		hight+offset, 
		width+offset, 
		color_orange,
		1 );*/





	//ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	//event_queue = al_create_event_queue();
 
	//event loop
	timer.start();
	bool loop = true;
	bool redraw = false;
	while(loop)
	{

		// ALLEGRO_EVENT ev;
		// al_wait_for_event(event_queue, &ev);

		// if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				// break;
		// }

		// if( al_is_event_queue_empty(event_queue)) {
		if (redraw && eventQueue.isEmpty()) {

			myMainScene.onRun();

			al_flip_display();

			redraw = false;
		}


		//wait for event
		Event event = eventQueue.waitForEvent();

		//process event
		switch (event.getType()) {
			//key down
			case ALLEGRO_EVENT_KEY_DOWN:
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
					redraw = true;
					// updateLogic(); //???????????????????????????????????
				}
				break;

			//display close
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				loop = false;
				break;

		}//switch end
 }




	// al_flip_display(); //Отрисовка
	
	// al_rest(5.0); //Задержка в секундах
	// al_destroy_display(display);




	 return 0;
}
