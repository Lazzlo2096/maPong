
#include <iostream>
#include <allegro5/allegro.h>

#include "alx.hpp"

using namespace std;
using namespace alx;


// const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
// const int BOUNCER_SIZE = 32;


//a sprite class
class Sprite {

public:


    int hight;
    int width;

    Point<int> position;

    Point<int> velocity;

    // Bitmap bitmap;


    /*Sprite(const Point<int> &pos, const Bitmap &bmp) : position(pos), bitmap(bmp) {
    }

    //draws the bitmap
    void draw() const {
        bitmap.draw(position.getX(), position.getY());
    }

    //get rect
    Rect<int> getRect() const {
        return Rect<int>(position, bitmap.getSize());
    }*/

    Sprite(const Point<int> &pos, int _width, int _hight) : position(pos), hight(_hight), width(_width) {
    }

    Sprite(const Point<int> &pos) : position(pos) {
    }


    // ALLEGRO_COLOR sprite_color = al_map_rgb(255, 0, 0);
    ALLEGRO_COLOR sprite_color = al_map_rgb(255, 255, 255);


    void draw() {

        // al_draw_rectangle(position.getX(), position.getY(), width+position.getX(), hight+position.getY(), sprite_color, 1);
        al_draw_filled_rectangle(position.getX(), position.getY(), width+position.getX(), hight+position.getY(), sprite_color);
    
    }


};

class Ball : public Sprite
{

    int color = 0;
public:



    // Ball();
    ~Ball(){};

    Ball(const Point<int> &pos, int _width, int _hight) : Sprite(pos, _width, _hight) {
    }


    void setRandomColor(){

        int i = color;
            sprite_color = al_map_rgb((i%3==0?255:0), (i%3==1?255:0), (i%3==2?255:0));

        color++;

    }



    void fly() {

        // setRandomColor();

        //проверка на столкновение с краями
        if (position.getX() >= SCREEN_W or position.getX() <=0)
            velocity.setX( -velocity.getX() );

        if (position.getY() >= SCREEN_H or position.getY() <=0)
            velocity.setY( -velocity.getY() );

        position += velocity;
    }


    
};


class Board : public Sprite
{
public:



    // Board();
    ~Board(){};

    Board(const Point<int> &pos, int _width, int _hight) : Sprite(pos, _width, _hight) {
    }




    void move_down() {

        //проверка на столкновение с краями
        // if (position.getX() >= SCREEN_W or position.getX() <=0)
            // velocity.setX( -velocity.getX() );


        if (position.getY()+velocity.getY() <= SCREEN_H-hight)
            // velocity.setY( -velocity.getY() );
            position.setY( position.getY()+velocity.getY() ) ;
        else
            position.setY( SCREEN_H-hight );
    }

    void move_up() {

        //проверка на столкновение с краями
        // if (position.getX() >= SCREEN_W or position.getX() <=0)
            // velocity.setX( -velocity.getX() );

        if (position.getY()-velocity.getY() >= 1)
            // velocity.setY( -velocity.getY() );
            position.setY( position.getY()-velocity.getY() ) ;
        else
            position.setY( 1 );
    }


    
};


int main(int argc, char **argv){

    al_init();
    al_install_keyboard();


    Display display(SCREEN_W, SCREEN_H);
    display.setWindowTitle("Ma Pong :-)");

    //--------------
    EventQueue eventQueue;
    Timer timer(1./60);
    UserEventSource ues;

    //bind the resources to the event queue
    eventQueue << Keyboard::getEventSource() /*<< Mouse::getEventSource()*/ << display << timer << ues;
    //--------------


    // al_clear_to_color(al_map_rgb(40,40,40)); //Цвет фона
    Color clr1(40,40,40);
    









    

    float hight = 25;
    float width = 25;



    Ball ball( makePoint(SCREEN_W/2, SCREEN_H/2), hight, width );
    ball.velocity = makePoint(1, 1);
    ball.sprite_color = al_map_rgb(255, 0, 0);

    Board myBoard( makePoint( SCREEN_W-75 , SCREEN_H/2), 25, 150 );
    myBoard.velocity = makePoint(5, 5);

    // cout << ball.position.getX() << endl;
    // cout << ball.position.getY() << endl;
    
// 

    // float offset = 5.5;
    // ALLEGRO_COLOR color_orange = al_map_rgb(255, 0, 0);
    // al_draw_rectangle(offset, offset, hight+offset, width+offset, color_orange, 1);

    
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
            
            al_clear_to_color( clr1 );

            ball.draw();
            ball.fly();

            myBoard.draw();


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
                paddle.position.setX(std::max(0, std::min(event.getMouseX() - paddle.bitmap.getWidth()/2, display.getWidth() - paddle.bitmap.getWidth())));
                if (ball.velocity == Point<int>(0, 0)) {
                    ball.position.setX(paddle.position.getX() + paddle.bitmap.getWidth()/2 - ball.bitmap.getWidth()/2);
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
                    // updateLogic(); //???????????????????????????????????????????????????????????????????????????
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
