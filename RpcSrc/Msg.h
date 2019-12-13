#ifndef _MSG_H_
#define _MSG_H_
#include <iostream>
#include <string>
    enum msg_type
    {
        info,
        error,
        success
    }; //枚举的消息类型
    void msg(msg_type type, std::string msg)
    {
        //向服务器控制台发送消息

        switch (type)
        {
        case info:
        {
            std::cout << "\033[34m"
                      << "【info】"
                      << "\033[37m\t" << msg << "\033[0m" << std::endl;
            break;
        }
        case error:
        {
            std::cout << "\033[31m"
                      << "【error】"
                      << "\033[37m\t" << msg << "\033[0m" << std::endl;
            break;
        }
        case success:
        {
            std::cout << "\033[32m"
                      << "【success】"
                      << "\033[37m\t" << msg << "\033[0m" << std::endl;
            break;
        }
        }
    }
#endif