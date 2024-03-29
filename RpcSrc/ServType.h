#ifndef _SERVTYPE_H_
#define _SERVTYPE_H_
#include "CppRpc.h"
#include "../DynamicFunc/DynamicFunc.h"
#include <unordered_map>
using SockPtr=std::shared_ptr<boost::asio::ip::tcp::socket>;    //智能指针
//实现UDP TCP的服务器端
class ServUDP : public serverType{      //UDP服务器
    boost::asio::ip::udp::socket mServerSocket; //udp只需要一个服务器socket
    boost::asio::ip::udp::endpoint mClientEndpoint;
    char mBuffer[1200];
    virtual void accept();
    void HandleAccept(const boost::system::error_code& ec, int size);
    void HandleNull(){
        return;
    }
public:
    ServUDP(int port):
        serverType(port),               //初始化端口
        mServerSocket(mio_Serv,boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(),port))
    {
    
    }
    virtual void startServ(){           //UDP服务器的启动
        //1.注册accept消息
        accept();
        //2:启动mio_serv监听
        mio_Serv.run();
    }
    ~ServUDP(){
        mServerSocket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        mServerSocket.close();
    }
};

class ServTCP : public serverType{              //TCP服务器
    boost::asio::ip::tcp::acceptor mAcceptor;     //tcp所需要的acceptor
    boost::asio::ip::tcp::socket   mSocket;       //临时的Socket
    char mBuffer[1200];                         //全局缓冲区
    DynamicFunc dynamicFunc;                    //用于动态接受函数call
    NetMsg nm;         //接受从客户端发来的请求
    RespondMsg rm;      //发送给客户端的响应

    void HandleAccept(const boost::system::error_code& ec,SockPtr sp);
    void HandleRead(const boost::system::error_code& ec,SockPtr sp);
    void HandleNull(const boost::system::error_code& ec){
        return;
    }
    virtual void accept();
    
public:
    ServTCP(int port,std::string soPath):
        serverType(port),               //初始化端口
        mAcceptor(mio_Serv,boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(),port)),
        mSocket(mio_Serv),
        dynamicFunc(soPath)
    {
    
    }
    virtual void startServ(){           //TCP服务器的启动
        //1.注册accept消息
        accept();
        //2:启动mio_serv监听
        mio_Serv.run();
    }
    ~ServTCP(){

        mAcceptor.close();

    }
};
#endif