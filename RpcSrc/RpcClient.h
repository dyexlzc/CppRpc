#ifndef _RPCCLIENT_H
#define _RPCCLIENT_H
#include "CppRpc.h"
#include <boost/asio.hpp>
#include <string>
#include"../DynamicSo/interface.h"
#include"ClientType.h"
class CppRpcClient : public CppRpc{     //实现rpc客户端，向远程发送请求
    Network *NetPtr;                    //动态绑定UDP、TCP的发送方式
    char mBuffer[5000];
    NetMsg msg;
public:
    //客户端是阻塞的同步方式向服务器通信
    //在构造函数里面设定服务器的endpoint
    CppRpcClient(Network* ptr):NetPtr(ptr)
    {

    }
    ~CppRpcClient(){
        delete NetPtr;
    }
    virtual void start(){}
    virtual void Call(
        const std::string& FuncName,
        char* param,
        int param_size,
        char* returns,
        int return_size
    );                          //RPC call远程函数，填好param后需要指定param大小和returns地址和其大小
};
#endif