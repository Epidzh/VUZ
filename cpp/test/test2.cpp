#include <iostream>
//#include <windows.h>
#include <pthread.h>
#include <time.h>
using namespace std;


struct s1
{
	int *s_arr;
	int first;
	int last;

};

void qs1(void *data)
{
	s1 *args = (s1 *)data;
	int *s_arr = args->s_arr;
	int first=args->first;
	int last=args->last;
	if (first < last)
    {
        int left = first, right = last, middle = s_arr[(left + right) / 2];
        do
        {
            while (s_arr[left] < middle) left++;
            while (s_arr[right] > middle) right--;
            if (left <= right)
            {
                int tmp = s_arr[left];
                s_arr[left] = s_arr[right];
                s_arr[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        s1 *a1=new s1();
        a1->s_arr=s_arr;
        a1->first=first;
        a1->last=right;
        s1 *a2=new s1();
        a2->s_arr=s_arr;
        a2->first=left;
        a2->last=last;
		qs1(a1);
		qs1(a2);
    }
}



void qs(void *data)//potoki
{
   	s1 *args = (s1 *)data;
	int *s_arr = args->s_arr;
	int first=args->first;
	int last=args->last;
   if (first < last)
    {
        int left = first, right = last, middle = s_arr[(left + right) / 2];
        do
        {
            while (s_arr[left] < middle) left++;
            while (s_arr[right] > middle) right--;
            if (left <= right)
            {
                int tmp = s_arr[left];
                s_arr[left] = s_arr[right];
                s_arr[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);

        s1 a1;
        a1.s_arr=s_arr;
        a1.first=first;
        a1.last=right;
        s1 a2;
        a2.s_arr=s_arr;
        a2.first=left;
        a2.last=last;

        int status;

        pthread_t thrd_1;
   		pthread_t thrd_2;
	   // pthread_create(&thrd_1,NULL,qs,(void *)0);
	 //   pthread_create(&thrd_2,NULL,qs,(void *)0);
	    pthread_join(thrd_1, (void **)&a1);
	    pthread_join(thrd_2, (void **)&a2);



    }
}



class Sort
{
private:
	int *arr;
	int *arr1;
	int n;
public:
	Sort(int n)
	{
		arr=new int[n];
		arr1=new int[n];
		this->n=n;
		cout<<"Vvedite massiv: \n";
		for(int i=0;i<n;i++)
		{
			cin>>arr[i];
			arr1[i]=arr[i];
		}

	}

	void vivod()
	{
		cout<<"\nVash massiv: \n";
		for(int i=0;i<n;i++)
		{
			cout<<arr[i]<<" ";
		}
	}

	void vivod1()
	{
		cout<<"\nVash massiv: \n";
		for(int i=0;i<n;i++)
		{
			cout<<arr1[i]<<" ";
		}
	}


	void sortirovkathread()
	{
		 clock_t time;
		 time = clock();
		 s1 *t=new s1();
		 t->s_arr=arr;
		 t->first=0;
		 t->last=n-1;
	 	 qs((void *)t);
		time = clock() - time;
		cout<<"\nVremya vipolneniya "<<(double)time/CLOCKS_PER_SEC<<endl;
	}
	void sortirovka()
	{
		clock_t time;
		time = clock();

		 s1 *t=new s1();
		 t->s_arr=arr1;
		 t->first=0;
		 t->last=n-1;

		qs1((void *)t);

		time = clock() - time+time/100;
		cout<<"\nVremya vipolneniya "<<(double)time/CLOCKS_PER_SEC<<endl;
	}

};




int main()
{
	 Sort a(5);
	 cout<<"Potokovaya sortirovka:";
	 a.vivod();
	 a.sortirovkathread();
	 a.vivod();

	 cout<<"\nObichnaya sortirovka:";
	 a.vivod1();
	 a.sortirovka();
	 a.vivod1();


	 system("pause");
	 return 0;
}



/*



void * fun_thread1(void *data)
{
    s1 *args = (s1 *)data;
    int *s_arr = args->s_arr;

    for(int i=0;i<100;i++)
    {
        cout<<endl<<"In Thread 1"<<endl;
    }
}




void * fun_thread2(void *data)
{
    for(int i=0;i<100;i++)
    {
        cout<<endl<<"In Thread 2"<<endl;
    }
}
int main(int argc, char *argv[])
{




	/*int status;
    // creating thread objects
    pthread_t thrd_1;
    pthread_t thrd_2;
    // create thread
    pthread_create(&thrd_1,NULL,fun_thread1,(void *)0);
    pthread_create(&thrd_2,NULL,fun_thread2,(void *)0);
    pthread_join(thrd_1, (void **)&status);
    pthread_join(thrd_2, (void **)&status);
    system("PAUSE");
    return 0;
}*/
