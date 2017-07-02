#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include "server.h"

boost::array<char, 128> send_buf_g; // = {0}; мусор
		//string send_buf_g  = "Hello world!";

Server::Server(int port):
	ep(boost::asio::ip::udp::v4(), port),
	sk(io, ep)
{};

void Server::connect()
{
	std::cout << "=> ждёт подключения клиента" << std::endl;
	size_t len_buf = 
		sk.receive_from(boost::asio::buffer(send_buf_g), receiver_endpoint);
	std::cout << "=> Клиент подключился" << std::endl;
};

void Server::run()
{
	size_t len_buf = 
		sk.receive_from(boost::asio::buffer(send_buf_g), receiver_endpoint);

	std::cout << "receive..." << std::endl;
	std::cout.write(send_buf_g.data(), len_buf); // Почему не работает?!?! работает но не с первого раза

	sk.send_to(boost::asio::buffer(send_buf_g), receiver_endpoint);

	// cout << send_buf_g << endl; 

	//buffer(send_buf_g)
};