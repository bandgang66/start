#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath> //sqr() - не видит почему-то, использую pow()
#include <random>
#include <thread>
#include <chrono>
#include <mutex> 


using namespace std;
random_device Rand;
mutex mtx;

enum Do     //для распознования действия, сложение, умножение, сумма квадратов
{
    PLUS=1,
    MULT,
    SUMSQR
};

//создать файлы in_1.dat,in_3.dat,in_5.dat
void make_files(string path,string name,int code);
//чтение файлов и запись в вектор стрингов
void read_file(string path, string name,vector<string> &vec);
//запись в созданный файл out.dat из вектора флоат
void write_file(string path,const vector<float> &vec,int code);
//converter из стринг в флоат (векторы)
void string_to_float(const vector<string> &vec_s,vector<float> &vec_f);
//cout вывод на экран содержимого векторов
template <typename T>
void show_vector(const vector<T> &vec);

int main(int argc,char* argv[])
{   

    string path;                //путь до директории

    //проверка на передачу пути к дериктории
    if(!argv[1])
    {
        cout<<"no path"<<endl;
        return 0;
    } 
    else
    {
        path=argv[1];
    }

    fstream file;
    file.open((path+"/out.dat").c_str(),ios::out);      //очистка и создание файла out.dat
    file.close();
     
     //=================================ВАРИАНТ 1, МНОГО ПЕРЕМЕННЫХ, НО БОЛЬШЕ ДЕЙСТВИЙ ДЕЛАЕТСЯ В РАЗНЫХ ПОТОКАХ===============================================================================


    /*
    string name1 = "in_1.dat";  
    string name2 = "in_3.dat";
    string name3 = "in_5.dat";  //имена файлов в директории
    vector<string> nums_string_name1; //массив временного хранения (считывает с файла)
    vector<string> nums_string_name2; //массив временного хранения (считывает с файла)
    vector<string> nums_string_name3; //массив временного хранения (считывает с файла)
    vector<float> nums_float_name1;   //массив хранит дробные числа
    vector<float> nums_float_name2;   //массив хранит дробные числа
    vector<float> nums_float_name3;   //массив хранит дробные числа

    //-----------------------1---------------------------
    thread th1([&]()
    {
        make_files(path,name1,PLUS);
        //открытие файла на чтение(переданый путь + / + имя файла)
        read_file(path,name1,nums_string_name1);
        //конвертация в дробные числа
        string_to_float(nums_string_name1,nums_float_name1);
        show_vector(nums_string_name1);
        show_vector(nums_float_name1);
        write_file(path,nums_float_name1,PLUS);
    });

    //-----------------------2---------------------------
    thread th2([&]()
    {
        make_files(path,name2,MULT);
        //открытие файла на чтение(переданый путь + / + имя файла)
        read_file(path,name2,nums_string_name2);
        //конвертация в дробные числа
        string_to_float(nums_string_name2,nums_float_name2);
        show_vector(nums_string_name2);
        show_vector(nums_float_name2);
        write_file(path,nums_float_name2,MULT);
    });

    //-----------------------3-------------------------------
    thread th3([&]()
    {
        make_files(path,name3,SUMSQR);
        //открытие файла на чтение(переданый путь + / + имя файла)
        read_file(path,name3,nums_string_name3);
        //конвертация в дробные числа
        string_to_float(nums_string_name3,nums_float_name3);
        show_vector(nums_string_name3);
        show_vector(nums_float_name3);
        write_file(path,nums_float_name3,SUMSQR);
    });

    th1.join();
    th2.join();
    th3.join();
    */
   //=====================ВАРИАНТ 2 МЕНЬШЕ ПЕРЕМЕННЫХ, НО ИСПОЛЬЗУЕТСЯ МЬЮТЕКС====================================================================================

    vector<string> nums_string_name;
    vector<float> nums_float_name;

    auto foo = [&](string name,int code)
    {   
        make_files(path,name,code);
        mtx.lock();
        read_file(path,name,nums_string_name);
        string_to_float(nums_string_name,nums_float_name);
        write_file(path,nums_float_name,code);
        nums_string_name.clear();
        nums_float_name.clear();
        mtx.unlock();
    };
    
    thread th1(foo,"int_1.dat",PLUS);
    thread th2(foo,"int_3.dat",MULT);
    thread th3(foo,"int_5.dat",SUMSQR);
    
  
    th1.join();
    th2.join();
    th3.join();
    
    return 0;
}

void make_files(string path,string name,int code=0)
{
    fstream file;
    file.open((path+"/"+name).c_str(),ios::out);
    if(!file.is_open())
    {
        cout<<"file is not open"<<endl;
    }
    else
    {
        if(code==1)
            file<<"1\n ";
        else if(code==2)
            file<<"2\n ";
        else if(code==3)
            file<<"3\n ";
        else
            file<<"WRONG CODE\n";

        for(int i=0;i<10;++i)
        {
            if(i<9)
                file<<Rand()%(1000-1)/10.0<<" ";
            else
                file<<Rand()%(1000-1)/10.0;
        }

    }
    file.close();
    this_thread::sleep_for(chrono::milliseconds(10)); //задержка что бы поток успел захватить мьютекс

}

void read_file(string path, string name, vector<string> &vec)
{
    fstream file;        
    file.open((path+"/"+name).c_str(),ios::in);
    if(!file.is_open())
    {
        cout<<"file is not open"<<endl;
    }
    else
    {
        cout<<"file open"<<endl;
        while(!file.eof())
        {   
            getline(file,vec.emplace_back(),' ');//запись в вектор стрингов всех цифр через проебл
            
        }
    }
    file.close();
}

void write_file(string path,const vector<float> &vec, int code)
{
    float result=0;
    fstream file;
    string name="/out.dat";
    file.open((path+name).c_str(),ios::app);

    if(!file.is_open())
    {
        cout<<"file is not open"<<endl;
    }
    else
    {
        switch(code)
        {
            case PLUS:
                file<<"\n------\ncode = PLUS\n-----\n";
                file<<"numbers: ";
                    for(int i=1;i<vec.size();++i)
                    {   
                        if(i<vec.size()-1)
                            file<<vec[i]<<" + ";
                        else
                            file<<vec[i];

                        result+=vec[i];
                    }
                file<<"\nresult = "<<result<<"\n----------\n";
            break;

            case MULT:
                result=1;
                file<<"\n------\ncode = MULT\n-----\n";
                file<<"numbers: ";
                    for(int i=1;i<vec.size();++i)
                    {   
                        if(i<vec.size()-1)
                            file<<vec[i]<<" * ";
                        else
                            file<<vec[i];

                        result*=vec[i];
                    }
                file<<"\nresult = "<<result<<"\n----------\n";
            break;

            case SUMSQR:
                file<<"\n------\ncode = SUMSQR\n-----\n";
                file<<"numbers: ";
                    for(int i=1;i<vec.size();++i)
                    {   
                        if(i<vec.size()-1)
                            file<<"sqr("<<vec[i]<<") + ";
                        else
                            file<<"sqr("<<vec[i]<<")";

                        result+=pow(vec[i],2);
                    }
                file<<"\nresult = "<<result<<"\n----------\n";
            break;

            default:
                cout<<"WRONG CODE"<<endl;
            break;
        }
    }
    file.close();

}

void string_to_float(const vector<string> &vec_s, vector<float> &vec_f)
{
    for(int i=0;i<vec_s.size();++i)
    {
        vec_f.emplace_back(atof(vec_s[i].c_str()));
    }
}

template <typename T>
void show_vector(const vector<T> &vec)
{
    cout<<"*#*#*#*#*#*#*#*#"<<endl;
    for(auto x: vec)
    {
        cout<<"-=-=- * "<<x<<endl;
    }
    cout<<"*#*#*#*#*#*#*#*#"<<endl;
    
}

