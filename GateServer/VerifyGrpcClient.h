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
    /// @brief ���캯������ȡgRPC��ͨ����Stub���������
    /// @param poolSize 
    /// @param host 
    /// @param port 
    RPConPool(size_t poolSize, std::string host, std::string port);

    ~RPConPool();

    /// @brief �õ������һ��stub
    /// @return 
    std::unique_ptr<VarifyService::Stub> getConnection();

    /// @brief ��stub���¼������
    /// @param context 
    void returnConnection(std::unique_ptr<VarifyService::Stub> context);

    void Close();

private:
    std::atomic<bool> b_stop_;
    size_t poolSize_;
    std::string host_;
    std::string port_;
    // VarifyService::Stub ���� gRPC ������ͨ�ŵ�������ͨ�������ͻ��˿��Է���ص���Զ�̷��񷽷��������������Ӧ��
    std::queue<std::unique_ptr<VarifyService::Stub>> connections_;
    // ��֤�����̰߳�ȫ
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

