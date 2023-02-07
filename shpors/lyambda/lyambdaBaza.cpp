#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <functional> //
#include <vector>
using namespace std;

//lyambda [](){}, 


//функция где фанкшн параметр
void functional(vector<int> &vec,function<void(int)> funkl)
{   //передали вектор с числами, и обьект фанкшн, который будет хранить указатель на функцию по макету 
    for(auto val:vec) //идём по вектору перебираем каждый элемент который интеджер
    {
        funkl(val); //подставляем в функцию число из вектора, функция лямбда - [](int a){cout<<"(lyambda) a = "<<a<<endl;};  
    }

    /* работа в меин
        vector<int> vec={10,20,30,40,50};
        function<void(int)> fun;
        fun = [](int a){cout<<"(lyambda) a = "<<a<<endl;};  
        functional(vec,fun);
    */

}

// primer pole classa
class mylass
{
    public :
    int a=5;
    void msg(){cout<<"myclass msg"<<endl;}

    void lyambda()
    {
        auto gek = [this](){this->msg();};
        gek();
    }

};



int main(int argc,char* argv[])
{   
    //необходимые переменные=======================================
    int a=5,b=7;
    int sum=0;
    const int size = 5;
    int mass[size]={1,1,1,1,1};
    vector<int> vec={10,20,30,40,50};

    //[захват](параметры)->возвращаемый тип{инструкции}; // lyavbda

        //пример через фанкшн
    function<void(int)> fun;
    fun = [](int a){cout<<"(lyambda v funk) a = "<<a<<endl;};  
    functional(vec,fun);

        //пример сразу лямблды
    functional(vec,[](int a){cout<<"(lyambda) a = "<<a<<endl;});

        // пример с авто
    cout<<"a = "<<a<<endl;
    auto lyam = [&a](int x){a=a+x;};
    lyam(10);
    cout<<"a = "<<a<<endl;

    int A=2;
    int B=3;

    auto lyam2 = [&A,B]{cout<<++A<<B;}; // захфат по ссылке и по значению
    auto lyam3 = [=]{cout<<A<<B;};      // захват всех по значению(нельзя изменять)
    auto lyam4 = [&]{cout<<++A<<++B;};  // захват всех по ссылке(можно изменять)
    auto lyam5 = [A,B]mutable{cout<<++A<<++B;}; //делает так как будто переданы по значению(внутри лямбды изменится)

    
    

   

    
    



   return 0;
}




