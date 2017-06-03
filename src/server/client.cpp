#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

main(){

	io_service io;

	ip::udp::endpoint ep(ip::address::from_string("127.0.0.1"), 9090);

	ip::udp::socket sk(io);	//не (io, ep)
	sk.connect(ep); //Connect the socket to the specified endpoint. //error test


	string send_buf  = "Hello world!\0";
    
    sk.send_to( buffer(send_buf,12), ep);

    	boost::array<char, 128> recv_buf = {0};

    size_t len = sk.receive_from( boost::asio::buffer(recv_buf), ep); //присылаеться мусор с серверского буфера

    std::cout.write(recv_buf.data(), len);


	sk.close();

}