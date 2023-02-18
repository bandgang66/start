#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <cstring>
#include <chrono>
#include <thread>

/*
	2.1 Создайте приложение, порождающее

поток. Этот поток должен отображать в консоль числа

от 0 до 50

Для каждой из задач выделите поток.

Добавьте поток, выводящий набор чисел и результаты вычислений в файл
	
*/


using namespace std;

void nums();
void file_write();
void file_read();


int main(int argc,char* argv[])
{

    thread th1(nums);
    thread th2(file_write);
    cout<<"thread 1 start work,  id = "<<this_thread::get_id()<<endl;
    this_thread::sleep_for(chrono::milliseconds(5500));
    cout<<"thread 1 end work,  id = "<<this_thread::get_id()<<endl;
    th1.join();
    th2.join();
    cout<<"\n================================================\n"<<endl;

    file_read();


    return 0;
   
}

void nums()
{
    int i=0;
    cout<<"thread 2 start work,  id = "<<this_thread::get_id()<<endl;
    while(i<=50)
    {
        cout<<"i = "<<i<<endl;
        ++i;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout<<"thread 2 end work,  id = "<<this_thread::get_id()<<endl;
}

void file_write()
{
    cout<<"thread 3(FILE WRITE) start work,  id = "<<this_thread::get_id()<<endl;

    string path = "/home/dima/dir_file/nums.txt";
    fstream file;
    file.open(path.c_str(),ios::out);
    if(!file.is_open())
    {
        cout<<"file NOT open"<<endl;
    }
    else
    {
        for(int i=0;i<50;++i)
        {
            file<<i<<endl;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
    cout<<"thread 3(FILE WRITE) end work,  id = "<<this_thread::get_id()<<endl;
    file.close();
    
}

void file_read()
{
    string path = "/home/dima/dir_file/nums.txt";
    fstream file;
    file.open(path.c_str());
    if(!file.is_open())
    {
        cout<<"file NOT open"<<endl;
    }
    else
    {
        char* buff = nullptr;
        buff=new char[256];
        while(!file.eof())
        {
            file.getline(buff,256);
            cout<<buff<<endl;
        }

    }


    file.close();
}
