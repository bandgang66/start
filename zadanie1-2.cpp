#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <chrono>
#include <thread>




/*
	Задание 2. Разработайте приложение, которое отображает спи-
сок процессов. Пользователь может указать временной
интервал для обновления списка.
Добавьте к первому заданию возможность выбора
конкретного процесса в списке.
При выборе процесса отображается детальная ин-
формация о нём. Например:
■ Идентификатор процесса;
■ Время старта;
■ Общее количество процессорного времени, потра-
ченного на этот процесс;
■ Количество копий процесса такого вида (если у вас
запущено пять консолей, должно появиться число
пять).
■ возможность заверше-
ния выбранного процесса.

*/


static int EXIT = 1;





using namespace std;




void scanTerminal(vector<string> &list, const char *command = "ps a")   //функция для чтения из терминала
{
    FILE *ptrProc = popen(command,"r");

    while(!feof(ptrProc))
    {
        char buff[200];
        fgets(buff,200,ptrProc);
        list.emplace_back(buff);
    }    

    fclose(ptrProc);
}

void showVector(vector<string> list)
{
    int count=0;

    while(EXIT)
    {
        
        system("clear");
        for(auto x:list)
        {
            cout<<x;
        }
        ++count;
        cout<<"=============== "<<count<<" =================="<<endl;    //так лучше видно что обновляестя
        this_thread::sleep_for(chrono::milliseconds(2000));


    }
}



int main(int argc,char** argv)
{
    vector<string> list;
    string command;
    string name;
    int vibor;

    cout<<"===================== MENU ======================\n"
        <<"Dlya vivoda vseh procesov vvedite...........1\n"
        <<"Dlya vibora konkretnogo processa vvedite....2\n"
        <<"Dlya vihoda vvedite........................0\n";
    cin>>vibor;


    switch(vibor)
    {
        case 1:
        list.clear();
        scanTerminal(list);
        showVector(list);
        break;
        
        case 2:
        list.clear();
        cout<<"Vvedite imya processa: "<<endl;
        cin>>name;
        command="ps ax | grep "+name;
        scanTerminal(list,command.c_str());
        showVector(list);
        break;

        case 0:
        EXIT=0;
        break;

        default:
        cout<<"NEVERNIY VVOD"<<endl;
        break;
    }

    return 0;
}
