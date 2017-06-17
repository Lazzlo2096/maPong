#include <iostream>
#include <string>
#include <boost/asio.hpp>

//using namespace std;
//using namespace boost::asio;

boost::array<char, 128> send_buf; // = {0}; мусор
		//string send_buf  = "Hello world!";

class Server
{
public:
	Server(int port);
	// ~server();

	void connect();

	void run();
	
private:
	boost::asio::io_service io;
	
	boost::asio::ip::udp::endpoint ep;
	
	boost::asio::ip::udp::socket sk;

	boost::asio::ip::udp::endpoint receiver_endpoint /*= *resolver.resolve(query)*/;
};