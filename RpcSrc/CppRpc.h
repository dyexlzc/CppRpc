#ifndef _CPPRPC_H
#define _CPPRPC_H
#include <boost/asio.hpp>
#include "../DynamicSo/interface.h"
/*
    CppRpc框架设计
    一些主要的，全局的interface将会在这里定义
*/
class Network{                  
/*
    统一的网络发送、接受interface
    必须必须重写UDP/TCP
*/
protected:
    RespondMsg rm;
    std::string ServAddr;
    int mPort;
    boost::asio::io_service mio_Serv;
public:
    Network(const std::string& servAddr,int port):
        ServAddr(servAddr),
        mPort(port)
    {

    }
    virtual void connect()=0;
    virtual MsgType sendAndrecv(char* buffer,int buffer_size,char* recverBuffer,int return_buffer_size)=0;
};

//////////////////////////////////////////////////////////////
class CppRpc{                           
public:
    virtual void start()=0;          //服务器、客户端的启动,统一的父类
    virtual ~CppRpc(){}
};
/////////////////////////////////////////////////////////////
class serverType{                   //决定UDP还是TCP服务器
protected:
    int mport;                      //服务器端口
    boost::asio::io_service    mio_Serv;//UDP TCP都需要的io_service
    virtual void accept()=0;        //不同服务器的接受回调
public:
    serverType(int port):mport(port){}
    virtual ~serverType(){
        mio_Serv.stop();
    }
    virtual void startServ()=0;     //不同服务器的启动接口
    
};

#endif