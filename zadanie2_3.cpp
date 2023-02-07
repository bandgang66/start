#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <thread>
#include <random>
#include <fstream>

#define SIZE 10000

/*
	2.3 Консольное приложение генерирует набор чисел,

состоящий из 10000 элементов. С помощью механизма

потоков нужно найти максимум, минимум, среднее в этом

наборе.
Для каждой из задач выделите поток.

Добавьте поток, выводящий набор чисел и результаты вычислений в файл


*/


using namespace std;
random_device Rand;

//dlya raboti s filom
void file_write(int max_val,int min_val,int mid_val);
void file_read();



int generation(int *mass);
void show(int *mass);
int max(int *mass);
int min(int *mass);
int mid(int *mass);



int main(int argc,char* argv[])
{
    int massiv[SIZE];
    int min_val;
    int max_val;
    int mid_val;
    generation(massiv);
    show(massiv);
    cout<<"\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==\n";

    auto MAX=[&max_val](int *massive){max_val=max(massive);};
    auto MIN=[&min_val](int *massive){min_val=min(massive);};
    auto MID=[&mid_val](int *massive){mid_val=mid(massive);};

    thread th1(MAX,massiv);
    thread th2(MIN,massiv);
    thread th3(MID,massiv);
    th1.join();
    th2.join();
    th3.join();

    thread th4(file_write,max_val,min_val,mid_val);
    cout<<"max_val = "<<max_val<<endl;
    cout<<"min_val = "<<min_val<<endl;
    cout<<"mid_val = "<<mid_val<<endl;
    th4.join();

    cout<<"\n================================================\n"<<endl;
    file_read();




    return 0;
   
}


int generation(int *mass)
{
    for(int i = 0;i<SIZE;++i)
    {
        *(mass+i)=Rand()%99;
    }
    return *mass;
}

void show(int *mass)
{
    for(int i = 0;i<SIZE;++i)
    {
        cout<<*(mass+i)<<endl;
    }
}

int max(int *mass)
{
    int max=mass[0];

    for(int i=0;i<SIZE-1;++i)
    {
        if(max<mass[i+1])
        {
            max=mass[i+1];
        }
    }
    return max;

}

int min(int *mass)
{
    int min=mass[0];

    for(int i=0;i<SIZE-1;++i)
    {
        if(min>mass[i+1])
        {
            min=mass[i+1];
        }
    }
    return min;

}

int mid(int *mass)
{
    int mid=0;
    for(int i=0;i<SIZE;++i)
    {
        mid+=mass[i];
    }

    mid/=SIZE;

    return mid;
}

void file_write(int max_val,int min_val,int mid_val)
{
    cout<<"thread 3(FILE WRITE) start work,  id = "<<this_thread::get_id()<<endl;

    string path = "/home/dima/dir_file/nums3.txt";
    fstream file;
    file.open(path.c_str(),ios::out);
    if(!file.is_open())
    {
        cout<<"file NOT open"<<endl;
    }
    else
    {
        file<<"max_val = "<<max_val<<endl;
        file<<"min_val = "<<min_val<<endl;
        file<<"mid_val = "<<mid_val<<endl;
    }
    cout<<"thread 3(FILE WRITE) end work,  id = "<<this_thread::get_id()<<endl;
    file.close();
    
}

void file_read()
{
    string path = "/home/dima/dir_file/nums3.txt";
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
