/*
JOIN NOTES
0. Once a thread is started we wait for this thread to finish by calling join() function on thread object.
1. Double join will result into program termination.
2. If needed we should check thread is joinable before joining. ( using joinable() function)

DETACH NOTES
0. This is used to detach newly created thread from the parent thread.
1. Always check before detaching a thread that it is joinable otherwise we may end up double detaching and 
   double detach() will result into program termination.
2. If we have detached thread and main function is returning then the detached thread execution is suspended.

NOTES:
Either join() or detach() should be called on thread object, otherwise during thread object�s destructor it will 
terminate the program. Because inside destructor it checks if thread is still joinable? if yes then it terminates the program.

*/

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;


void run(int x) {				
	  while(x-- > 0)
	  cout<<x<<endl;
	  this_thread::sleep_for(chrono::seconds(3));
}


int main() {
	thread t(run,10); 
	cout<<"main() before"<<endl;
	//t.join();



	/*
	if(t.joinable())  //always check if the thread is joinable before joining.
					  // dont join twice, or detach twice 
	t.join();
	*/

	t.detach();
/*
output:

main() before
main() after

this is because the main has executed and returned 0 before thread t can even start.
*/

	cout<<"main() after"<<endl;
	return 0;
}