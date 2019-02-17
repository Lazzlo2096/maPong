

#include "MainScene.hpp"

/* // if def with_server
#include "./server/helpPage.h" //struct EnpPoint, parseArgs()
#include "./server/server.h"
#include "./server/client.h"
*/

int main(int argc, char **argv)
{
/* // if def with_server
	struct EnpPoint ep = parseArgs(argc, argv); //парсим аргументы //надобы завести пространство имён (непонятно откуда эта функция)

	//проверка на режим игры
	if (ep.port != 0){
		//Значит работает как сервер или клиент, а не как одиночная игра с компьютером

		if (ep.address == ""){
			//Значит работает как сервер
			cout << "=> Runing as server at port " << ep.port << endl;
			static Server server(ep.port); // Может не static а просто вынести из скобок или как?

			server.connect();
		} else
		{
			//Значит работает как клиент
			cout << "=> Runing as client at address "<< ep.address << " and port " << ep.port << endl;
			static Client client(ep.address, ep.port); // Может не static а просто вынести из скобок или как?

			client.connect();
		}
	}
*/

	allegro_init();

	MyGame maPong;

	maPong.init();

	//maPong.run();

	return 0;
}