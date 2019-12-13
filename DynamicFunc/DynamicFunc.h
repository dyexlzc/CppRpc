#ifndef _DF_H_
#define _DF_H_
#include "../DynamicSo/dLoad.hpp"   //引入ds文件
/////////////////////////////////////////////////////////
struct netMsg{                      //网络上传递过来调用函数格式
    char FuncName[20];              //函数名称
    char Param[1024];               //存放函数参数的缓冲区，至于函数参数将会被填充到什么样的结构体里需要动态加载so中的定义
};
////////////////////////////////////////////////////////
class DynamicFunc{
    std::string soPath;
    dynamicLoader loader;
public:
    DynamicFunc(std::string SoPath):soPath(SoPath),loader(SoPath){
        //定义类和参数so文件的存放位置
    }
    //因为DF模块面对的是来自网络上的数据，因此必须有一种有效的方法来从比特流中重构数据
    void Call(std::string FuncName,char* Param){
        //1.通过FuncName动态加载Func所对应的Class以及Param所对应的Class
        //2.因此，客户端和服务器必须有一份同样的Class来描述参数的数据结构

        //1.加载函数所在的so,因为我们把函数包装在类里，所以先把函数的实例获取出来
        std::string FuncSoName=FuncName+".so";
        loader.load(FuncSoName);
        interface *p=loader.getInstance(FuncSoName);        //取得函数的实例
        //2.现在函数已经取出来，需要再取出函数需要的参数列表
        
    }
};
#endif