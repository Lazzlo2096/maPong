
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

    Sprite(const Point<int> &pos) : position(pos) {
    }



};

class Ball : public Sprite
{
public:

    int hight;
    int width;


    // Ball();
    ~Ball(){};

    Ball(const Point<int> &pos, int _hight, int _width) : Sprite(pos), hight(_hight), width(_width) {
    }



    void draw() {

        ALLEGRO_COLOR color_orange = al_map_rgb(255, 0, 0);
        al_draw_rectangle(position.getX(), position.getY(), hight+position.getX(), width+position.getY(), color_orange, 1);
    
    }

    void fly() {

        //проверка на столкновение с краями
        if (position.getX() >= SCREEN_W or position.getX() <=0)
            velocity.setX( -velocity.getX() );

        if (position.getY() >= SCREEN_H or position.getY() <=0)
            velocity.setY( -velocity.getY() );

        position += velocity;
    }


    
};


int main(int argc, char **argv){

    al_init();
    Display display(SCREEN_W, SCREEN_H);
    display.setWindowTitle("Ma Pong :-)");


    // al_clear_to_color(al_map_rgb(40,40,40)); //Цвет фона
    Color clr1(40,40,40);
    









    

    float hight = 25;
    float width = 25;

    float offset = 5.5;

    // Point<int> pnt1(5, 6);
    // Ball ball( pnt1 );
    // Ball ball( *(new Point<int> (5,6)) );
    Ball ball( makePoint(5, 6), hight, width );
    ball.velocity = makePoint(1, 1);

    // cout << ball.position.getX() << endl;
    // cout << ball.position.getY() << endl;
    
// 

    // ALLEGRO_COLOR color_orange = al_map_rgb(255, 0, 0);
    // al_draw_rectangle(offset, offset, hight+offset, width+offset, color_orange, 1);

    
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    event_queue = al_create_event_queue();

    while(1)
    {
            // al_clear_to_color( clr1 );

        // ALLEGRO_EVENT ev;
        // al_wait_for_event(event_queue, &ev);
 
        // if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            // break;
        // }
 
        // if( al_is_event_queue_empty(event_queue)) {
            // redraw = false;

            ball.draw();
            ball.fly();


            al_flip_display();
        // }
   }
 



    // al_flip_display(); //Отрисовка
    
    al_rest(5.0); //Задержка в секундах
    // al_destroy_display(display);




   return 0;
}
