#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"
#include "Singleton.h"
using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVarifyReq;
using message::GetVarifyRsp;
using message::VarifyService;

class RPConPool {
public:
    /// @brief 构造函数，获取gRPC的通道和Stub，加入队列
    /// @param poolSize 
    /// @param host 
    /// @param port 
    RPConPool(size_t poolSize, std::string host, std::string port);

    ~RPConPool();

    /// @brief 得到池里的一个stub
    /// @return 
    std::unique_ptr<VarifyService::Stub> getConnection();

    /// @brief 将stub重新加入池子
    /// @param context 
    void returnConnection(std::unique_ptr<VarifyService::Stub> context);

    void Close();

private:
    std::atomic<bool> b_stop_;
    size_t poolSize_;
    std::string host_;
    std::string port_;
    // VarifyService::Stub 是与 gRPC 服务器通信的桥梁，通过它，客户端可以方便地调用远程服务方法，处理请求和响应。
    std::queue<std::unique_ptr<VarifyService::Stub>> connections_;
    // 保证队列线程安全
    std::mutex mutex_;
    std::condition_variable cond_;
};

class VerifyGrpcClient :public Singleton<VerifyGrpcClient>
{
    friend class Singleton<VerifyGrpcClient>;
public:

    GetVarifyRsp GetVarifyCode(std::string email);

private:
    VerifyGrpcClient();

    std::unique_ptr<RPConPool> pool_;
};

