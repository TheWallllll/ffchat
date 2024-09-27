#pragma once
#include "const.h"

class HttpConnection;
typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler;

class LogicSystem : public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>;
public:
	~LogicSystem();

	// 处理get请求
	bool HandleGet(std::string, std::shared_ptr<HttpConnection>);

	// 处理post请求
	bool HandlePost(std::string path, std::shared_ptr<HttpConnection> con);

	// 注册get请求
	void RegGet(std::string, HttpHandler handler);

	// 注册post请求
	void RegPost(std::string, HttpHandler handler);
private:
	LogicSystem();
	std::map<std::string, HttpHandler> _post_handlers;
	std::map<std::string, HttpHandler> _get_handlers;
};

