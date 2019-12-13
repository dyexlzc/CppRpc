#ifndef _CPPRPC_H
#define _CPPRPC_H
#include <boost/asio.hpp>
/*
    CppRpc框架设计

*/
class Network{                  
/*
    统一的网络发送、接受interface
    必须必须重写UDP/TCP
*/
public:
    virtual void send(char* buffer,int buffer_size)=0;
    virtual void recv(char* buffer,int buffer_size)=0;
};

//////////////////////////////////////////////////////////////
class CppRpc{                           

public:
    virtual void start()=0;             //服务器、客户端的启动
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