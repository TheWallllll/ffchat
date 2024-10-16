#pragma once
#include "const.h"

class CServer :public std::enable_shared_from_this<CServer>
{
public:
	// ioc没有拷贝构造，保证唯一性
	CServer(boost::asio::io_context& ioc, unsigned short& port);
	void Start();
private:
	tcp::acceptor  _acceptor;                   // 接收连接
	net::io_context& _ioc;						// 上下文
};

