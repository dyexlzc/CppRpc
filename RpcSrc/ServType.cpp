/*
    实现TCP/UDP服务器接口
*/
#include "ServType.h"
#include "Msg.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>
#include <iostream>

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
                    sp,
                    boost::asio::placeholders::bytes_transferred)
    );
}
void ServTCP::HandleAccept(const boost::system::error_code& ec,SockPtr sp,int size){
    if(size==0){        //telnet在断开时会发送一个0字节的tcp包，必须在这里处理
        char port_[5];
        sprintf(port_,":%d",sp->remote_endpoint().port);
        msg(error,sp->remote_endpoint().address().to_string()+port_+" has disconnected.");
        sp->close();
        sp.reset();     //reset析构socket对象
        return;
    }

    //处理客户端accept
    /*
        RPC服务器的操作在这里
    */
    
    sp->async_write_some(
        boost::asio::buffer("Server has get your TCP request"),
        boost::bind(
            &ServTCP::HandleRead,
            this,
            ec,
            sp
        )
    );
    //doing...
    
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
