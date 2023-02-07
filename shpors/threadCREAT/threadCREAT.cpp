#include <iostream>
#include <string>
#include <thread>  // подключение потоков
#include <chrono>  // подключение замедление времени

using namespace std;


void FuncVoid() // функция ничего не принимает и не возвращает
{   cout<<endl<<"1"<<endl;
    cout<<"FuncVoid() START"<<endl;
    this_thread::sleep_for(chrono::milliseconds(1000)); // остановка потока
    cout<<"Номер потока: "<<this_thread::get_id()<<", FuncVoid() "<<endl;   //получение номера потока, он не интеджер
    cout<<endl<<"1"<<endl;
    cout<<"FuncVoid() FINISH"<<endl;
}

void FuncVoidParam(int a, int b)    //не возвращает, принимает по значению
{
    cout<<endl<<"2"<<endl;
    cout<<"FuncVoidParam() START"<<endl;
    this_thread::sleep_for(chrono::milliseconds(1000)); 
    cout<<"Номер потока: "<<this_thread::get_id()<<", FuncVoidParam(int a, int b) "<<endl;
    cout<<"a = "<<a<<", b = "<<b<<", a + b = "<<a+b<<endl;
    cout<<endl<<"2"<<endl;
    cout<<"FuncVoidParam() FINISH"<<endl;
}

int FuncIntParam(int a, int b)  //принимает по значению, и возвращает
{
    cout<<endl<<"3"<<endl;
    cout<<"FuncIntParam() START"<<endl;
    this_thread::sleep_for(chrono::milliseconds(1000)); 
    cout<<"Номер потока: "<<this_thread::get_id()<<", FuncIntParam(int a, int b) "<<endl;
    cout<<endl<<"3"<<endl;
    cout<<"FuncIntParam() FINISH"<<endl;
    return a+b;
}

void FuncVoidParamRef(int &a,int &b)    //ничего не возвращает, принимает по ссылке
{
    cout<<endl<<"4"<<endl;
    cout<<"FuncVoidParamRef() START"<<endl;
    this_thread::sleep_for(chrono::milliseconds(1000)); 
    cout<<"Номер потока: "<<this_thread::get_id()<<", FuncVoidParamRef(int &a,int &b) "<<endl;
    cout<<"a = "<<a<<", b = "<<b<<endl;
    ++a;
    ++b;
    cout<<"a = "<<a<<", b = "<<b<<endl;
    cout<<endl<<"4"<<endl;
    cout<<"FuncVoidParamRef() FINISH"<<endl;
}

void massiveWork(int *mass, int size)  //пример с преедачей по указателю
{
    cout<<endl<<"5"<<endl;
    cout<<"massiveWork() START"<<endl;
    this_thread::sleep_for(chrono::milliseconds(1000)); 
    cout<<"Номер потока: "<<this_thread::get_id()<<", massiveWork(int *mass, int size) "<<endl;
    for(int i=0;i<size;++i)
    {
        ++mass[i];
    }
    cout<<endl<<"5"<<endl;
    cout<<"massiveWork() FINISH"<<endl;
}

int main(int argc,char* argv[])
{
    //запускается поток меин
    cout<<endl<<"1-BOSS"<<endl;
    cout<<"main(int argc,char* argv[]) START"<<endl;
    this_thread::sleep_for(chrono::microseconds(1000));
    cout<<"Номер потока: "<<this_thread::get_id()<<", main(int argc,char* argv[]) "<<endl;

    //запускаются 5 потоков и создаются переменные для них
    thread th1(FuncVoid);
    thread th2(FuncVoidParam, 2,3);
    int sum = 0;
    cout<<"(MAIN BEGIN) sum = "<<sum<<endl;
    thread th3([&sum](){cout<<"START LYAMBDA"<<endl; sum = FuncIntParam(2,8); cout<<"FINISH LYAMBDA"<<endl;});
    int a=1,b=1;
    cout<<"(MAIN BEGIN) a = "<<a<<", b = "<<b<<endl;
    thread th4(FuncVoidParamRef,ref(a),ref(b));
    const int size=5;
    int mass[size]={1,1,1,1,1};
    for(int i=0;i<size;++i){cout<<"(MAIN BEGIN)----+++ "<<mass[i]<<" +++----"<<endl;}
    thread th5(massiveWork,mass,size);
    this_thread::sleep_for(chrono::microseconds(1000));

    //тут будут заканчиваться потоки, используем джоин что бы меин ждал завершения потокв, если использовать детач,
    //то меин закончит все потоки когда сам закончится
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();

    //вывод используемых в меине переменных
    for(int i=0;i<size;++i){cout<<"(MAIN END) ----+++ "<<mass[i]<<" +++----"<<endl;}
    cout<<"(MAIN END) sum = "<<sum<<endl;
    cout<<"(MAIN END) a = "<<a<<", b = "<<b<<endl;

    //конец потока меин
    cout<<endl<<"1-BOSS"<<endl;
    cout<<"main(int argc,char* argv[]) FINISH"<<endl;

    return 0;
}


