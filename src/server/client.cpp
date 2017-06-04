#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

class Client
{
public:
	Client(string address, int port):
		ep(ip::address::from_string(address), port),
		sk(io)
	{
		sk.connect(ep); //Connect the socket to the specified endpoint. //error test
		
	};
	// ~Client();

	void connect(){

		string send_buf  = "initial send!\0";
		// size_t len_buf = 
			// sk.receive_from(boost::asio::buffer(send_buf), receiver_endpoint);
		sk.send_to( buffer(send_buf,12), ep);
				
	};

	void run(){
		
	};
	
	void send(){

		string send_buf  = "Hello world!\0";
		sk.send_to( buffer(send_buf,12), ep);

	};

	void receive(){

		boost::array<char, 128> recv_buf = {0};
		size_t len = sk.receive_from( boost::asio::buffer(recv_buf), ep); //присылаеться мусор с серверского буфера

		std::cout.write(recv_buf.data(), len);

		sk.close();

	};
	
private:
	io_service io;
	
	ip::udp::endpoint ep;
	
	ip::udp::socket sk;

	ip::udp::endpoint receiver_endpoint /*= *resolver.resolve(query)*/;
};

main(){

	Client myClient(string("127.0.0.1"), 9090);

	// myClient.connect();

	myClient.send();

	//wait??

	myClient.receive();

}