/*
Five different types for creating threads.
1. Function Pointer -- this is the very basic form of creating threads.
2. Lambda Function
3. Functor (Function Object)
4. Non-static member function
5. Static member function


if there are multiple threads, there is no gurantee which will start first
*/



#include <iostream>
#include <thread>
using namespace std;

class base {
public: 
	  void operator () (int x) {			//overloaded (). This is called functor
	  while(x-- > 0)
	  cout<<x<<endl;
	  }

	  void run(int x) {				//non-static member function
	  while(x-- > 0)
	  cout<<x<<endl;
	  }

	  static void print(int x) {				//static member function
	  while(x-- > 0)
	  cout<<x<<endl;
	  }

};






int main() {
	
//function pointer we did before

/*lambda function 

thread t([](int x) {
while(x-- > 0)
	cout<<x<<endl;
},10);

t.join();
*/


/*
using functors


thread t(base(),10);
t.join();

*/

/*
using non-static member functions

base b;
thread t(&base::run,&b,10);   //parameters: the member function which we want to call, the reference of the object, argument 
t.join();


*/

thread t(&base::print,10);   //parameters: the member function which we want to call, argument 
t.join();


return 0;

}