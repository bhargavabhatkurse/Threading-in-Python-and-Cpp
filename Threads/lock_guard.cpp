/*
Few points to remember about the lock_guard is as follows:
0. It is very light weight wrapper for owning mutex on scoped basis.      ****
1. It acquires mutex lock the moment you create the object of lock_guard.
2. It automatically removes the lock while goes out of scope.  
3. You can not explicitly unlock the lock_guard.        *********
4. You can not copy lock_guard.
*/

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex m1;
int buffer = 0;


void task(const char * threadN,int loopfor) {
lock_guard<mutex> lock(m1);  //instead of doing m1.lock() and m1.unlock,
							 //we can use lock guard to acquire lock and unlock when the scope ends
for (int i = 0; i < loopfor; ++i)
{
	buffer += 1;
	cout<<threadN<<" "<<buffer<<endl;
}
}


int main() {

	thread t1(task,"T1",10);
	thread t2(task,"T2",10);
	t1.join();
	t2.join();

	return 0;
}

// o/p:
// T1 1
// T1 2
// T1 3
// T1 4
// T1 5
// T1 6
// T1 7
// T1 8
// T1 9
// T1 10
// T2 11
// T2 12
// T2 13
// T2 14
// T2 15
// T2 16
// T2 17
// T2 18
// T2 19
// T2 20
