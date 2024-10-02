#pragma once
#include "const.h"
#include <thread>
#include <jdbc/mysql_driver.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/exception.h>

class SqlConnection {
public:
    SqlConnection(sql::Connection* con, int64_t lasttime) :_con(con), _last_oper_time(lasttime) {}
    std::unique_ptr<sql::Connection> _con;
    // 心跳机制，保活
    int64_t _last_oper_time;
};

class MySqlPool {
public:
    MySqlPool(const std::string& url, const std::string& user, 
        const std::string& pass, const std::string& schema, int poolSize);

    std::unique_ptr<SqlConnection> getConnection();

    void returnConnection(std::unique_ptr<SqlConnection> con);

    void checkConnection();

    void Close() {
        b_stop_ = true;
        cond_.notify_all();
    }

    ~MySqlPool() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (!pool_.empty()) {
            pool_.pop();
        }
    }

private:
    std::string url_;
    std::string user_;
    std::string pass_;
    std::string schema_;
    int poolSize_;
    std::queue<std::unique_ptr<SqlConnection>> pool_;
    std::mutex mutex_;
    std::condition_variable cond_;
    std::atomic<bool> b_stop_;
    // 心跳机制，保活
    // 创建一个检查线程，每分钟进行一次查询，防止长时间无操作被断开连接。
    std::thread _check_thread;
};

struct UserInfo {
    std::string name;
    std::string pwd;
    int uid;
    std::string email;
};

class MysqlDao
{
public:
    MysqlDao();
    ~MysqlDao();
    int RegUser(const std::string& name, const std::string& email, const std::string& pwd);
    bool CheckEmail(const std::string& name, const std::string& email);
    bool UpdatePwd(const std::string& name, const std::string& newpwd);
    bool CheckPwd(const std::string& email, const std::string& pwd, UserInfo& userInfo);
private:
    std::unique_ptr<MySqlPool> pool_;
};
