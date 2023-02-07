#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <functional>
using namespace std;

//указатель на функцию, functional, лмбда-выражение================

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





int main(int argc,char* argv[])
{   
    //необходимые переменные=======================================
    int a=5,b=7;
    int sum=0;
    const int size = 5;
    int mass[size]={1,1,1,1,1};

    // обьявление указателей======================================
    void(*ptrVoid)();
    void(*ptrVoidParam)(int,int);
     int(*ptrIntParam)(int,int);
    void(*ptrVoidParamRef)(int&,int&);  //параметры должны совпадать
    void(*ptrMassiveWork)(int*,int);

    //присваиваем указателям адреса функций=========================
    ptrVoid = funcVoid;
    ptrVoidParam = funcVoidParam;
    ptrIntParam = funcIntParam;
    ptrVoidParamRef = funcVoidParamRef;
    ptrMassiveWork = massiveWork; 

    //использование===========================
    //1
    ptrVoid();

    //2
    ptrVoidParam(a,b);

    //3
    sum = ptrIntParam(a,b);
    cout<<"sum = "<<sum<<endl;

    //4
    cout<<"a = "<<a<<", b = "<<b<<endl;
    ptrVoidParamRef(a,b);
    cout<<"a = "<<a<<", b = "<<b<<endl;

    //5
    for(int i=0;i<size;++i){cout<<"-+- "<<mass[i]<<" -+-"<<endl;}
    ptrMassiveWork(mass,size);
    for(int i=0;i<size;++i){cout<<"-+- "<<mass[i]<<" -+-"<<endl;}
    
    //  ПРИмер испозования массива указателей на функции 
    int x = 10;
    void(*operations[4])(int) = {foo1,foo2,foo3,foo4};
    int length = sizeof(operations)/sizeof(operations[0]);
    for(int i=0;i<length;++i){ operations[i](x); }

        




   
}




