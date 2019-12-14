#include<iostream>
#include<thread>
#include "RpcSrc/RpcServer.h"
using namespace std;
int main(){
    CppRpcServer serv(
        new ServTCP(40232,"./DynamicSo/")
    );

    move(thread(
        [&serv]{
            string cmd;
            while(true){
                cin>>cmd;
                if(cmd=="q"){
                    serv.close();
                    exit(0);
                }
            }
        }
    )).detach();
    serv.start();       //开始监听
    return 0;
}