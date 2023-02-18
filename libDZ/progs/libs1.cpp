
//поиск простого числа
bool simple_num(int num)
{
    int count_delitel=0;        //schetchik deleniy, doljno rovnyatsya 2

    for(int i=1;i<=num;++i)
        if(num%i==0)
            ++count_delitel;

    if(count_delitel==2)
        return true;
    else
        return false;
}


//подсчет количества разрядов числа
int digit(int num)
{
    int digit_count=0;

    while(num>0)
    {
            num=num/10;
            ++digit_count;
    }

    return digit_count;
}

//является ли число точной стпенью 2

    //способ арифметический
bool degree(int num)
{
    for(int i=1;i<=num;i*=2)
        if(i==num)return true;

    return false;
}
    //способ побитовый

bool degree_bit(int num)
{
    if(num>0&&(num&(num-1))==0) return true;

    return false;
} 

