#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

// using namespace std;
// using namespace boost::asio;

class Client
{
public:
	Client(std::string address, int port);
	// ~Client();

	void connect();

	void run();
	
	void send();

	void receive();
	
private:
	boost::asio::io_service io;
	
	boost::asio::ip::udp::endpoint ep;
	
	boost::asio::ip::udp::socket sk;

	boost::asio::ip::udp::endpoint receiver_endpoint /*= *resolver.resolve(query)*/;
};