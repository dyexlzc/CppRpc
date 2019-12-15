#ifndef _NET_H
#define _NET_H
#include "CppRpc.h"
/*
    实现UDP/TCP情况下的数据传输
*/
class UDP : public Network{
    //实现UDP客户端的链接
public:
    UDP(const std::string& servAddr,int port):Network(servAddr,port){

    }
    ~UDP(){

    }
    virtual MsgType sendAndrecv(char* buffer,int buffer_size,char* recverBuffer,int return_buffer_size){
        //UDP发送方式
        return MsgType(Success);
    }

};

class TCP : public Network{
    boost::asio::ip::tcp::socket socket;    //TCP套接字
    boost::asio::ip::tcp::endpoint ep;      //服务器端点
    char mBuffer[5000];
    //实现TCP客户端的链接
    void connect(){
        socket.connect(ep);
    }
public:
    TCP(const std::string& servAddr,int port):
        Network(servAddr,port),
        socket(mio_Serv),
        ep(boost::asio::ip::address::from_string(servAddr),port)
    {
        connect();      //初始化构造函数的时候就开始连接服务器
    }
    ~TCP(){
        socket.close();
    }
    virtual MsgType sendAndrecv(char* buffer,int buffer_size,char* recverBuffer,int return_buffer_size){
        //TCP发送方式
        socket.send(
            boost::asio::buffer(buffer,buffer_size)
        );
        socket.receive(
            boost::asio::buffer(mBuffer,sizeof(mBuffer))
        );
        memcpy(&rm,mBuffer,sizeof(rm)); //填充Respond结构体
        memcpy(recverBuffer,rm.data,return_buffer_size);
        return rm.msgType;              //把服务器对此条消息的相应返回，自行做判断
    }
};
#endif