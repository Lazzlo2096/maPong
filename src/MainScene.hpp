#pragma once



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
		//to_string(yourScore).c_str()
		yourScore_str.c_str()
	);

	al_draw_text(
		font,
		color_score,
		SCREEN_W/2 - interval,
		0+indentation,
		ALLEGRO_ALIGN_CENTRE,
		//to_string(enemyScore).c_str()
		enemyScore_str.c_str()
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

class mainScene // MainScene
{

	const float board_height = 25;
	const float board_width = 150;

	maPong::Ball ball;
	// ball.sprite_color = al_map_rgb(255, 0, 0);

	/*Board myBoard( alx::makePoint( SCREEN_W-75-25/2 , SCREEN_H/2-150/2), 25,
	 150 );*/
	maPong::Board myBoard;

	maPong::Board enemyBoard;

	ALLEGRO_FONT *font;

	//GameInterfaceElements::Menu mainMenu;

public:

	mainScene():
		ball( alx::makePoint(SCREEN_W/2, SCREEN_H/2), 25, 25 ),
		myBoard( alx::makePoint( SCREEN_W-75 , SCREEN_H/2), board_height, board_width ),
		enemyBoard( alx::makePoint( 75 , SCREEN_H/2), board_height, board_width )	
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

	void init(){

		ball.setVelocity( alx::makePoint(1, 1) );
		myBoard.setVelocity( alx::makePoint(5, 5) );
		// enemyBoard.velocity() = makePoint(5, 5); //Багает при этом значении
		enemyBoard.setVelocity( alx::makePoint(1, 1) );
	};

	void calcAndDrawFrame(){
		//Что первее - отрисовка или логика?
		//Думаю эти блоки можно разделить по методам??

		//Как бы отрисовка игры
		//Мб отрисовку игры можно типа объединить в один метод
		//-------
		drawPingPongBackground(font);

		ball.draw();
		myBoard.draw();
		enemyBoard.draw();
		//-------

		//Как бы логика игры
		//-------
		ball.fly();
		//реализовать - Если сталкиваються, то мячик отпрыгивает = скорость - растояние до обекта + оставшаяся скоость в новом направлении
		ball.collision( myBoard );
		ball.collision( enemyBoard );
		//ball.collision( Borders );

		//Если может ловить только мои объекты(в частности мячи),
		//то используя метод внути (а если он будет слидить и за бортиком то используй шаблон?полиморфизм?)
		enemyBoard.autoCatch( ball.getPosition() ); //переименовать в follow()
		// enemyBoard.follow( ball );
		//-------

		//GameInterfaceElements::Menu
		//mainMenu.drawMenu();

	}

	//зачем мне дополнительные методы ещё и для mainScene - можно убрать
	void onKeyDown(){ myBoard.move_down(); }
	void onKeyUp(){ myBoard.move_up(); }
};