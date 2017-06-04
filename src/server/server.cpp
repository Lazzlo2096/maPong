#include <iostream>
#include <string>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

boost::array<char, 128> send_buf; // = {0}; мусор
		//string send_buf  = "Hello world!";

class server
{
public:
	server():
		ep(ip::udp::v4(), 9090),
		sk(io, ep)
	{};
	// ~server();

	void connect(){

		size_t len_buf = 
			sk.receive_from(boost::asio::buffer(send_buf), receiver_endpoint);
				
	};

	void run(){

		size_t len_buf = 
			sk.receive_from(boost::asio::buffer(send_buf), receiver_endpoint);

		cout<< "receive..." << endl;
		cout.write(send_buf.data(), len_buf); // Почему не работает?!?! работает но не с первого раза

		sk.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

		// cout << send_buf << endl; 

		//buffer(send_buf)

	};
	
private:
	io_service io;
	
	ip::udp::endpoint ep;
	
	ip::udp::socket sk;

	ip::udp::endpoint receiver_endpoint /*= *resolver.resolve(query)*/;
};

main(){

	server myServer;

	myServer.connect();

	while(true){

		myServer.run();
		
	}

}