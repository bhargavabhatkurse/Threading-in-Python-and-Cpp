/*
In this video we will learn about Mutex In C++ Threading | Why Use Mutex | What Is Race Condition And How To Solve It? | What Is Critical Section

Mutex: Mutual Exclusion

RACE CONDITION:
0. Race condition is a situation where two or more threads/process happens to change a common data at the same time.
1. If there is a race condition then we have to protect it and the protected section is  called critical section/region.

MUTEX:
0. Mutex is used to avoid race condition.
1. We use lock() , unlock() on mutex to avoid race condition.

*/


#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int money=0;

mutex m;		//mutex variable

void run() {	
	  m.lock();
	  ++money;		//there could be a race condition here, so we use locks
	  m.unlock();		
}


int main() {
	thread t1(run); 
	thread t2(run); 
	t1.join();
	t2.join();

	cout<<money;
	return 0;
}