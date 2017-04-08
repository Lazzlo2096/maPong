
#include <iostream>
#include <string>
#include <allegro5/allegro.h>

// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_ttf.h>

#include "alx.hpp"

using namespace std;
using namespace alx;


const float FPS = 60;
const int SCREEN_W = 640*1.25;
const int SCREEN_H = 480;
// const int BOUNCER_SIZE = 32;

ALLEGRO_FONT *font;

int yourScore = 0;
int evilScore = 0;

void drawBackground(){

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


//a sprite class
class Sprite {

protected:

	int hight;
	int width;

	Point<int> position;

	Point<int> velocity;

	// Bitmap bitmap;

	// ALLEGRO_COLOR sprite_color = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR sprite_color = al_map_rgb(255, 255, 255);

public:

	Point<int> getPosition() const { return position; } /*const метод т.к.
	юзаеться вконст obj в методе Ball::colision*/
	void setPosition(Point<int> _position){ position = _position; }

	Point<int> getVelocity(){ return velocity; }
	void setVelocity(Point<int> _velocity){ velocity = _velocity; }

	ALLEGRO_COLOR getSprite_color(){ return sprite_color; }
	void setSprite_color(ALLEGRO_COLOR _sprite_color){ sprite_color = _sprite_color; }


	int getHight() const { return hight; }
	int getWidth() const { return width; }


	/*Sprite(const Point<int> &pos, const Bitmap &bmp) 
		: position(pos), bitmap(bmp) {
	}

	//draws the bitmap
	void draw() const {
			bitmap.draw(position.getX(), position.getY());
	}
*/
	
	//get rect
	Rect<int> getRect() const {

		Point<int> _position = - makePoint(width/2, hight/2) + position;
		return Rect<int>(_position, makeSize(width, hight));
	}

	Sprite(const Point<int> &pos, int _width, int _hight) : 
		position(pos), hight(_hight), width(_width) {
	}

	Sprite(const Point<int> &pos) : position(pos) {
	}


	void draw() {

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

	// hitTest(const Sprite& sprite){ // getRect() ?? 
	// }
	


};

class Ball : public Sprite
{

	int color = 0;
public:



	// Ball();
	~Ball(){};

	Ball(const Point<int> &pos, int _width, int _hight) 
		: Sprite(pos, _width, _hight) {}


	void setRandomColor(){

		int i = color;
		setSprite_color( al_map_rgb((i%3==0?255:0), (i%3==1?255:0), (i%3==2?255:0)) );

		color++;

	}



	void fly() {
	/*
	Проверка на столкновение с краями идеёт после прибавления к координатам скорости.
	Это может вызвать глюк, когда отталкивание
	совершаеться за стенами, при большом velocity.
	*/

		// setRandomColor();

		//проверка на столкновение с краями

		if (position.getY() <= 0+hight/2 or position.getY() >= SCREEN_H-hight/2)
			velocity.setY( -velocity.getY() );

		if (position.getX() >= SCREEN_W-width/2){
			position = makePoint(SCREEN_W/2, SCREEN_H/2);
			evilScore++;
		}

		if (position.getX() <= 0+width/2){
			position = makePoint(SCREEN_W/2, SCREEN_H/2);
			yourScore++;
		}


		position += velocity;
	}

	//check collision between two sprites
	// bool collision(const Sprite& obj) {
	void collision(const Sprite& obj) {
		
		// if( getRect().intersects(obj.getRect()) ){
		if( abs(position.getX()-obj.getPosition().getX()) == width/2+obj.getWidth()/2 and
			(abs(position.getY()-obj.getPosition().getY()) < hight/2+obj.getHight()/2 ) )
		{
			// setRandomColor();
			//Баги, баги, эти баги ВЕЗДЕ!
			// velocity.setX( -abs(velocity.getX()+1.5) ); 
			velocity.setX( -velocity.getX() ); 
		}
		else if( 
			abs(position.getY()-obj.getPosition().getY()) == hight/2+obj.getHight()/2  and
			(abs(position.getX()-obj.getPosition().getX()) < width/2+obj.getWidth()/2 ) 
			)
			velocity.setY( -velocity.getY() );
		// else

	}
		
};


class Board : public Sprite
{
public:



	// Board();
	~Board(){};

	Board(const Point<int> &pos, int _width, int _hight) 
		: Sprite(pos, _width, _hight) {
	}




	void move_down() {

		//проверка на столкновение с краями
		// if (position.getX() >= SCREEN_W or position.getX() <=0)
			// velocity.setX( -velocity.getX() );


		if (position.getY()+velocity.getY() <= SCREEN_H-hight/2)
			// velocity.setY( -velocity.getY() );
			position.setY( position.getY()+velocity.getY() ) ;
		else
			position.setY( SCREEN_H-hight/2 );
	}

	void move_up() {

		//проверка на столкновение с краями
		// if (position.getX() >= SCREEN_W or position.getX() <=0)
			// velocity.setX( -velocity.getX() );

		if (position.getY()-velocity.getY() >= 1+hight/2)
			// velocity.setY( -velocity.getY() );
			position.setY( position.getY()-velocity.getY() ) ;
		else
			position.setY( 1+hight/2 );
	}



	void autoCatch(Point<int> point){

		if (position.getY() > point.getY())
			move_up();
		else if (position.getY() < point.getY())
			move_down();


	}


		
};


int main(int argc, char **argv){

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


	float hight = 25;
	float width = 25;


	Ball ball( makePoint(SCREEN_W/2, SCREEN_H/2), hight, width );
	ball.setVelocity( makePoint(1, 1) );
	// ball.sprite_color = al_map_rgb(255, 0, 0);

	/*Board myBoard( makePoint( SCREEN_W-75-25/2 , SCREEN_H/2-150/2), 25,
	 150 );*/
	Board myBoard( makePoint( SCREEN_W-75 , SCREEN_H/2), 25, 150 );
	myBoard.setVelocity( makePoint(5, 5) );
	



	Board evilBoard( makePoint( 75 , SCREEN_H/2), 25, 150 );
	// evilBoard.velocity() = makePoint(5, 5); //Багает при этом значении
	evilBoard.setVelocity( makePoint(1, 1) );




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



	// font = al_load_ttf_font("Smirnof.ttf",72,0 );
	font = al_load_ttf_font("04B_03__.TTF",72,0 );
	// ALLEGRO_FONT *font = al_load_bitmap_font("a4_font.tga");
	if (!font){
      fprintf(stderr, "Could not load 'pirulen.ttf'.\n");
      return -1;
   }

	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	event_queue = al_create_event_queue();
 
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

			drawBackground();

			ball.draw();
			myBoard.draw();
			evilBoard.draw();

			//-------
			ball.fly();
			ball.collision( myBoard );
			ball.collision( evilBoard );

			evilBoard.autoCatch( ball.getPosition() );
			//-------

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
							myBoard.move_down();
						break;

					case ALLEGRO_KEY_UP :
							myBoard.move_up();
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
