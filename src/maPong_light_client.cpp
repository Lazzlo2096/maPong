#include <iostream>
#include <string>

#include "./server/helpPage.h" //struct EnpPoint, parseArgs()
#include "./server/server.h"
#include "./server/client.h"

using namespace std;

//Нужен для того чтобы проверить как работает maPong как сервер. Потом можно превратить в тест?
int main(int argc, char **argv){


	struct EnpPoint ep = parseArgs(argc, argv); //парсим аргументы //надобы завести пространство имён (непонятно откуда эта функция)

	//проверка на режим игры
	if (ep.port != 0){
		//Значит работает как сервер или клиент, а не как одиночная игра с компьютером

		if (ep.address == ""){
			//Значит работает как сервер
		} else
		{
			//Значит работает как клиент
			cout << "=> Runing as client at address "<< ep.address << " and port " << ep.port << endl;
			static Client client(ep.address, ep.port); // Может не static а просто вынести из скобок или как?

			client.connect();


		}
	}



}