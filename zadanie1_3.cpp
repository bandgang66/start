#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <string.h>


/*
Задание 3
Разработайте приложение, которое умеет запускать 
дочерний процесс и передавать ему аргументы командной 
строки. В качестве аргументов должно быть два числа 
и операция, которую необходимо выполнить. Например, 
аргументы:
■ 7;
■ 3;
■ +.
Дочерний процесс должен отобразить аргументы 
и вывести результат сложения 10 на экран.
*/



using namespace std;



int main(int argc,char* argv[])
{
   
  
    int pid = fork();


    if(argc>1)
    {
        if(pid)
        {
        int first,second;
        first = atoi(argv[1]);
        second = atoi(argv[3]);
            if(strcmp(argv[2],"+")==0)
            {   
                cout<<"summa: "<<first+second<<endl;
                return first+second;
            }

        }
        else
        {
            return 0;
        }
    }
     
   
}
