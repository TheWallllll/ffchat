#pragma once
#include "const.h"

class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:
	friend class LogicSystem;
	HttpConnection(tcp::socket socket);
	void Start();

private:
	// 检测超时
	void CheckDeadline();

	// 应答函数
	void WriteResponse();

	// 处理请求
	void HandleReq();

	void PreParseGetParam();

	tcp::socket  _socket;
	// 读缓冲区
	beast::flat_buffer  _buffer{ 8192 };

	// 请求信息
	http::request<http::dynamic_body> _request;

	// 相应信息
	http::response<http::dynamic_body> _response;

	// 为连接设置定时器
	net::steady_timer deadline_{
		_socket.get_executor(), std::chrono::seconds(60) };

	// URL
	std::string _get_url;

	// 参数
	std::unordered_map<std::string, std::string> _get_params;
};

