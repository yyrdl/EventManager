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
void fucn(Arguments*p)//�޲����Ͷ����ʱ��ҲҪ����ʽ��д�ϲ�����C++��������������������Կ�����Ĭ�ϴ��ģ����Ǹ���
{
  ABC tt;
  tt.sefintr(p);
  cout<<"�޲����Ͳ���"<<endl;
}
int main()
{
     Event_Manager myEventPool;

     tt p(6897,686);
     Arguments_Package<tt*>arguments(&p);//��װ�ص������Ĳ���
     typedef void(*f1)(Arguments*);
     Callback_Package<f1>func(output);//��װ�ص�����
     myEventPool.on("event1",&func);//ע���¼����󶨻ص�����
     myEventPool.emit("event1",&arguments);//�����¼����������ص�����
     myEventPool.removeEventListener("event1");//ע���¼�
     myEventPool.removeEventListener("unexistEvent");//����ע���������¼�
     myEventPool.emit("event1");//���Լ����Ѿ�ɾ���¼�

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
