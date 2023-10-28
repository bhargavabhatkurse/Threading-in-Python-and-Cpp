/*
Few points to remember about the try_lock is as follows:
0. try_lock() Tries to lock the mutex. Returns immediately. On successful lock acquisition returns true otherwise returns false.
1. If try_lock() is not able to lock mutex, then it doesn't get blocked that's why it is called non-blocking.
2. If try_lock is called again by the same thread which owns the mutex, the behaviour is undefined.
   It is a dead lock situation with undefined behaviour. (if you want to be able to lock the same mutex by same thread more than one time the go for recursive_mutex)

There are so many try_lock function
1. std::try_lock
2. std::mutex::try_lock
3. std::shared_lock::try_lock
4. std::timed_mutex::try_lock
5. std::unique_lock::try_lock
6. std::shared_mutex::try_lock
7. std::recursive_mutex::try_lock
8. std::shared_timed_mutex::try_lock
9. std::recursive_timed_mutex::try_lock
*/


#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

int money=0;

mutex m;		//mutex variable

void blocking() {	

	//this is blocking
	for(int i=0;i<100000;i++) {
	  m.lock();
	  ++money;		
	  m.unlock();	
	  }	
}

void nonblocking() {	

	//this is non blocking
	//if it doesnt get the lock, it will skip the iteration instead of blocking
	//therefore, the answer wont be 2 lakh in this case
	for(int i=0;i<100000;i++) {
	  if(m.try_lock()) {
	  ++money;		
	  m.unlock();	
	}
	  }	
}


int main() {
	thread t1(blocking); 
	thread t2(blocking); 
	t1.join();
	t2.join();
	cout<<money<<endl;

	money=0;

	thread t3(nonblocking); 
	thread t4(nonblocking); 
	t3.join();
	t4.join();

	cout<<money;
	return 0;
} 