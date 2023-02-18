#include <iostream>
#include <unistd.h>
#include "libs1head.h"

using namespace std;


int main()
{
    for(int i=0;i<=100;++i)
        if(simple_num(i))
            cout<<i<<" - prostoe chislo"<<endl;

    cout<<"\n=-=-=-=-=-===-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=\n";

    for(int j=1100000;j>0;j/=10)
        cout<<"У числа: "<<j<<" - "<<digit(j)<<", разрядов"<<endl;
    
    cout<<"У числа: "<<0.5<<" - "<<digit(0.5)<<", разрядов"<<endl;

    cout<<"\n=-=-=-=-=-===-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=\n";

    if(degree(256))
        cout<<"число 256 степень двойки"<<endl;
    else
        cout<<"число 256 НЕ степень двойки"<<endl;

    if(degree(255))
        cout<<"число 255 степень двойки"<<endl;
    else
        cout<<"число 255 НЕ степень двойки"<<endl;  

    if(degree_bit(1024))
        cout<<"число 1024 степень двойки"<<endl;
    else
        cout<<"число 1024 НЕ степень двойки"<<endl;  

    if(degree_bit(1023))
        cout<<"число 1023 степень двойки"<<endl;
    else
        cout<<"число 1023 НЕ степень двойки"<<endl;      
    


    return 0; 
    
   
}