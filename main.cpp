#include <iostream>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include "monitor.h"
#include <numeric>

#define MAX_BUFOR 9 // Maksymalna pojemnosc bufora
using namespace std;




class MonitorBuffer:Monitor
{
	public:
		void* produce();
		void* consumeA();
		void* consumeB();
		void showBuff();
		MonitorBuffer(){}
	private:
	Condition CanAconsume,
 	CanBconsume,
 	CanWrite,
 	CanRead;
	vector<int> bufor;
	
};
void* MonitorBuffer::produce()
{
	srand(time(NULL));
	while(true)
	{
		int sleepTime= (rand()%5+1)*100000;
		usleep(sleepTime);
		enter();
			if(bufor.size()==9)	
			{
				cout<<"Bufor jest pelny"<<endl;
				wait(CanWrite);
			}	
			int random = rand()%10+1;
			cout<<"Do bufora trafia "<<random<<endl;
			bufor.push_back(random);
			showBuff();
			if(bufor.size()>3) signal(CanRead);
		leave();
	}
}
void* MonitorBuffer::consumeA()
{
	srand(time(NULL));
	while(true)
	{
		int sleepTime= (rand()%5+1)*100000;
		usleep(sleepTime);
		enter();
			if(bufor.size()<=3)
			{
				cout<<"Nie mozna czytac, nie ma co najmniej 4 elementow w buforze"<<endl;
				wait(CanRead);
			}
			if((bufor.front()%2)==1)
			{
				cout<<"A moze konsumowac tylko liczby parzyste"<<endl;
				signal(CanBconsume);
				wait(CanAconsume);
			}
			cout<<"A konsumuje "<<bufor.front()<<endl;
			bufor.erase(bufor.begin());
			showBuff();
			if(bufor.size()==8)	signal(CanWrite);
		leave();
	}
}
void* MonitorBuffer::consumeB()
{
	srand(time(NULL));
	while(true)
	{
		int sleepTime= (rand()%5+1)*100000;
		usleep(sleepTime);
		enter();
			if(bufor.size()<=3)
			{
				cout<<"Nie mozna czytac, nie ma co najmniej 4 elementow w buforze"<<endl;
				wait(CanRead);
			}
			if((bufor.front()%2)==0)
			{
				cout<<"B moze konsumowac tylko liczby nieparzyste"<<endl;
				signal(CanAconsume);
				wait(CanBconsume);
			}
			cout<<"B konsumuje "<<bufor.front()<<endl;
			bufor.erase(bufor.begin());
			showBuff();
			if(bufor.size()==8)	signal(CanWrite);
		leave();
	}
}

void MonitorBuffer::showBuff()
{
	cout<<"Bufor zawiera: ";
	for(auto iterator: bufor)	cout<<" "<<iterator;
	cout<<endl;
}

void* do_produce(void* M)
{
	((MonitorBuffer*) M)->produce();
}
void* do_consumeA(void* M)
{
	((MonitorBuffer*) M)->consumeA();
}
void* do_consumeB(void* M)
{
	((MonitorBuffer*) M)->consumeB();
}

int main() 
{
	MonitorBuffer *Buff=new MonitorBuffer;
	pthread_t konsA, konsB, prodA, prodB;

	void* ptr = NULL;

	pthread_create(&konsA, NULL, do_consumeA, (void*) Buff);
   	pthread_create(&konsB, NULL, do_consumeB, (void*) Buff);
	pthread_create(&prodB, NULL, do_produce, (void*) Buff);
	pthread_create(&prodA, NULL, do_produce, (void*) Buff);

	pthread_join(konsA, NULL);
    	pthread_join(prodB, NULL);
    	pthread_join(konsB, NULL);
    	pthread_join(prodA, NULL);

	return 0;
}	
