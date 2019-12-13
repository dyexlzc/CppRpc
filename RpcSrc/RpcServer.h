#ifndef _RPCSERVER_H
#define _RPCSERVER_H
#include "CppRpc.h"
#include "ServType.h"
#include <boost/asio.hpp>

class CppRpcServer : public CppRpc{     //实现rpc服务器，监听远程连接请求
    serverType* mServType;              //服务器实例，可以开启UDP/TCP的实例
public:
    CppRpcServer(serverType *servType ){             //在本机的port端口号开启服务
        //接受外部的参数，启动UDP/TCP服务器
        mServType=servType;
    }
    virtual void start();                 //启动监听
    void close();               //结束服务，释放资源
    ~CppRpcServer();
};
#endif