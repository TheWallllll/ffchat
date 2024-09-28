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

class VerifyGrpcClient :public Singleton<VerifyGrpcClient>
{
    friend class Singleton<VerifyGrpcClient>;
public:

    GetVarifyRsp GetVarifyCode(std::string email) {
        ClientContext context;
        GetVarifyRsp reply;
        GetVarifyReq request;
        request.set_email(email);

        Status status = stub_->GetVarifyCode(&context, request, &reply);

        if (status.ok()) {

            return reply;
        }
        else {
            reply.set_error(ErrorCodes::RPCFailed);
            return reply;
        }
    }

private:
    VerifyGrpcClient() {
        // 通道
        std::shared_ptr<Channel> channel = grpc::CreateChannel("127.0.0.1:50051", 
            grpc::InsecureChannelCredentials());
        stub_ = VarifyService::NewStub(channel);
    }

    // VarifyService::Stub 是与 gRPC 服务器通信的桥梁，通过它，客户端可以方便地调用远程服务方法，处理请求和响应。
    std::unique_ptr<VarifyService::Stub> stub_;
};

