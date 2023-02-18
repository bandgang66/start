#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>
#include <future>

using namespace std;



mutex mtx;

void Print(char ch)
{   
    this_thread::sleep_for(chrono::milliseconds(100));
    //время выполнения кода
    auto start = chrono::high_resolution_clock::now();

    
        for(int i=0;i<5;++i)
        {
            for(int j=0;j<10;++j)
            {
                cout<<ch;
                this_thread::sleep_for(chrono::milliseconds(20));
            }
            cout<<endl;
        }
    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = finish - start;
    cout<<"Duration = "<<duration.count()<<endl;
    cout<<endl;


 
}


int main(int argc,char* argv[])
{   
  
    
  async(launch::async,[](){Print('x'); this_thread::sleep_for(chrono::milliseconds(1));});
  async(launch::async,[](){Print('o'); this_thread::sleep_for(chrono::milliseconds(1));});
  async(launch::async,[](){Print('p'); this_thread::sleep_for(chrono::milliseconds(1));});





    return 0;
}




