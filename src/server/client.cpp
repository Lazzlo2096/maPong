#include <iostream>
#include <boost/asio.hpp>

#include "client.h"

Client::Client(std::string address, int port):
	ep(boost::asio::ip::address::from_string(address), port),
	sk(io)
{
	sk.connect(ep); //Connect the socket to the specified endpoint. //error test
};
// Client::~Client();

void Client::connect()
{
	std::string send_buf  = "initial send!\0";
	// size_t len_buf = 
		// sk.receive_from(boost::asio::buffer(send_buf), receiver_endpoint);
	std::cout << "=> сейчас будет подключен к серверу" << std::endl;
	sk.send_to( boost::asio::buffer(send_buf,12), ep);
	std::cout << "=> подключен к серверу" << std::endl;
			
};

void Client::run()
{
	
};

void Client::send()
{
	std::string send_buf  = "Hello world!\0";
	sk.send_to( boost::asio::buffer(send_buf,12), ep);

};

void Client::receive()
{
	boost::array<char, 128> recv_buf = {0};
	size_t len = sk.receive_from( boost::asio::buffer(recv_buf), ep); //присылаеться мусор с серверского буфера

	std::cout.write(recv_buf.data(), len);

	sk.close();

};