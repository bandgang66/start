#include <iostream>
#include <unistd.h>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <cmath>
#include <string>
#include <fstream>


using namespace std;

random_device Rand;

//функции из библиотек
bool simple_num(int num);
int digit(int num);
bool degree(int num);
bool degree_bit(int num);

//местные функции
void initVector(vector<int>& vec, int size_vector); //заполнение вектора
void CreatFileWithNums(int size);                   //Создать файл и заполнить числами раземером (передается параметром)
void ReadFile_to_vector(vector<int>& vec);          //Чтение из файла в вектор


// параметр если передаем то это размер массива, если много то это будут переданы значения
int main(int argc,char* argv[])
{
    auto start_main = chrono::steady_clock::now();
    cout<<"=-=-=-=-=-==-=-=-=MAIN START-=-=-=-=-==-=-=-=-=-=-=-=-=-=-"<<endl;
    chrono::duration<float> duration_simple;
    chrono::duration<float> duration_digit;
    chrono::duration<float> duration_degree;
    chrono::duration<float> duration_degree_bit;    //буду засекать время

//==========================================================================================================
    cout<<"=-=-=-=-=-==-=-=-=INIT VECTOR=-=-=-=-==-=-=-=-=-=-=-=-=-=-"<<endl;

    int size_vector=0;
    vector<int> vec;

    if(argc<=1)//нет параметров
    {
        size_vector = Rand()%1750+250;
        initVector(vec,size_vector);        //просто рандомное заполнение
    }
    else if(argc==2)//параметр размер массива //либо из файла, либо  с заданым размером
    {
        int vibor=0;
        int vihod = 0;

        while(vihod==0)
        {
            cout<<"Как ВЫ ХОТИИТЕ ЗАПОЛНИТЬ МАССИВ? 1 - ИЗ ФАЙЛА, 2 - СРАЗУ ТУТ "<<endl;
            cin>>vibor;
            switch(vibor)
            {
                case 1:
                    vihod=1;
                CreatFileWithNums(atoi(argv[1]));
                ReadFile_to_vector(vec);
                break;
                case 2: //переданый параметр сразу сделает своё дело как размер массива
                    size_vector = atoi(argv[1]);
                    initVector(vec,size_vector);
                    vihod=1;
                break;
                default:
                    cout<<"НЕ ВЕРНЫЙ ВВОД, ВВЕДИТЕ ЕЩЕ РАЗ"<<endl;
                break;
            }
        }

    }
    else if(argc>2)//параметры числа для массива
    {
        //в main передаются числа

        for(int i=1;i<argc;++i)
        {
            vec.emplace_back(atoi(argv[i]));
        }

        for(int i=0;i<vec.size();++i)
            cout<<"vec["<<i<<"] = "<<vec[i]<<endl;
    }   

//=============================================================================================================
    cout<<"=-=-=-=-=-==-=-=-=START THREADS-=-=-=-=-==-=-=-=-=-=-=-=-=-=-"<<endl;
//============================================================================================================
    cout<<"=-=-=-=-=-==-=-=-=SIMPLE(ПОИСК КОЛИЧЕСТВА ПРОСТЫХ ЧИСЕЛ)-=-=-=-=-==-=-=-=-=-=-=-=-=-=-"<<endl;
    
    int count_simpl_nums=0;
    thread th1([&vec,&count_simpl_nums,&duration_simple]()
    {
        auto start_simple = chrono::steady_clock::now();
        cout<<"=-=-=-=-=-==-=-=-=SIMPLE START-=-=-=-=-==-=-=-=-=-=-=-=-=-=-"<<endl;

        for(int i=0;i<vec.size();++i)
        {
            if(simple_num(vec[i]))
            {
                ++count_simpl_nums;
                cout<<"vec["<<i<<"] число: "<<vec[i]<<", простое"<<endl;
            } 
        }

        cout<<"=-=-=-=-=-==-=-=-=SIMPLE FINISH-=-=-=-=-==-=-=-=-=-=-=-=-=-=-"<<endl;
        auto finish_simple = chrono::steady_clock::now();
        duration_simple=finish_simple-start_simple;
    });
//=======================================================================================================
    cout<<"=-=--=-=DIGIT(ПОИСК ЧИСЛА С САМЫМ БОЛЬШИМ КОЛИЧЕСТВОМ РАЗРЯДОВ)-=-=-==-=-=-"<<endl;

    int count_max_digit=0;
    int count_current_digit=0;
    int MAX_num=0;
    thread th2([&vec,&count_current_digit,&count_max_digit,&MAX_num,&duration_digit]()
    {
        auto start_digit = chrono::steady_clock::now();
        cout<<"=-=-=-=-=-==-=-=-=DIGIT START-=-=-=-=-==-=-=-=-=-=-=-=-=-=-"<<endl;

        for(int i=0;i<vec.size();++i)
        {
            count_current_digit=0;
            count_current_digit=digit(vec[i]);
              
            if(count_current_digit>count_max_digit)
            {
                count_max_digit=count_current_digit;
                MAX_num=vec[i];
                cout<<"vec["<<i<<"] число имеет: "<<count_max_digit<<" разрядов"<<endl;
            }
        }

        cout<<"=-=-=-=-=-==-=-=-=DIGIT FINISH-=-=-=-=-==-=-=-=-=-=-=-=-=-=-"<<endl;
        auto finish_digit = chrono::steady_clock::now();
        duration_digit=finish_digit-start_digit;
    });
//=====================================================================================================
    cout<<"=-=-=-=-=-==-=-=-=DEGREE(СТЕПЕНЬ ДВОЙКИ)-=-=-=-=-==-=-=-=-=-=-=-=-=-=-"<<endl;

    int count_degree_nums=0;
    thread th3([&vec,&count_degree_nums,&duration_degree]()
    {
        auto start_degree= chrono::steady_clock::now();
        cout<<"=-=-=-=-=-==-=-=-=DEGREE START-=-=-=-=-==-=-=-=-=-=-=-=-=-=-"<<endl;

        for(int i=0;i<vec.size();++i)
        {
            if(degree(vec[i]))
            {
                ++count_degree_nums;
            }
        }

        cout<<"=-=-=-=-=-==-=-=-=DEGREE FINISH-=-=-=-=-==-=-=-=-=-=-=-=-=-=-"<<endl;
        auto finish_degree= chrono::steady_clock::now();
        duration_degree=finish_degree-start_degree;
    });
//======================================================================================================
    cout<<"=-=--=-=-=DEGREE_BIT(СТЕПРЕНЬ ДВОЙКИ ВТОРОЙ ВАРИАНТ)-=-=-=-=-==-=-=-=-=-=-"<<endl;

    int count_degree_bit_nums=0;
    thread th4([&vec,&count_degree_bit_nums,&duration_degree_bit]()
    {
        auto start_degree_bit= chrono::steady_clock::now();
        cout<<"=-=-=-=-=-==-=-=-=DEGREE_BIT START-=-=-=-=-==-=-=-=-=-=-=-=-=-=-"<<endl;

        for(int i=0;i<vec.size();++i)
        {
            if(degree_bit(vec[i]))
            {
                ++count_degree_bit_nums;
            }
        }

        cout<<"=-=-=-=-=-==-=-=-=DEGREE_BIT FINISH-=-=-=-=-==-=-=-=-=-=-=-=-=-=-"<<endl;
        auto finish_degree_bit= chrono::steady_clock::now();
        duration_degree_bit=finish_degree_bit-start_degree_bit;
    });


    th1.join();
    th2.join();
    th3.join();
    th4.join();

    cout<<"=-=-=-=-=-==-=-=-=END THREADS-=-=-=-=-==-=-=-=-=-=-=-=-=-=-"<<endl;
//=====================================================================================================
    cout<<"=-=-=-=-=-==-=-=-=ИТОГОВЫЕ ЗНАЧЕНИЯ-=-=-=-=-==-=-=-=-=-=-=-=-=-=-"<<endl;

    cout<<"У вектора: "<<count_simpl_nums<<", простых чисел        "<<endl;
    cout<<"У вектора, число: "<<count_max_digit<<"имеет МАХ разрядов: "<<MAX_num<<endl;
    cout<<"У вектора: "<<count_degree_nums<<", чисел степеней 2"<<endl;
    cout<<"У вектора: "<<count_degree_bit_nums<<", чисел степеней 2(способ 2) "<<endl;
//====================================================================================================
    cout<<"=-=-=-=-=-==-=-=-=TOTAL TIME-=-=-=-=-==-=-=-=-=-=-=-=-=-=-"<<endl;
    cout<<"duration SIMPLE     = "<<duration_simple.count()           <<endl;
    cout<<"duration DIGIT      = "<<duration_digit.count()            <<endl;
    cout<<"duration DEGREE     = "<<duration_degree.count()           <<endl;
    cout<<"duration DEGREE_BIT = "<<duration_degree_bit.count()       <<endl;

//====================================================================================================
    auto finish_main = chrono::steady_clock::now();
    chrono::duration<float> duration_main=finish_main-start_main;
    cout<<"=-=-=-=-=-==-=-=-=END MAIN-=-=-=-=-==-=-=-=-=-=-=-=-=-=-"<<endl;
    cout<<"duration Main = "<<duration_main.count()<<endl;

    return 0; 
}


void initVector(vector<int>& vec, int size_vector)
{
    int digits=0;

    for(int i=0;i<size_vector;++i) 
    {
        digits = 0;
        digits = (pow(10,(Rand()%5+2))); //так веселее рандом будет
        vec.emplace_back(Rand()%digits);
        cout<<"vec["<<i<<"] = "<<vec[i]<<endl;
    }
    cout<<endl<<vec.size()<<endl;
}

void CreatFileWithNums(int size)
{
    cout<<"FILE CREAT START"<<endl;
    fstream file;
    file.open("/home/dima/progs/file_for_libs.txt",ios_base::out);
    if(!file.is_open())
    {
        cout<<"FiLE Not opEn"<<endl;
    }
    else
    {
        int digits=0;
        int num = 0;
        
        for(int i=0;i<size;++i)
        {
            digits = (pow(10,(Rand()%5+2))); //так веселее рандом будет
            num = Rand()%digits;
            file<<num<<" ";
            if(i%10==0&&i!=0)
                file<<"\n";
        }
    }
    file.close();
    cout<<"FILE CREAT FINISH"<<endl;
}

void ReadFile_to_vector(vector<int>& vec)
{
    cout<<"FILE READ START"<<endl;
    fstream file;
    file.open("/home/dima/progs/file_for_libs.txt",ios_base::in);
    if(!file.is_open())
    {
        cout<<"File not open"<<endl;
    }
    else
    {
        vector<string> str;

        while(!file.eof())
        {
            getline(file,str.emplace_back(),' ');
        }

        for(int i=0;i<str.size();++i)
            vec.emplace_back(atoi(str[i].c_str()));

        for(int i=0;i<vec.size();++i)
            cout<<"vec["<<i<<"] = "<<vec[i]<<endl;

    }
    cout<<"FILE READ FINISH"<<endl;
}