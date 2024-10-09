#pragma once
#include "const.h"
#include "MysqlDao.h"
#include "Singleton.h"
class MysqlMgr: public Singleton<MysqlMgr>
{
	friend class Singleton<MysqlMgr>;
public:
	~MysqlMgr();
	int RegUser(const std::string& name, const std::string& email,  const std::string& pwd);
	bool CheckEmail(const std::string& name, const std::string & email);
	bool UpdatePwd(const std::string& name, const std::string& email);
	bool CheckPwd(const std::string& name, const std::string& pwd, UserInfo& userInfo);
	std::shared_ptr<UserInfo> GetUser(int uid);
	std::shared_ptr<UserInfo> GetUser(std::string name);

private:
	MysqlMgr();
	MysqlDao  _dao;
};

