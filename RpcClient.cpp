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
            if(client.Call(cmd,        //远程调用函数
                (char*)&t,sizeof(t),
                (char*)&result,sizeof(result)
            )==Success){
                cout<<boost::format("%1% %2% %3%=%4%")
                        %t.a
                        %cmd
                        %t.b
                        %result<<endl;
            }else{
                cout<<"Error ocure in server"<<endl;
            }
            
            continue;
        }
        if(cmd=="login"){
            struct loginStruct{
                char usrname[10];
                char pwd[10];
            }usr;
            cout<<"Username:";cin>>usr.usrname;
            cout<<"Pwd:";cin>>usr.pwd;
            char servMsg[50];
            if(client.Call(cmd,        //远程调用函数
                (char*)&usr,sizeof(usr),
                (char*)servMsg,sizeof(servMsg)
            )==Success){
                cout<<boost::format("登录消息:%1%")
                        %servMsg<<endl;
            }else{
                cout<<"Error ocure in server"<<endl;
            }
            continue;
        }
        if(cmd=="q"){
            break;
        }
    }
    return 0;
}