#pragma once
#include "const.h"

class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:
	friend class LogicSystem;
	HttpConnection(tcp::socket socket);
	void Start();

private:
	// ��ⳬʱ
	void CheckDeadline();

	// Ӧ����
	void WriteResponse();

	// ��������
	void HandleReq();

	void PreParseGetParam();

	tcp::socket  _socket;
	// ��������
	beast::flat_buffer  _buffer{ 8192 };

	// ������Ϣ
	http::request<http::dynamic_body> _request;

	// ��Ӧ��Ϣ
	http::response<http::dynamic_body> _response;

	// Ϊ�������ö�ʱ��
	net::steady_timer deadline_{
		_socket.get_executor(), std::chrono::seconds(60) };

	// URL
	std::string _get_url;

	// ����
	std::unordered_map<std::string, std::string> _get_params;
};

