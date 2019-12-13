#include "RpcServer.h"
void CppRpcServer::start(){
    //RPC服务器启动监听
    mServType->startServ(); //启动服务器监听
    
}
void CppRpcServer::close(){
    //RPC服务器关闭链接，释放资源
    delete mServType;   //删除服务器资源，自动调用析构函数释放
    mServType=nullptr;  //指针悬空
    
}
CppRpcServer::~CppRpcServer(){
    //析构函数
    
}