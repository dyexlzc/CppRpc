#ifndef _DF_H_
#define _DF_H_
#include "../DynamicSo/dLoad.hpp"   //引入ds文件

////////////////////////////////////////////////////////
class DynamicFunc{
    std::string soPath;
    dynamicLoader loader;
public:
    DynamicFunc(std::string SoPath):soPath(SoPath),loader(SoPath){
        //定义类和参数so文件的存放位置
    }
    //因为DF模块面对的是来自网络上的数据，因此必须有一种有效的方法来从比特流中重构数据
    void Call(std::string FuncName,char* buffer,char* returns){
        //1.通过FuncName动态加载Func所对应的Class以及Param所对应的Class
        //2.因此，客户端和服务器必须有一份同样的Class来描述参数的数据结构

        //1.加载函数所在的so,因为我们把函数包装在类里，所以先把函数的实例获取出来
        std::string FuncSoName=FuncName+".so";
        loader.load(FuncSoName);
        interface *p=loader.getInstance(FuncSoName);        //取得函数的实例
        //2.现在函数已经取出来，只需要把buffer填入run的参数(buffer)中即可，计算和对buffer的操作将在run中由用户手动memcpy格式化到struct/class中
        p->run(buffer,returns);
        //由so内部将结果存放到returns中, 指针returns是一个由调用者按照so中的调用规范所申请的一个内存地址。
        //因此计算完成后，returns的内存地址中存放的就是计算结果了
    }
};
#endif