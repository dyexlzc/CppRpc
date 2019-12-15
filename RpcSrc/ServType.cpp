/*
    实现TCP/UDP服务器接口
*/
#include "ServType.h"
#include "Msg.h"
#include "../DynamicSo/interface.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <iostream>
#include <boost/format.hpp>
//TCP
void ServTCP::accept(){
    //异步调用处理接收
    msg(info,"new SockPtr");
    SockPtr sp(new boost::asio::ip::tcp::socket(mio_Serv));
    mAcceptor.async_accept(
        *sp,
        [this,sp](const boost::system::error_code &ec){
            if(!ec){
                this->HandleRead(ec,sp);
                accept();
            }
        }
    );
}
void ServTCP::HandleRead(const boost::system::error_code& ec,SockPtr sp){
    sp->async_read_some(
        boost::asio::buffer(mBuffer,sizeof(mBuffer)),
        boost::bind(&ServTCP::HandleAccept,
                    this,
                    boost::asio::placeholders::error,
                    sp)
    );
}
void ServTCP::HandleAccept(const boost::system::error_code& ec,SockPtr sp){
    
    //处理客户端accept
        /*
            RPC服务器的操作在这里
        */
        //buffere中数据的格式一定是DynamicSo/interface.h/NetMsg 的格式，客户端也要遵守这个格式打包数据
        if(ec){
            msg(error,(boost::format("%1%:%2% has disconnect.")
                %sp->remote_endpoint().address().to_string()
                %sp->remote_endpoint().port()).str()
            );
            sp->close();
            sp.reset();
            return;
        }
        memcpy(&nm,mBuffer,sizeof(nm));
        msg(info,(boost::format("%1%:%2% Call:【%3%】")
                %sp->remote_endpoint().address().to_string()
                %sp->remote_endpoint().port()
                %std::string(nm.FuncName)).str()
        );
        if(!dynamicFunc.SoisExist(nm.FuncName)){  //如果so不存在
            rm.msgType=DonotExist;              //告知客户端不存在该过程
            msg(error,"Func .So doesn't exist");
        }
        else{
            rm.msgType=Success;
            dynamicFunc.Call(                       //获取动态调用
                nm.FuncName,
                nm.Param,
                rm.data
            );
            //处理完成,结果存放在rm.data中，发回给客户端，然后客户端再根据自己传的数据来自己解析
        }
        memcpy(mBuffer,&rm,sizeof(rm));     //填充到缓冲区等待发送
        sp->async_write_some(
            boost::asio::buffer(mBuffer,sizeof(mBuffer)),
            boost::bind(
                &ServTCP::HandleRead,
                this,
                ec,
                sp
            )
        );
    
}   
//////////////////////////////////////////////////////////////////////////////////
//UDP处理
void ServUDP::accept(){     //接收客户端发送的消息
    mServerSocket.async_receive_from(
        boost::asio::buffer(mBuffer,sizeof(mBuffer)),       //往已经申请好的buffer中写入
        mClientEndpoint,                                    //client的端点
        boost::bind(        //绑定回调函数
            &ServUDP::HandleAccept,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
        )
    );
}
void ServUDP::HandleAccept(const boost::system::error_code& ec, int size){
    //处理客户端accept

    mServerSocket.async_send_to(
        boost::asio::buffer("Server has get your UDP request"),
        mClientEndpoint,
        boost::bind(
            &ServUDP::HandleNull,
            this
        )
    );
    //doing...
    accept();       //处理完成后继续监听
}   
