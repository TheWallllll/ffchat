#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "CServer.h"

int main()
{
	try
	{
		// 端口号
		unsigned short port = static_cast<unsigned short>(8080);
		// 上下文，设置一个线程
		net::io_context ioc{ 1 };
		// 设置信号集
		boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
		// 等待信号发生
		signals.async_wait([&ioc](const boost::system::error_code& error, int signal_number) {
			if (error) {
				return;
			}
			ioc.stop();
			});
		std::make_shared<CServer>(ioc, port)->Start();
		std::cout << "Gate Server listen on port: " << port << std::endl;
		ioc.run();
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}