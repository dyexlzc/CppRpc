#include<iostream>
#include"./RpcSrc/RpcClient.cpp"
#include<boost/format.hpp>
using namespace std;
int main(){
    CppRpcClient client(
        new TCP("127.0.0.1",40232)
    );
    string cmd;
    while(1){
        cin>>cmd;
        if(cmd=="add" || cmd=="mul"){
            struct param{
                int a,b;
            }t;
            int result;         //保存计算结果
            cin>>t.a>>t.b;
            client.Call(cmd,        //远程调用函数
                (char*)&t,sizeof(t),
                (char*)&result,sizeof(result)
            );
            cout<<boost::format("%1% %2% %3%=%4%")
                        %t.a
                        %cmd
                        %t.b
                        %result<<endl;
            continue;
        }
        if(cmd=="q"){
            break;
        }
    }
    return 0;
}