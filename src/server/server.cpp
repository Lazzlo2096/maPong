#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include "server.h"

Server::Server(int port):
	ep(boost::asio::ip::udp::v4(), port),
	sk(io, ep)
{};

void Server::connect()
{
	size_t len_buf = 
		sk.receive_from(boost::asio::buffer(send_buf), receiver_endpoint);		
};

void Server::run()
{
	size_t len_buf = 
		sk.receive_from(boost::asio::buffer(send_buf), receiver_endpoint);

	cout<< "receive..." << endl;
	cout.write(send_buf.data(), len_buf); // Почему не работает?!?! работает но не с первого раза

	sk.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

	// cout << send_buf << endl; 

	//buffer(send_buf)
};