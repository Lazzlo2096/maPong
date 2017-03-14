
#include <iostream>
#include <allegro5/allegro.h>

#include "alx.hpp"

using namespace std;
using namespace alx;

#define PI 3.14159

// const float FPS = 60;
const int SCREEN_W = 640*1.25;
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

    // ALLEGRO_COLOR sprite_color = al_map_rgb(255, 0, 0);
    ALLEGRO_COLOR sprite_color = al_map_rgb(255, 255, 255);


    /*Sprite(const Point<int> &pos, const Bitmap &bmp) : position(pos), bitmap(bmp) {
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

    Sprite(const Point<int> &pos, int _width, int _hight) : position(pos), hight(_hight), width(_width) {
    }

    Sprite(const Point<int> &pos) : position(pos) {
    }


    void draw() {

        // al_draw_rectangle(position.getX(), position.getY(), width+position.getX(), hight+position.getY(), sprite_color, 1);
        // al_draw_filled_rectangle(position.getX(), position.getY(), width+position.getX(), hight+position.getY(), sprite_color);

        Point<int> _position = position - makePoint(width/2, hight/2);
        // Point<int> _position = position ;
        al_draw_filled_rectangle(_position.getX(), _position.getY(), width+_position.getX(), hight+_position.getY(), sprite_color);
    
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
        if (position.getX() >= SCREEN_W-width/2 or position.getX() <= 0+width/2)
            velocity.setX( -velocity.getX() );

        if (position.getY() >= SCREEN_H-hight/2 or position.getY() <= 0+hight/2)
            velocity.setY( -velocity.getY() );

        position += velocity;
    }

    //check collision between two sprites
    // bool collision(const Sprite& obj) {
    void collision(const Sprite& obj) {
        
        // if( getRect().intersects(obj.getRect()) ){
        if( abs(position.getX()-obj.position.getX()) == width/2+obj.width/2  and (abs(position.getY()-obj.position.getY()) < hight/2+obj.hight/2 ) )
        {
            setRandomColor();
                // velocity.setX( -abs(velocity.getX()+1.5) ); //Баги, баги, эти баги ВЕЗДЕ!
                velocity.setX( velocity.getX() ); 
        }
        else if( abs(position.getY()-obj.position.getY()) == hight/2+obj.hight/2  and (abs(position.getX()-obj.position.getX()) < width/2+obj.width/2 ) )
            velocity.setY( -velocity.getY() );
        // else


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
    // ball.sprite_color = al_map_rgb(255, 0, 0);

    // Board myBoard( makePoint( SCREEN_W-75-25/2 , SCREEN_H/2-150/2), 25, 150 );
    Board myBoard( makePoint( SCREEN_W-75 , SCREEN_H/2), 25, 150 );
    myBoard.velocity = makePoint(5, 5);
    



    Board evilBoard( makePoint( 75 , SCREEN_H/2), 25, 150 );
    // evilBoard.velocity = makePoint(5, 5); //Багает при этом значении
    evilBoard.velocity = makePoint(1, 1);




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

            myBoard.draw();

            evilBoard.draw();
            // evilBoard.position.setY( ball.position.getY() );


            al_flip_display();

            redraw = false;
        }
            ball.fly();
            evilBoard.autoCatch( ball.position );

            ball.collision( myBoard );
            ball.collision( evilBoard );


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
