
#include <iostream>
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


//using namespace boost::asio
//using ip::tcp

using std::string;
using std::cout;
using std::endl;

int main()
{
	int port = 1233;
	boost::asio::io_service io_service_;
	boost::asio::ip::tcp::acceptor acceptor_(io_service_, 
	boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));

    	char packet_type[4];

    	boost::asio::ip::tcp::socket socket_(io_service_);

    	acceptor_.async_accept(socket_, [&](boost::system::error_code ec){

        	boost::asio::async_read(socket_, boost::asio::buffer(packet_type, 4), 
        	[&](boost::system::error_code ec, std::size_t N)
        	{
           		std::cout << "Received: '";
            		std::cout.write(packet_type, sizeof(packet_type)) << "'\n";
 			write(socket_, boost::asio::buffer(packet_type),ec);
        	});
    	});

	io_service_.run();

	return 0;
}

