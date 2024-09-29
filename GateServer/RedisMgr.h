#pragma once
#include "const.h"

class RedisConPool {
public:
    RedisConPool(size_t poolSize, const char* host, int port, const char* pwd);

    ~RedisConPool();

    redisContext* getConnection();

    void returnConnection(redisContext* context);

    void Close();

private:
    std::atomic<bool> b_stop_;
    size_t poolSize_;
    const char* host_;
    int port_;
    std::queue<redisContext*> connections_;
    std::mutex mutex_;
    std::condition_variable cond_;
};

class RedisMgr : public Singleton<RedisMgr>,
    public std::enable_shared_from_this<RedisMgr>
{
    friend class Singleton<RedisMgr>;
public:
    ~RedisMgr();
    /// @brief ��ȡkey��Ӧ��value
    /// @param key 
    /// @param value 
    /// @return 
    bool Get(const std::string& key, std::string& value);
    /// @brief ����key��value
    /// @param key 
    /// @param value 
    /// @return 
    bool Set(const std::string& key, const std::string& value);
    /// @brief ������֤
    /// @param password 
    /// @return 
    bool Auth(const std::string& password);
    /// @brief ������
    /// @param key 
    /// @param value 
    /// @return 
    bool LPush(const std::string& key, const std::string& value);
    /// @brief ���ɾ��
    /// @param key 
    /// @param value 
    /// @return 
    bool LPop(const std::string& key, std::string& value);
    /// @brief �Ҳ����
    /// @param key 
    /// @param value 
    /// @return 
    bool RPush(const std::string& key, const std::string& value);
    /// @brief �Ҳ�ɾ��
    /// @param key 
    /// @param value 
    /// @return 
    bool RPop(const std::string& key, std::string& value);
    /// @brief �������������
    /// @param key 
    /// @param hkey 
    /// @param value 
    /// @return 
    bool HSet(const std::string& key, const std::string& hkey, const std::string& value);
    /// @brief �����ַ���
    /// @param key 
    /// @param hkey 
    /// @param hvalue 
    /// @param hvaluelen 
    /// @return 
    bool HSet(const char* key, const char* hkey, const char* hvalue, size_t hvaluelen);

    std::string HGet(const std::string& key, const std::string& hkey);
    bool Del(const std::string& key);
    bool ExistsKey(const std::string& key);
    void Close();
private:
    RedisMgr();

    std::unique_ptr<RedisConPool> _con_pool;
};

