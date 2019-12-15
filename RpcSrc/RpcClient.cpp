#include "RpcClient.h"

MsgType CppRpcClient::Call(
    const std::string& FuncName,
    char* param,
    int param_size,
    char* returns,
    int return_size
){
    //1.填充结构体
    strcpy(msg.FuncName,FuncName.c_str());  //填充函数名
    memcpy(msg.Param,param,param_size);     //填充函数参数体
    memcpy(mBuffer,&msg,sizeof(msg));       //把待发送的数据放入缓冲区
    MsgType mt=NetPtr->sendAndrecv(
        mBuffer,
        sizeof(mBuffer),
        mBuffer,
        sizeof(mBuffer)
    );                  
    /*
        调用接口发送二进制数据,需要四个参数
        (
            需要发送的缓冲区
            缓冲区大小
            接受返回消息的缓冲区
            返回消息缓冲区的大小
        )
        缓冲区其实可以复用
    */
    
    //处理结束，此时mBuffer中已经存放了返回的消息
    memcpy(returns,mBuffer,return_size);
    return mt;
}