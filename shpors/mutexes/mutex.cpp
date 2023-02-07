#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;



mutex mtx_lock_unlock;
mutex mtx_lock_guard;
mutex mtx_deadlock_1;
mutex mtx_deadlock_2;
recursive_mutex rm; //блокриуется и разблокируется не один раз, но сколько заблок столько и разблок
mutex mtx_uniq_lock;


//lock, unlock
void Print_lock_unlock(char ch)
{   //тут будут работать 2 потока
    this_thread::sleep_for(chrono::milliseconds(2000));

    //начало критической секции где будет работать только один поток
    mtx_lock_unlock.lock();
    for(int i=0;i<5;++i)
    {
        for(int j=0;j<10;++j)
        {
            cout<<ch;
            this_thread::sleep_for(chrono::milliseconds(20));
        }
        cout<<endl;
    }
    cout<<endl;
    mtx_lock_unlock.unlock();
    //конец критической секции где будет работать один поток

    //тут будут работать 2 потока
    this_thread::sleep_for(chrono::milliseconds(2000));
}

//lock_guard;
void Print_lock_guard(char ch)
{   //лок_гуард предназначен для полной асинхронизации функции
    //начало критической секции где будет работать только один поток
    lock_guard<mutex> guard(mtx_lock_guard); //создаем обьект и помещаем туда мьютекс, теперь он пойман
    //что бы сделать как лок анлок и выделить область которую нужно заблокрировать просто засунуть вместе с 
    //лок гвардом в {}, потому что при выходе с области выдимости вызываются диструкторы
    for(int i=0;i<5;++i)
    {
        for(int j=0;j<10;++j)
        {
            cout<<ch;
            this_thread::sleep_for(chrono::milliseconds(20));
        }
        cout<<endl;
    }
    cout<<endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
    //конец критической секции где будет работать один поток
    //по завершении сработает диструктор обьекта лок_гвард и мьютекс освободится
}

//deadlock взаимная блокировка

void Print_deadlock_1()
{   //
    mtx_deadlock_1.lock(); //блокируется тем что в разном порядке вызваются 
    this_thread::sleep_for(chrono::milliseconds(1)); //нре сработает если не замедлить
    mtx_deadlock_2.lock();

    for(int i=0;i<5;++i)
    {
        for(int j=0;j<10;++j)
        {
            cout<<"*";
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        cout<<endl;
    }
    cout<<endl;
    mtx_deadlock_1.unlock();
    mtx_deadlock_2.unlock(); 
}

void Print_deadlock_2()
{
    mtx_deadlock_1.lock();  //выставив такой же порядок мы утсраняем блокировку
    this_thread::sleep_for(chrono::milliseconds(1));
    mtx_deadlock_2.lock();

    for(int i=0;i<5;++i)
    {
        for(int j=0;j<10;++j)
        {
            cout<<"#";
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        cout<<endl;
    }
    cout<<endl;
    mtx_deadlock_1.unlock();
    mtx_deadlock_2.unlock(); 
}


//recursive_mutex

void Foo_recursive_mutex(int a)
{
    rm.lock();
    cout<<a<<" ";
    this_thread::sleep_for(chrono::milliseconds(200));
    if(a<=1)
    {
        cout<<endl;
        rm.unlock();
        return;
    }
    a--;
    Foo_recursive_mutex(a);
    rm.unlock();
}

//unique_lock
void Print_unique_lock(char ch)
{   
    unique_lock<mutex> uniqlock(mtx_uniq_lock,std::defer_lock); //обьект создался но не запустился лок

    this_thread::sleep_for(chrono::milliseconds(2000));

    uniqlock.lock(); //запустили лок
   // unique_lock<mutex> uniqlock(mtx_uniq_lock); //создался лок просто как лок_гвард
    
    for(int i=0;i<5;++i)
    {
        for(int j=0;j<10;++j)
        {
            cout<<ch;
            this_thread::sleep_for(chrono::milliseconds(20));
        }
        cout<<endl;
    }
    cout<<endl;

    uniqlock.unlock();  //если не сделать этого, то анлок вызовитс в момент уничтожения
    this_thread::sleep_for(chrono::milliseconds(2000));
   
}



int main(int argc,char* argv[])
{   cout<<"MAIN START"<<endl;
     cout<<"\n\n=-=-=-=-=-==-=-=LOCK UNLOCK-=-=-=-==-=-=-==-=-==\n\n";
    //время выполнения кода - start
    auto start = chrono::high_resolution_clock::now();

    thread th1(Print_lock_unlock,'x');
    thread th2(Print_lock_unlock,'o');
    thread th3(Print_lock_unlock,'z');

    cout<<"MAIN WORK Print_lock_unlock"<<endl;

    th1.join();
    th2.join();
    th3.join();

    //время выполнения кода - finsh
    auto finish = chrono::high_resolution_clock::now();
    //время выполнения кода - rezult
    chrono::duration<float> duration = finish - start;
    cout<<"Duration = "<<duration.count()<<" seconds"<<endl;

    cout<<"\n\n=-=-=-=-=-==-=-=LOCK GUARD-=-=-=-==-=-=-==-=-==\n\n";

    //время выполнения кода - start
    auto start2 = chrono::high_resolution_clock::now();

    thread th4(Print_lock_guard,'q');
    thread th5(Print_lock_guard,'b');
    thread th6(Print_lock_guard,'d');

    cout<<"MAIN WORK Print_lock_guard"<<endl;

    th4.join();
    th5.join();
    th6.join();

    //время выполнения кода - finsh
    auto finish2 = chrono::high_resolution_clock::now();
    //время выполнения кода - rezult
    chrono::duration<float> duration2 = finish2 - start2;
    cout<<"Duration = "<<duration2.count()<<" seconds"<<endl;

    cout<<"\n\n=-=-=-=-=-==-DEADLOCK=-=-=-=-=-==-=-=-==-=-==\n\n";

    //время выполнения кода - start
    auto start3 = chrono::high_resolution_clock::now();

    thread th7(Print_deadlock_1);
    thread th8(Print_deadlock_2);


    cout<<"MAIN WORK deadlock"<<endl;

    th7.join();
    th8.join();

    //время выполнения кода - finsh
    auto finish3 = chrono::high_resolution_clock::now();
    //время выполнения кода - rezult
    chrono::duration<float> duration3 = finish3 - start3;
    cout<<"Duration = "<<duration3.count()<<" seconds"<<endl;

     cout<<"\n\n=-=-=-=-=-==-RECURSIVE MUTEX=-=-=-=-=-==-=-=-==-=-==\n\n";

    //время выполнения кода - start
    auto start4 = chrono::high_resolution_clock::now();

    thread th9(Foo_recursive_mutex,10);
    thread th10(Foo_recursive_mutex,10);


    cout<<"MAIN WORK recursive_mutex"<<endl;

    th9.join();
    th10.join();

    //время выполнения кода - finsh
    auto finish4 = chrono::high_resolution_clock::now();
    //время выполнения кода - rezult
    chrono::duration<float> duration4 = finish4 - start4;
    cout<<"Duration = "<<duration4.count()<<" seconds"<<endl;


     cout<<"\n\n=-=-=-=-=-==-RECURSIVE MUTEX=-=-=-=-=-==-=-=-==-=-==\n\n";

    //время выполнения кода - start
    auto start5 = chrono::high_resolution_clock::now();

    thread th11(Print_unique_lock,'<');
    thread th12(Print_unique_lock,'>');


    cout<<"MAIN WORK recursive_mutex"<<endl;

    th11.join();
    th12.join();

    //время выполнения кода - finsh
    auto finish5 = chrono::high_resolution_clock::now();
    //время выполнения кода - rezult
    chrono::duration<float> duration5 = finish5 - start5;
    cout<<"Duration = "<<duration5.count()<<" seconds"<<endl;

    cout<<"MAIN FINISH"<<endl;
    return 0;
}




