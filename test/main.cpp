#include <iostream>
//#include<string>
#include<myEvent.h>
using namespace std;
using namespace My_Event;
class tt
{
private:
     int name;
public:
     int id;
    tt( int str,int d)
    {
        name=str;
        id=d;
    }
    void dis()
    {
        cout<<name<<endl;
    }
};
void output(Arguments *tar)
{
     tt *p=(tt*)tar->getArgumentsPointer();
     p->dis();
     cout<<p->id<<endl;
}
class ABC
{
 private:
     int abc;
 public:
    int description;
    ABC()
    {
        abc=8798;
        description=878998;
    }
    void dis()
    {
        cout<<abc<<"  "<<description<<endl;
    }
    void sefintr(Arguments*tar)
    {
        cout<<"inside ABC"<<endl;
    }
};
void outt(Arguments *tar)
{
    ABC *p=(ABC*)tar->getArgumentsPointer();
    p->dis();
}
void fucn(Arguments*p)//无参类型定义的时候也要在形式上写上参数，C++必须声明，这个参数可以看成是默认带的，就是个壳
{
  ABC tt;
  tt.sefintr(p);
  cout<<"无参类型测试"<<endl;
}
int main()
{
     Event_Manager myEventPool;

     tt p(6897,686);
     Arguments_Package<tt*>arguments(&p);//包装回调函数的参数
     typedef void(*f1)(Arguments*);
     Callback_Package<f1>func(output);//包装回调函数
     myEventPool.on("event1",&func);//注册事件并绑定回调函数
     myEventPool.emit("event1",&arguments);//激发事件，并触发回调函数
     myEventPool.removeEventListener("event1");//注销事件
     myEventPool.removeEventListener("unexistEvent");//测试注销不存在事件
     myEventPool.emit("event1");//测试激发已经删除事件

     ABC *pp=new ABC;
     typedef void(*f2)(Arguments*);
     Arguments_Package<ABC*>arguments2(pp);
     Callback_Package<f2>func2(outt);
     myEventPool.on("fire",&func2);
     myEventPool.emit("fire",&arguments2);

     typedef void(*f3)(Arguments*);
     f3 ff3=fucn;
    //void(*f3)(Arguments*);
    //f3=fucn;
     Callback_Package<f3>f3package(ff3);
     myEventPool.on("event3",&f3package);
     myEventPool.emit("event3");

     delete pp;
    return 0;
}
