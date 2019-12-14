/*
    RCP独立客户端测试
*/
#include<iostream>
#include<boost/asio.hpp>
#include<boost/bind.hpp>
#include<boost/format.hpp>
 
#include"DynamicSo/interface.h"
using namespace std;
using namespace boost::asio;
int main(){
    io_service io_serv;
    ip::tcp::socket socket(io_serv);
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"),40232);
    char mBuffer[5000];//缓冲区和服务器5000单位保持一致
    try{
        socket.connect(ep);
        string cmd;
        NetMsg msg;
        while(1){
            cin>>cmd;
            
            if(cmd=="q"){
                socket.close();
                return 0;
            }else{
                strcpy(msg.FuncName,cmd.c_str());     //初始化调用函数名
                struct add_param{               //和服务器的具体so中的参数保持一致
                    int numa,numb;
                }addparam;
                cin>>addparam.numa>>addparam.numb;
                memcpy(msg.Param,&addparam,sizeof(addparam));  // 组合参数消息
                memcpy(mBuffer,&msg,sizeof(msg));
                socket.send(boost::asio::buffer(mBuffer,sizeof(mBuffer)));  //发送消息，等待服务器处理
                socket.receive(boost::asio::buffer(mBuffer,sizeof(mBuffer)));//接收消息
                int result;//因为结果是整数，所以需要申请地址来保存整数
                memcpy(&result,mBuffer,sizeof(result));
                cout<<boost::format("%1% %4% %2%=%3%")
                        %addparam.numa
                        %addparam.numb
                        %result
                        %cmd<<endl;
                continue;
            }

        }
    }
    catch(const boost::system::error_code &ec){
        cout<<ec.message()<<endl;
    }
    

    io_serv.run();
    return 0;
}