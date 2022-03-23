#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <queue>
#include <cmath>
#include <math.h>
//#include <bits/stdc++.h>

using namespace std;
ifstream f("input.txt");
ofstream g("output.txt");
bool OK;
long N,Max,T,pp,ll;
using namespace std::chrono;
void generare_nr_random(long vector_size, long max_value,long V[])
{
    srand((unsigned)time(NULL));
    int numar1;
    for(int i=0 ; i<vector_size; i++)
    {
        numar1 = rand()*rand() % max_value;
        V[i]=1+numar1;
    }
}
void generare_vector_constant(long vector_size,long max_value,long V[])
{
    srand((unsigned)time(NULL));
    int numar2;
    numar2 = rand()*rand() % max_value;
    for(int i = 0 ; i < vector_size ; i++)
    {
        V[i] = numar2;
    }
}
void citire_din_fisier(long vector_size,long max_value,long V[])
{
    char nume_fisier[60];
    cout<<"Numele fisierului de intrare este:"<<endl;
    cout<<"Numerele trebuie sa fie mai mici decat valoarea maxima introdusa"<<endl;
    cout<<"Daca sunt mai multe numere decat numarul de elemente introdus se vor lua doar primele N numere"<<endl;
    cout<<"Iar daca sunt mai putine numere atunci restul numerelor pana la N se vor genera aleatoriu"<<endl;
    cin>>nume_fisier;
    ifstream citeste_din_fisier;
    citeste_din_fisier.open(nume_fisier);
    cout<<"avem"<<vector_size<<"numere , mai mici decat"<<max_value<<endl;
    for(long i=0; i<vector_size ; i++)
    {
        citeste_din_fisier>>V[i];
    }
}
void afisare_vector(long vector_size, long V[])
{
    for(long i=0; i<vector_size; i++)
    {
        cout<<V[i]<<" ";
    }
    cout<<endl;
}
void duplicare_vector(long vector_size, long max_value,long V[],long V2[])
{
    for (long i=0; i<vector_size; i++)
    {
        V2[i]=V[i];
    }
}
void bubble_sort(long vector_size, long V[])
{
    for(long  i = 0 ; i < vector_size-1; i++)
    {
        for(long j = i+1 ; j<vector_size; j++)
        {
            if(V[i]>V[j])
                swap(V[i],V[j]);
        }
    }
}
void counting_sort(long vector_size,long max_value, long V[])
{
    long *Frecventa = new long[max_value+1];
    for (long i=0 ; i<=max_value ; i++)
    {
        Frecventa[i] = 0;
    }
    long Max=0;
    for(long i=0; i <vector_size; i++)
    {
        Frecventa[V[i]]++;
        if(V[i] > Max)
        {
            Max = V[i];
        }
    }
    long I=0;
    for(long i = 0 ; i <= Max ; i++)
    {
        while(Frecventa[i] > 0)
        {
            V[I] = i;
            I++;
            Frecventa[i]--;
        }
    }
    delete [] Frecventa;
}
void merge_sort(long st, long dr, long V[], long vector_temp[])
{
    if(st<dr)
    {
        long mid = (st+dr) / 2;
        merge_sort(st,mid,V,vector_temp);
        merge_sort(mid+1,dr,V,vector_temp);
        long i=st;
        long j=mid+1;
        long k=0;
        while(i<=mid && j<=dr)
        {
            if(V[i] < V[j])
            {
                vector_temp[k] = V[i];
                i++;
                k++;
            }
            else
            {
                vector_temp[k] = V[j];
                j++;
                k++;
            }
        }
        while(i<=mid)
        {
            vector_temp[k] = V[i];
            i++;
            k++;
        }
        while(j<=dr)
        {
            vector_temp[k] = V[j];
            j++;
            k++;
        }
        long I=st;
        long K=0;
        while(I<=dr)
        {
            V[I] = vector_temp[K];
            I++;
            K++;
        }
    }
}
void quick_sort(long st,long dr,long V[])
{
    if(st<dr)
    {
        long pivot = (st+dr) / 2;
        swap(V[pivot], V[st]);
        long i = st;
        long j = dr;
        bool OK=0;
        while(i<j)
        {
            if(V[i] > V[j])
            {
                swap(V[i],V[j]);
                OK = !OK;
            }
            if(OK == 0)
                j--;
            else
                i++;
        }
        quick_sort(st,i-1,V);
        quick_sort(i+1,dr,V);
    }
}
void counting_sort_pentru_radix(long vector_size, long V[], long putere10)
{
    long ap_cif[10];
    long *vector_temp = new long [N];
    for (long i = 0 ; i < 10 ; i++)
    {
        ap_cif[i] = 0;
    }
    for(long i=0; i < vector_size; i++)
    {
        ap_cif[(V[i]/putere10)%10]++;
    }
    for(long i=1; i<10; i++)
    {
        ap_cif[i] = ap_cif[i]+ap_cif[i-1];
    }
    for(long i=vector_size-1; i>=0; i--)
    {
        vector_temp[ap_cif[V[i]/putere10%10]-1] = V[i];
        ap_cif[V[i]/putere10%10]--;
    }
    for(long i=0; i<vector_size; i++)
    {
        V[i]=vector_temp[i];
    }
    delete[] vector_temp;
}
void radix_sort(long vector_size,long V[])
{
    long Max=V[0];
    for(long i=1; i<vector_size; i++)
    {
        if(V[i]>Max)
        {
            Max=V[i];
        }
    }
    for(long putere10=1; putere10<=Max; putere10=putere10*10)
    {
        counting_sort_pentru_radix(vector_size,V,putere10);
    }
}
void shell_sort(long vector_size, long V[])
{
    for(long interval=vector_size/2; interval>0; interval/=2)
    {
        for(long i = interval ; i<vector_size; i+=1)
        {
            long long temp = V[i];
            long long j;
            for(j=i; j>=interval && V[j-interval]>temp; j-=interval)
            {
                V[j]=V[j-interval];
            }
            V[j]=temp;
        }
    }
}
void shell_sort_Ciura(long vector_size,long V[])
{
    vector<int> gaps = {1,4,10,23,57,132,301,701,1750,3937,8858,19930,44842,100894,227011,510774};
    for(int q=15; q>=0; q--)
    {
        int interval = gaps[q];
        for(int i = interval; i<vector_size; i++)
        {
            long long temp = V[i];
            long long j;
            for(j=i; j>=interval && V[j-interval]>temp; j-=interval)
            {
                V[j]=V[j-interval];
            }
            V[j]=temp;
        }
    }
}
void shell_sort_Tokuda(long vector_size,long V[])
{
    vector<int> gaps = {1,4,9,20,46,103,233,525,1182,2660,5985,13467,30301,68178,153401,345152};
    for(int q=15; q>=0; q--)
    {
        int interval = gaps[q];
        for(int i = interval; i<vector_size; i++)
        {
            long long temp = V[i];
            long long j;
            for(j=i; j>=interval && V[j-interval]>temp; j-=interval)
            {
                V[j]=V[j-interval];
            }
            V[j]=temp;
        }
    }
}
void radix_base_16(long vector_size, long V[], int shift) //doar pentru N maxx 10^6
{
    int count[16] = { 0 };
    int  output[vector_size];
    int i, last;

    for (i = 0; i < vector_size; i++)
    {
        ++count[(V[i] >> shift) & 15];
    }
    for (i = last = 0; i < 16; i++)
    {
        last += count[i];
        count[i] = last - count[i];
    }
    for (i = 0; i < vector_size; i++)
    {
        output[count[(V[i] >> shift) & 15]++] = V[i];
    }
    for (i = 0; i < vector_size; i++)
    {
        V[i] = output[i];
    }
}
void rsort16(long vector_size, long V[])
{
    int max = V[0];
    for (int i = 1; i < vector_size; i++)
    {
        if (V[i] > max)
        {
            max = V[i];
        }
    }
    for (int shift = 0; (max >> shift) > 0; shift += 4)
    {
        radix_base_16(vector_size, V, shift);
    }
}
void radix_2_la_16(long vector_size,long V[])  //implementare diff(wierd)
{
    vector<int>count(65536);
    vector<int>output(vector_size);
    int max = V[0];
    int p=0;
    int i;
    for(i=1; i<vector_size; i++)
    {
        if(V[i]>max)
            max=V[i];
    }
    fill(output.begin(), output.end(), 0);
    while(max)
    {
        fill(count.begin(), count.end(), 0);
        for(i=0; i<vector_size; i++)
        {
            count[(V[i]>>p)&65535]++;
        }
        for(i=1; i<65536; i++)
            count[i]+=count[i-1];
        for(i=vector_size-1; i>=0; i--)
        {
            output[count[(V[i]>>p) & 65535]-1]=V[i];
            count[(V[i]>>p)&65535]--;
        }
        for(i=0; i<vector_size; i++)
        {
            V[i]=output[i];
        }
        p+=16;
        max=max/65536;

    }

}
void radix_2_la_8(long vector_size,long V[])  //implementare diff(wierd)
{
    vector<int>count(256);
    vector<int>output(vector_size);
    int max = V[0];
    int p=0;
    int i;
    for(i=1; i<vector_size; i++)
    {
        if(V[i]>max)
            max=V[i];
    }
    fill(output.begin(), output.end(), 0);
    while(max)
    {
        fill(count.begin(), count.end(), 0);
        for(i=0; i<vector_size; i++)
        {
            count[(V[i]>>p)&255]++;
        }
        for(i=1; i<256; i++)
            count[i]+=count[i-1];
        for(i=vector_size-1; i>=0; i--)
        {
            output[count[(V[i]>>p) & 255]-1]=V[i];
            count[(V[i]>>p)&255]--;
        }
        for(i=0; i<vector_size; i++)
        {
            V[i]=output[i];
        }
        p+=8;
        max=max/256;

    }

}
int partitionare(long V[],int st,int dr)
{
    int pivot = V[dr],i=st-1,aux;
    for(int j = st; j < dr; j++)
        if( V[j] <= pivot )
        {
            i++;
            swap(V[i],V[j]);
        }

    swap(V[i+1],V[dr]);

    return i + 1;
}
int medianadin3(long V[],int &a,int&b,int&c)
{
    if ((V[a] > V[b]) ^ (V[a] > V[c]))
        return a;
    else if ((V[b] < V[a]) ^ (V[b] < V[c]))
        return b;
    else
        return c;
}
int partitie_random(long V[],int st,int dr)
{
    int poz = st + rand()%(dr-st);
    swap(V[poz],V[dr]);
    return partitionare(V,st,dr);
}
void quick_sort_random(long V[],int st,int dr)
{
    if(st<dr)
    {
        int poz = partitie_random(V,st,dr);
        quick_sort_random(V,st,poz-1);
        quick_sort_random(V,poz+1,dr);
    }
}
int partitie_med(long V[],int st,int dr)
{
    int a = st+rand()%(dr-st);
    int b = st+rand()%(dr-st);
    int c = st+rand()%(dr-st);
    int poz = medianadin3(V,a,b,c);
    swap(V[poz],V[dr]);
    return partitionare(V,st,dr);
}
void quick_sort_med3(long V[],int st,int dr)
{
    if(st<dr)
    {
        int poz = partitie_med(V,st,dr);
        quick_sort_med3(V,st,poz-1);
        quick_sort_med3(V,poz+1,dr);
    }
}
bool comparare_vectori(long vector_size, long V1[], long V2[])
{
    for(long i=0; i<vector_size; i++)
    {
        if(V1[i] != V2[i])
            return 0;
    }
    return 1;
}
int main()
{
    cin>>T;
    for(int indice=0; indice<T; indice++)
    {
        cout<<"Alege varianta : "<<endl;
        cout<<"Pentru vector cu numere random apasa : 1"<<endl;
        cout<<"Pentru numere din fisier apasa : 2"<<endl;
        cout<<"Pentru vector constant apasa : 3"<<endl;
        cout<<"Pentru vector crescator apasa : 4"<<endl;
        cout<<"Pentru vector descrescator apasa : 5"<<endl;
        cout<<"Pentru vector sortat pana la jumatate (partial) apasa : 6"<<endl;
        int Opt;
        cin>>Opt;
        cout<<"Cate numere citesc?"<<endl;
        cin>>N;
        cout<<"Numarul maxim pe care il pot primi este?"<<endl;
        cin>>Max;
        long *Vector = new long [N];
        long *VectorSortatCorect = new long [N];
        if(Opt == 1)
        {
            generare_nr_random(N,Max,Vector);
        }
        else if(Opt == 2)
        {
            citire_din_fisier(N,Max,Vector);
        }
        else if(Opt == 3)
        {
            generare_vector_constant(N,Max,Vector);
        }
        else if(Opt == 4)
        {
            generare_nr_random(N,Max,Vector);
            sort(Vector,Vector+N);
        }
        else if(Opt == 5)
        {
            generare_nr_random(N,Max,Vector);
            sort(Vector,Vector+N,greater<long>());
        }
        else if(Opt == 6)
        {
            generare_nr_random(N,Max,Vector);
            sort(Vector,Vector+N/2);
        }
        long *Vector_de_Sortat = new long [N];
        cout<<"Sortare stl C:"<<endl;
        duplicare_vector(N,Max,Vector,Vector_de_Sortat);
        auto  start1 = std::chrono::steady_clock::now();
        sort(Vector_de_Sortat, Vector_de_Sortat+N);
        auto stop1= std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff1 = stop1 - start1;
        cout<<diff1.count()<<" secunde"<<endl;
        duplicare_vector(N, Max, Vector_de_Sortat, VectorSortatCorect);
        cout<<endl<<endl;

        cout<<"Bubble Sort:"<<endl;
        if(N>10000)
        {
            cout<<"Sortarea dureaza prea mult"<<endl<<endl;
        }
        else
        {
            duplicare_vector(N, Max, Vector, Vector_de_Sortat);
            auto  start2 = std::chrono::steady_clock::now();
            bubble_sort(N, Vector_de_Sortat);
            auto stop2= std::chrono::steady_clock::now();
            std::chrono::duration<long double> diff2 = stop2 - start2;
            cout<<diff2.count()<<" secunde"<<endl;
            if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1)
            {
                cout<<"CORECT!!!!!"<<endl;
            }
            else
                cout<<"GRESIT!!!!!"<<endl;
            cout<<endl<<endl;
        }

        cout<<"Counting Sort:"<<endl;
        if(Max >= 1000000000)
        {
            cout<<"Sortarea nu functioneaza!"<<endl<<endl;
        }
        else
        {
            duplicare_vector(N, Max, Vector, Vector_de_Sortat);
            auto  start3 = std::chrono::steady_clock::now();
            counting_sort(N,Max,Vector_de_Sortat);
            auto stop3= std::chrono::steady_clock::now();
            std::chrono::duration<long double> diff3 = stop3 - start3;
            cout<<diff3.count()<<" secunde"<<endl;
            if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1)
            {
                cout<<"CORECT!!!!!"<<endl;
            }
            else
                cout<<"GRESIT!!!!!"<<endl;
            cout<<endl<<endl;
        }

        cout<<"Quick Sort(pivot la jumate):"<<endl;
        if((N >= 1000000 && (Opt == 3))|| N==100000000 && Max<=1000 || N==10000000 && Max==10)
        {
            cout<<"Sortarea dureaza prea mult"<<endl<<endl;
        }
        else
        {
            duplicare_vector(N, Max, Vector, Vector_de_Sortat);

            auto  start4 = std::chrono::steady_clock::now();
            quick_sort(0,N-1,Vector_de_Sortat);
            auto stop4= std::chrono::steady_clock::now();
            std::chrono::duration<long double> diff4 = stop4 - start4;
            cout<<diff4.count()<<" secunde"<<endl;
            if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1)
            {
                cout<<"CORECT!!!!!"<<endl;
            }
            else
                cout<<"GRESIT!!!!!"<<endl;
            cout<<endl<<endl;
        }
        cout<<"Merge Sort:"<<endl;
        duplicare_vector(N, Max, Vector, Vector_de_Sortat);
        long *VectorTemporar = new long[N];
        auto  start5 = std::chrono::steady_clock::now();
        merge_sort(0,N-1,Vector_de_Sortat,VectorTemporar);
        auto stop5= std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff5 = stop5 - start5;
        cout<<diff5.count()<<" secunde"<<endl;
        if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1)
        {
            cout<<"CORECT!!!!!"<<endl;
        }
        else
            cout<<"GRESIT!!!!!"<<endl;
        cout<<endl<<endl;

        delete[] VectorTemporar;
        cout<<"Radix Sort(baza 10):"<<endl;
        duplicare_vector(N, Max, Vector, Vector_de_Sortat);
        auto  start6 = std::chrono::steady_clock::now();
        radix_sort(N,Vector_de_Sortat);
        auto stop6= std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff6 = stop6 - start6;
        cout<<diff6.count()<<" secunde"<<endl;
        if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1)
        {
            cout<<"CORECT!!!!!"<<endl;
        }
        else
            cout<<"GRESIT!!!!!"<<endl;
        cout<<endl<<endl;

        cout<<"Shell Sort Normal:"<<endl;
        duplicare_vector(N,Max,Vector,Vector_de_Sortat);
        auto  start7 = std::chrono::steady_clock::now();
        shell_sort(N,Vector_de_Sortat);
        auto  stop7 = std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff7 = stop7 - start7;
        cout<<diff7.count()<<" secunde"<<endl;
        if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1)
        {
            cout<<"CORECT!!!!!"<<endl;
        }
        else
            cout<<"GRESIT!!!!!"<<endl;
        cout<<endl<<endl;

        cout<<"Shell Sort (Ciura gap sequence):"<<endl;
        duplicare_vector(N,Max,Vector,Vector_de_Sortat);
        auto  start8 = std::chrono::steady_clock::now();
        shell_sort_Ciura(N,Vector_de_Sortat);
        auto  stop8 = std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff8 = stop8 - start8;
        cout<<diff8.count()<<" secunde"<<endl;
        if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1)
        {
            cout<<"CORECT!!!!!"<<endl;
        }
        else
            cout<<"GRESIT!!!!!"<<endl;
        cout<<endl<<endl;

        cout<<"Shell Sort (Tokuda gap sequence):"<<endl;
        duplicare_vector(N,Max,Vector,Vector_de_Sortat);
        auto  start9 = std::chrono::steady_clock::now();
        shell_sort_Tokuda(N,Vector_de_Sortat);
        auto  stop9 = std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff9 = stop9 - start9;
        cout<<diff9.count()<<" secunde"<<endl;
        if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1)
        {
            cout<<"CORECT!!!!!"<<endl;
        }
        else
            cout<<"GRESIT!!!!!"<<endl;
        cout<<endl<<endl;

        cout<<"Radix Sort(baza 16):"<<endl;
        if(N>=1000000)
        {
            cout<<"Sortarea nu functioneaza"<<endl<<endl;
        }
        else
        {
            duplicare_vector(N,Max,Vector,Vector_de_Sortat);
            auto  start10 = std::chrono::steady_clock::now();
            rsort16(N,Vector_de_Sortat);
            auto  stop10 = std::chrono::steady_clock::now();
            std::chrono::duration<long double> diff10 = stop10 - start10;
            cout<<diff10.count()<<" secunde"<<endl;
            if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1)
            {
                cout<<"CORECT!!!!!"<<endl;
            }
            else
                cout<<"GRESIT!!!!!"<<endl;
            cout<<endl<<endl;
        }


        cout<<"Radix Sort(baza 2^16):"<<endl;
        duplicare_vector(N,Max,Vector,Vector_de_Sortat);
        auto  start11 = std::chrono::steady_clock::now();
        radix_2_la_16(N,Vector_de_Sortat);
        auto  stop11 = std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff11 = stop11 - start11;
        cout<<diff11.count()<<" secunde"<<endl;
        if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1)
        {
            cout<<"CORECT!!!!!"<<endl;
        }
        else
            cout<<"GRESIT!!!!!"<<endl;
        cout<<endl<<endl;

        cout<<"Quick Sort(pivot random):"<<endl;
        if((N >= 1000000 && (Opt == 3)) ||  N==100000000 && Max<=1000 || N==10000000 && Max==10)
        {
            cout<<"Sortarea dureaza prea mult"<<endl<<endl;
        }
        else
        {
            duplicare_vector(N, Max, Vector, Vector_de_Sortat);
            auto  start12 = std::chrono::steady_clock::now();
            quick_sort_random(Vector_de_Sortat,0,N-1);
            auto stop12= std::chrono::steady_clock::now();
            std::chrono::duration<long double> diff12 = stop12 - start12;
            cout<<diff12.count()<<" secunde"<<endl;
            if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1)
            {
                cout<<"CORECT!!!!!"<<endl;
            }
            else
                cout<<"GRESIT!!!!!"<<endl;
            cout<<endl<<endl;
        }

        cout<<"Quick Sort(mediana din 3):"<<endl;
        if((N >= 1000000 && (Opt == 3)) || N==100000000 && Max<=1000 || N==10000000 && Max==10)
        {
            cout<<"Sortarea dureaza prea mult"<<endl<<endl;
        }
        else
        {
            duplicare_vector(N, Max, Vector, Vector_de_Sortat);
            auto  start13 = std::chrono::steady_clock::now();
            quick_sort_med3(Vector_de_Sortat,0,N-1);
            auto stop13= std::chrono::steady_clock::now();
            std::chrono::duration<long double> diff13 = stop13 - start13;
            cout<<diff13.count()<<" secunde"<<endl;
            if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1)
            {
                cout<<"CORECT!!!!!"<<endl;
            }
            else
                cout<<"GRESIT!!!!!"<<endl;
            cout<<endl<<endl;

        }
        cout<<"Radix Sort(baza 2^8)"<<endl;
        duplicare_vector(N,Max,Vector,Vector_de_Sortat);
        auto  start14 = std::chrono::steady_clock::now();
        radix_2_la_8(N,Vector_de_Sortat);
        auto  stop14 = std::chrono::steady_clock::now();
        std::chrono::duration<long double> diff14 = stop14 - start14;
        cout<<diff14.count()<<" secunde"<<endl;
        if(comparare_vectori(N,Vector_de_Sortat, VectorSortatCorect)==1)
        {
            cout<<"CORECT!!!!!"<<endl;
        }
        else
            cout<<"GRESIT!!!!!"<<endl;
        cout<<endl<<endl;

        if(indice==T-1)
        {
            cout<<"Sfarsitul sortarilor"<<endl<<":^)"<<endl;
        }
        else
            cout<<"Urmatorul caz:"<<endl;
    }
    return 0;
}
