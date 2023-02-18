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
#include <random>

/*
	2.2 Создайте приложение, генерирующее набор

простых чисел в диапазоне, указанном пользователем. Количество чисел тоже указывается пользователем.

Используйте механизм потоков. Числа сохраняться в массиве, выводятся по завершении потока

Для каждой из задач выделите поток.

Добавьте поток, выводящий набор чисел и результаты вычислений в файл

*/

static int count=0; //counter dlya vectorov

using namespace std;

//dlya raboti s filom
void file_write(vector<int> &massiv);
void file_read();

//funkcii dlya 2h potokov
void poisk_natur_1(int range_min, int range_max, vector<int> &massiv);
void poisk_natur_2(int range_min, int range_max, vector<int> &massiv);
void show_vector(vector<int> vec);

//funkcii dlya odnogo potoka
int poisk_natur_num(int range_min, int range_max);
int natural_nums(int range_min, int range_max, int *mass, int size);


int main(int argc,char* argv[])
{
    int range_min=2;              //min range
    int range_max=1;              //max range


    //proverka vvoda===============================================================
    while((range_min>range_max)||(range_min<=0)||(range_max<=0)){
        cout<<"Enter min range: "<<endl;
        cin>>range_min;
        cout<<"Enter max range"<<endl;
        cin>>range_max;

      if((range_min>range_max)||(range_min<=0)||(range_max<=0))
        cout<<"\n!!!vveden ne verniy diapozon!!!\n"<<endl;
    }

    //PROVERKA SLOZHNOSTI=============================================================
    if(range_max-range_min>999)    //esli bolshe 9999 to nujen 2 potok
    {   
    vector<int> massiv1;
    vector<int> massiv2;

    thread th1(poisk_natur_1,range_min,range_max,ref(massiv1));
    thread th2(poisk_natur_2,range_min,range_max,ref(massiv2));

    th1.join();
    th2.join();

    //concatinaziya vectorov
    vector<int> massivSum;
    massivSum.reserve(massiv1.size()+massiv2.size());
    massivSum.insert(massivSum.end(),massiv1.begin(),massiv1.end());
    massivSum.insert(massivSum.end(),massiv2.begin(),massiv2.end());

    thread th3(file_write,ref(massivSum));
    show_vector(massivSum);
    th3.join();
    cout<<"\n================================================\n"<<endl;
    file_read();

    }
    else
    {
        //kolichestvo naturalnih chisel
        int size;
        size = poisk_natur_num(range_min,range_max);
        //sozdanie massiva naturalnih chisel
        int *mass = new int[size];
        *mass = natural_nums(range_min,range_max, mass, size);
        //vivod na ekran
        for(int i=0;i<size;++i)
        {
        cout<<i+1<<" -(1 potok) naturalnoe choslo = "<<mass[i]<<endl;
        }
    
        delete mass;
    }

    

    return 0;
   
}

///////////////////////////////========================================////////////////////////////////////////////

//funkcii dlya 2h potokov
void poisk_natur_1(int range_min, int range_max, vector<int> &massiv)
{
    int count_delitel=0;        //schetchik deleniy, doljno rovnyatsya 2

    for(int i=range_min;i<range_max/2;++i)    //podschet koli4estva naturalnih chisel;
    {
        if(i%2!=0)      //srazu otsekaem 4etnie
        {
            for(int j=i;j>=range_min;--j)
            {
                if(i%j==0)              //doljno delitsya bez ostatka
                {
                    ++count_delitel;    //natiralnoe delitysa na sebya i na 1, znachit tolko 2 delitelya
                }
            }
        

            if(count_delitel==2)        //natiralnoe delitysa na sebya i na 1, znachit tolko 2 delitelya
            {
                massiv.emplace_back(i);
            }
            count_delitel=0;
        }
    }
    
}

void poisk_natur_2(int range_min, int range_max, vector<int> &massiv)
{
    int count_delitel=0;        //schetchik deleniy, doljno rovnyatsya 2

    for(int i=(range_max/2);i<=range_max;++i)    //podschet koli4estva naturalnih chisel;
    {
        if(i%2!=0)      //srazu otsekaem 4etnie
        {
            for(int j=i;j>=range_min;--j)
            {
                if(i%j==0)              //doljno delitsya bez ostatka
                {
                    ++count_delitel;    //natiralnoe delitysa na sebya i na 1, znachit tolko 2 delitelya
                }
            }
        

            if(count_delitel==2)        //natiralnoe delitysa na sebya i na 1, znachit tolko 2 delitelya
            {
                massiv.emplace_back(i);
            }
            count_delitel=0;
        }
    }
    
}


void show_vector(vector<int> vec)
{
    //int i=0;
    for(auto v:vec)
    {
        cout<<count+1<<" -(2 potoka) naturalnoe choslo = "<<v<<endl;
        ++count;
    }
}
//funkcii dlya 1 potoka


int poisk_natur_num(int range_min, int range_max)
{
    int size=0;
    int count_delitel=0; 

    for(int i=range_min, count=0;i<=range_max;++i)    //podschet koli4estva naturalnih chisel;
    {
        if(i%2!=0)      //srazu otsekaem 4etnie
        {
            for(int j=i;j>=range_min;--j)
            {
                if(i%j==0)              //doljno delitsya bez ostatka
                {
                    ++count_delitel;    //natiralnoe delitysa na sebya i na 1, znachit tolko 2 delitelya
                }
            }
        

            if(count_delitel==2)    //natiralnoe delitysa na sebya i na 1, znachit tolko 2 delitelya
            {
               // mass[count]=i;      //zapisivaem v massiv
                ++size;
            }
            count_delitel=0;
        }
    }

    return size;
}

int natural_nums(int range_min, int range_max, int *mass, int size)
{
    
    int count_delitel=0; 

    for(int i=range_min, count=0;i<=range_max;++i)    //podschet koli4estva naturalnih chisel;
    {
        if(i%2!=0)      //srazu otsekaem 4etnie
        {
            for(int j=i;j>=range_min;--j)
            {
                if(i%j==0)              //doljno delitsya bez ostatka
                {
                    ++count_delitel;    //natiralnoe delitysa na sebya i na 1, znachit tolko 2 delitelya
                }
            }
        

            if(count_delitel==2)    //natiralnoe delitysa na sebya i na 1, znachit tolko 2 delitelya
            {
               mass[count]=i;      //zapisivaem v massiv
               ++count;
                
            }
            count_delitel=0;
        }
    }

    return *mass;
}


void file_write(vector<int> &massiv)
{
    cout<<"thread 3(FILE WRITE) start work,  id = "<<this_thread::get_id()<<endl;

    string path = "/home/dima/dir_file/nums2.txt";
    fstream file;
    file.open(path.c_str(),ios::out);
    if(!file.is_open())
    {
        cout<<"file NOT open"<<endl;
    }
    else
    {
        for(int i=0;i<massiv.size();++i)
        {
            file<<massiv[i]<<endl;
        }
    }
    cout<<"thread 3(FILE WRITE) end work,  id = "<<this_thread::get_id()<<endl;
    file.close();
    
}

void file_read()
{
    string path = "/home/dima/dir_file/nums2.txt";
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
