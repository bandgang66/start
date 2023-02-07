#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <vector>
#include <fstream>
#include <cstring>


/*
Задание 4
Разработайте приложение, которое умеет запускать 
дочерний процесс и передавать ему аргументы командной 
строки. В качестве аргументов должны быть путь к файлу 
и слово для поиска. Например, аргументы:
■ /home/someFolder/someFile;
■ bicycle.
Дочерний процесс должен отобразить количество раз, 
сколько слово bicycle встречается в файле.

*/


using namespace std;

void filework(vector<string> &vec,string path)
{


    FILE *ptr = fopen(path.c_str(),"r");
    char buff[256];

    if(!ptr)
    {

        cout<<"file not open"<<endl;
    }
    
    while((fgets(buff,256,ptr))!=NULL)
    {
        vec.emplace_back(buff);
    }
    

    fclose(ptr);
}

void show(vector<string> vec)
{
    for(auto x:vec)
    {
        cout<<x;
    }

}

int counter_word(vector<string> vec, string word)
{
    int i=0;
    for(auto str:vec)
    {
        if((strstr(str.c_str(),word.c_str())!=NULL))
        {
            ++i;
        }
    }
    return i;
}


int main(int argc,char* argv[])
{
    
    vector<string> v;
    int pid = fork();
    if(argc>1)
    {
        if(pid)
        {
        string path,word;
        path = argv[1];
        word = argv[2];
        filework(v,path);
        show(v);
        cout<<"\n\n\n======V FILE : "<<path<<" NAYDENO: "<<counter_word(v,word)<<" SLOV: "<<word<<endl;
        }
        else
        {
            return 0;
        }
    }
}
