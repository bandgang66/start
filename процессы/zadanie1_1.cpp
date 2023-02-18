#include <iostream>
#include <stdlib.h>
#include <unistd.h>

/*
Задание 1. Разработайте приложение, которое предоставляет
пользователю возможность запуска других приложений.
Пользователь может запустить:
■ Блокнот;
■ Калькулятор;
■ Paint;
■ Своё собственное другое приложение.

*/


using namespace std;


int main(int argc,char** argv)
{
    int choice=0;
    int exit=1;
    char prog[100];
    char yesno=' ';
   

    while(exit)
    {
        system("clear");

        cout<<"vibirite programu iz spiska:"<<endl
        <<"bloknot......................1"<<endl
        <<"calculatror..................2"<<endl
        <<"paint........................3"<<endl
        <<"enter your programm..........4"<<endl;

        cin>>choice;

        switch(choice)
        {
        case 1:
        system("gedit");
        break;
        case 2:
        system("gnome-calculator");
        break;
        case 3:
        system("mypaint");
        break;
        case 4:
        cout<<"enter programm name:"<<endl;
        cin>>prog;
        system(prog);
        break;
        default:
        cout<<"ne verniy vvod"<<endl;
        break;
        }

        cout<<"DO YOU WANT EXIT? Y/N"<<endl;

        cin>>yesno;
        if(yesno=='y'||yesno=='Y')
            exit=0;
        else if(yesno=='n'||yesno=='N')
            exit=1;

        

    }


   
    return 0;
}
