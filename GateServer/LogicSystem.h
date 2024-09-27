#pragma once
#include "const.h"

class HttpConnection;
typedef std::function<void(std::shared_ptr<HttpConnection>)> HttpHandler;

class LogicSystem : public Singleton<LogicSystem>
{
	friend class Singleton<LogicSystem>;
public:
	~LogicSystem();

	// ����get����
	bool HandleGet(std::string, std::shared_ptr<HttpConnection>);

	// ����post����
	bool HandlePost(std::string path, std::shared_ptr<HttpConnection> con);

	// ע��get����
	void RegGet(std::string, HttpHandler handler);

	// ע��post����
	void RegPost(std::string, HttpHandler handler);
private:
	LogicSystem();
	std::map<std::string, HttpHandler> _post_handlers;
	std::map<std::string, HttpHandler> _get_handlers;
};

