#include<iostream>
#include"DynamicFunc.h"
/*
    动态加载so调用函数并且返回结果示例
*/
using namespace std;
struct param_Add{
    int a,b;
};
int main(){
    DynamicFunc df("../CppdynamicLoad/");//指定so文件的位置
    int result;             //申请内存保存结果
    struct param_Add pa;    //和服务端保持一致的参数格式
    cin>>pa.a>>pa.b;
    df.Call("add",(char*)&pa,(char*)&result);   //远程调用函数
    cout<<result;
    return 0;
} 