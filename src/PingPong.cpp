#include "PingPong.h"


// Ball();
Ball::~Ball(){};

Ball::Ball(Point<int> pos, int _width, int _hight) 
	: Rectangle(pos, _width, _hight) {} ;

/*Ball::Ball(int pos_x, int pos_y, int _width, int _hight) 
	: Rectangle(Point<int>(pos_x, pos_y), _width, _hight) {} ;
*/
void Ball::setRandomColor(){

	int i = color;
	setRectangle_color( al_map_rgb((i%3==0?255:0), (i%3==1?255:0), (i%3==2?255:0)) );

	color++;

}



void Ball::fly() {
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
void Ball::collision(const Sprite& obj) {
	
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


//------------------------------

Board::~Board(){};

Board::Board(const Point<int> &pos, int _width, int _hight) 
	: Rectangle(pos, _width, _hight) {
}




void Board::move_down() {

	//проверка на столкновение с краями
	// if (position.getX() >= SCREEN_W or position.getX() <=0)
		// velocity.setX( -velocity.getX() );


	if (position.getY()+velocity.getY() <= SCREEN_H-hight/2)
		// velocity.setY( -velocity.getY() );
		position.setY( position.getY()+velocity.getY() ) ;
	else
		position.setY( SCREEN_H-hight/2 );
}

void Board::move_up() {

	//проверка на столкновение с краями
	// if (position.getX() >= SCREEN_W or position.getX() <=0)
		// velocity.setX( -velocity.getX() );

	if (position.getY()-velocity.getY() >= 1+hight/2)
		// velocity.setY( -velocity.getY() );
		position.setY( position.getY()-velocity.getY() ) ;
	else
		position.setY( 1+hight/2 );
}



void Board::autoCatch(Point<int> point){

	if (position.getY() > point.getY())
		move_up();
	else if (position.getY() < point.getY())
		move_down();


}