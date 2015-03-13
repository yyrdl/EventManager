# EventManager
学node.js 的时候接触到事件类这个东东，顿时就爱上了。苦于C++中没有这样的库，而且C++又是强类型语言，很是抓狂啊。

##My_Event
```bash
命名空间
a namespace named My_Event
```
##Event_Manager
```bash
和 int double 一样用于声明事件池
```
##Arguments
```bash
   回调函数的形参类型声明符，用法参加示例
```
##Arguments_Package
```bash
类名，用于包装传入回调函数的参数
```
##Callback_Package
```bash
 类名，包装回调函数
```
##Event.on(eventName,callback)
```bash
   注册监听事件，用法见示例
```
##Event.emit(eventName,arguments) &&Event.emit(eventName)
```bash
    激发相应事件,并传递相应参数
```
##Event.removeEventListener(eventName)
```bash
  移除事件监听
```
```c++
  #include <myEvent.h>
  using namespace My_Event;
  
  //then set two class and function
   
   class Class1{
      private:
        int name;
      public:
        int id;
        Class1( int str,int d)
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
     Class1 *p=(Class1*)tar->getArgumentsPointer();//important
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
  
  void display(Arguments *tar)
  {
    ABC *p=(ABC*)tar->getArgumentsPointer();//important
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
     Class1 p(6897,686);

     Arguments_Package<Class1*>arguments(&p);//包装回调函数的参数
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
     Callback_Package<f2>func2(display);
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
 
```
