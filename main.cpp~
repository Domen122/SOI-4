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

vector<int> bufor;


void wypisz()
{

}	

void* produceB(void* ptr)
{

} 

void* produceA(void* ptr)
{

}

void* consume(void* numerKonsumenta)
{

}

int main() 
{
	
	pthread_t kons1, kons2, prodA, prodB;

	unsigned int *iDKonsumenta1, *iDKonsumenta2;

	iDKonsumenta1 = new unsigned int;
	iDKonsumenta2 = new unsigned int;

	*iDKonsumenta1 = 1;
	*iDKonsumenta2 = 2;

	void* ptr = NULL;

	pthread_create(&kons1, NULL, consume, (void*) iDKonsumenta1);
   	pthread_create(&kons2, NULL, consume, (void*) iDKonsumenta2);
	pthread_create(&prodB, NULL, produceB, (void*) ptr);
	pthread_create(&prodA, NULL, produceA, (void*) ptr);

	pthread_join(kons1, NULL);
    	pthread_join(prodB, NULL);
    	pthread_join(kons2, NULL);
    	pthread_join(prodA, NULL);

	delete iDKonsumenta1;
	delete iDKonsumenta2;

	cout << "	W buforze pozostalo " << bufor.size() << " elementow." << endl;
	return 0;
}	
