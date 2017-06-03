#include <iostream>
#include <string>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

main(){

	io_service io;


	ip::udp::endpoint ep(ip::udp::v4(), 9090);


	while(true){

		ip::udp::socket sk(io, ep);

		ip::udp::endpoint receiver_endpoint /*= *resolver.resolve(query)*/;
		
		//string send_buf  = "Hello world!";
		boost::array<char, 128> send_buf; // = {0}; мусор

			size_t len_buf = 
		sk.receive_from(boost::asio::buffer(send_buf), receiver_endpoint);

			cout<< "receive..." << endl;
			cout.write(send_bufta(), len_buf); // Почему не работает?!?!

    	sk.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

    		// cout << send_buf << endl; 

    		//buffer(send_buf)
	
	}




}