#ifndef MYEVENT_H_
#define MYEVENT_H_
#include<string>
namespace My_Event
{
   class Arguments
  {
        protected:
        long *Bridge;
        public:
            long *getArgumentsPointer()
            {
                return Bridge;
            }
   };

   class Base_Function
  {
      public:
      Base_Function(){};
      virtual void do_CallBack(Arguments *tar)=0;
	  virtual void do_CallBack()=0;

  };
//参数包装类
  template<typename Arguments_Type>
  class Arguments_Package:public Arguments
  {
       public:
      Arguments_Package (Arguments_Type tar)
      {
          Bridge=(long*)tar;
      }
       Arguments_Type getArgumentsPointer()
      {
          return ((Arguments_Type)Bridge);
      }
  };

//回调函数包装类
  template <typename FUNCTION_TYPE>
  class  Callback_Package:public Base_Function
  {
    private:
        FUNCTION_TYPE func;
    public:
        Callback_Package(FUNCTION_TYPE f)
       {
           if(f)
            func=f;
           else
            func=0;
       }
       void operator=(const FUNCTION_TYPE tar)
       {
           func=tar;
       }
       void do_CallBack();
       void do_CallBack(Arguments*  arguments);
  };
  template<typename FUNCTION_TYPE>
  void Callback_Package<FUNCTION_TYPE>::do_CallBack()
  {
    //std::cout<<"do callback()"<<std::endl;
    Arguments *p=0;
    if(func)
     (*func)(p);
  }
  template <typename FUNCTION_TYPE>
  void  Callback_Package<FUNCTION_TYPE>::do_CallBack(Arguments* arguments)
  {
    if(func)
    (*func)(arguments);
  }

//事件池
  class Event_Manager
 {
   private:
       Base_Function *POOL[100];
       std::string  Event_name[100];
       int num;
  public:
      Event_Manager()
      {
          num=0;
      }
      bool on(std::string event_name,Base_Function  *func);
      bool emit(std::string event_name,Arguments* arguments);
      bool emit(std::string event_name);
	  bool removeEventListener(std::string event_name);
 };
 bool Event_Manager::on(std::string event_name,Base_Function  *func)
 {
  int i=0;
  bool tag=false;
  if(num==100)
  {
    std::cout<<"WARNING:Event Pool Overflow!"<<std::endl;
	return false;
  }
  for(;i<num;i++)
  {
      if(Event_name[i]==event_name)
      {
          std::cout<<"The event has already exist!"<<std::endl;
          tag=false;
          break;
      }
  }
  if(i==num)
    for(i=0;i<num+1;i++)
  {
      if(Event_name[i]=="")
	  {
	     Event_name[i]=event_name;
         POOL[i]=func;
         ++num;
		 tag=true;
		 break;
	  }
  }
   return tag;
 }
 bool Event_Manager::emit(std::string event_name)
 {
    //std::cout<<"event1"<<std::endl;
   int i=0;
   bool tag=false;
   for(;i<num;i++)
   {
      if(Event_name[i]==event_name)
      {
          POOL[i]->do_CallBack();
          tag=true;
          break;
      }
  }
  if(!tag)
  std::cout<<"The Event '"<<event_name<<"' doesn't exist!"<<std::endl;
  return tag;
 }
 bool Event_Manager::emit(std::string event_name,Arguments  *arguments)
 {
  int i=0;
  bool tag=false;
  for(;i<num;i++)
  {
      if(Event_name[i]==event_name)
      {
	      if(arguments)
          {
		   POOL[i]->do_CallBack(arguments);
           tag=true;
		  }else
		  {
		   std::cout<<"WARNING: Arguments needed!"<<std::endl;
		    return false;
		  }
          break;
      }
  }
  if(!tag)
  std::cout<<"The Event '"<<event_name<<"' doesn't exist!"<<std::endl;
  return tag;
 }
 bool Event_Manager::removeEventListener(std::string event_name)
 {
  bool tag=false;
   for(int i=0;i<num;i++)
   {
    if(Event_name[i]==event_name)
	{
	  Event_name[i]="";
	  POOL[i]=0;
	  tag=true;
	  break;
	}
   }
   if(!tag)
   std::cout<<"Failed to remove unregistered event: "<<event_name<<" !"<<std::endl;
   return tag;
 }
}
#endif
