#ifndef _NET_H
#define _NET_H
#include "CppRpc.h"
/*
    实现UDP/TCP情况下的数据传输
*/
class UDP : public Network{
    //实现UDP客户端的链接
public:
    UDP(){

    }
    ~UDP(){

    }
    virtual void send(char* buffer,int buffer_size){
        //UDP发送方式
    }
    virtual void recv(char* buffer,int buffer_size){
        //UDP接受方式
    }
};

class TCP : public Network{
    //实现TCP客户端的链接
public:
    TCP(){

    }
    ~TCP(){

    }
    virtual void send(char* buffer,int buffer_size){
        //TCP发送方式
    }
    virtual void recv(char* buffer,int buffer_size){
        //TCP接受方式
    }
};
#endif