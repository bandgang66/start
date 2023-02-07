#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <functional> //
using namespace std;

//functional, 

//создадим 5 стандартных функций==================================

// 1
void funcVoid()
{
    cout<<"funcVoid() - START "<<endl;
    cout<<"funcVoid() - FINISH "<<endl;
}

// 2
void funcVoidParam(int a, int b)
{
    cout<<"funcVoidParam() - START "<<endl;
    cout<<"a = "<<a<<", b = "<<b<<endl;
    cout<<"funcVoidParam() - FINISH "<<endl;
}

//3
int funcIntParam(int a, int b)
{
    cout<<"funcIntParam() - START "<<endl;
    cout<<"a = "<<a<<", b = "<<b<<endl;
    cout<<"funcIntParam() - FINISH "<<endl;
    return a+b;
}

//4
void funcVoidParamRef(int &a,int &b)
{
    cout<<"funcVoidParamRef() - START "<<endl;
    cout<<"a = "<<a<<", b = "<<b<<endl;
    ++a;++b;
    cout<<"a = "<<a<<", b = "<<b<<endl;
    cout<<"funcVoidParamRef() - FINISH "<<endl;
}

void massiveWork(int *mass,int size)
{
    cout<<"funcIntParam() - START "<<endl;
    for(int i=0;i<size;++i){++mass[i];}
    cout<<"funcIntParam() - FINISH "<<endl;

}


// функции для массива указателей на функции=====================
void foo1(int a){++a;cout<<"foo1 ++a work = "<< a <<endl;}
void foo2(int a){--a;cout<<"foo1 --a work = "<< a <<endl;}
void foo3(int a){a*=a;cout<<"foo1 a*=a work = "<< a <<endl;}
void foo4(int a){a/=a;cout<<"foo1 a/=a work = "<< a <<endl;}

// функции для передачи как аргумент параметру функции фанкшн
int fun1(int a){return ++a;}
int fun2(int a){return --a;}
int fun3(int a){return a*=a;}
int fun4(int a){return a/=a;}

//функция где фанкшн параметр
void functional(int a,function<int(int)> funkl){cout<<funkl(a)<<endl;}



int main(int argc,char* argv[])
{   
    //необходимые переменные=======================================
    int a=5,b=7;
    int sum=0;
    const int size = 5;
    int mass[size]={1,1,1,1,1};

    // обьявление function======================================
    function<void()> funkl_Void;
    function<void(int,int)> funkl_VoidParam;
    function<int(int, int)> funkl_IntParam;
    function<void(int&,int&)> funkl_VoidParamRef;
    function<void(int*,int)> funkl_massive;

    //присваиваем указателям адреса функций=========================
    funkl_Void = funcVoid;
    funkl_VoidParam = funcVoidParam;
    funkl_IntParam = funcIntParam;
    funkl_VoidParamRef = funcVoidParamRef;
    funkl_massive = massiveWork;

   //использование===========================
    //1
    funkl_Void();

    //2
    funkl_VoidParam(a,b);

    //3
    sum = funkl_IntParam(a,b);
    cout<<"sum = "<<sum<<endl;

    //4
    cout<<"a = "<<a<<", b = "<<b<<endl;
    funkl_VoidParamRef(a,b);
    cout<<"a = "<<a<<", b = "<<b<<endl;

    //5
    for(int i=0;i<size;++i){cout<<"-+- "<<mass[i]<<" -+-"<<endl;}
    funkl_massive(mass,size);
    for(int i=0;i<size;++i){cout<<"-+- "<<mass[i]<<" -+-"<<endl;}
    
    //  ПРИмер испозования массива указателей на функции 
    int x = 10;
    function<void(int)> funk[4] = {foo1,foo2,foo3,foo4};
    int length = sizeof(funk)/sizeof(funk[0]);
    for(int i=0;i<length;++i){ funk[i](x); }

        
    //пример когда фанкшн преедается как параметр
    int y=50;
    functional(y,fun1);
    functional(y,fun2);
    functional(y,fun3);
    functional(y,fun4);



   
}




