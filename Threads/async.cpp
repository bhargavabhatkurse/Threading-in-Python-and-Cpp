// NOTES:
// 1. It runs a function asynchronously (potentially in a new thread) and returns a std::future that will hold the result.
// 2. There are three launch policies for creating task:
//      a. std::launch::async    //creates a new thread
//      b. std::launch::deffered    //no seperate thread is created
//      c. std::launch::async | std::launch::async   //let computer decide if it should use async or deferred

// HOW IT WORKS:
// 1. It automatically creates a thread (Or picks from internal thread pool) and a promise object for us.
// 2. Then passes the std::promise object to thread function and returns the associated std::future object.
// 3. When our passed argument function exits then its value will be set in this promise object, so eventually return value will be available in std::future object.

// SIDE NOTES:
// 1. We can send functor and lambda function as callback to std::async, it will work the same.

#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <future>
using namespace std;
using namespace std::chrono;
typedef long int  ull;

ull findOdd(ull start, ull end) {
    ull OddSum = 0;
    //cout << "ThreadID of findOdd" << std::this_thread::get_id() << endl; //this was to see the threadid
    for (ull i = start; i <= end; ++i) { if (i & 1) { OddSum += i; } }
    return OddSum;
}

int main() {
    
    //async is similar to promise and future and is used to return a value from the thread
    ull start = 0, end = 1900000000;
  //  cout << "ThreadID" << std::this_thread::get_id() << endl;
   
    cout << "Thread created if policy is std::launch::async!!" << endl;
    //std::future<ull> OddSum = std::async(std::launch::async, findOdd, start, end);  //returning a value from the function

    cout << "Waiting For Result!!" << endl;
    cout << "OddSum : " << OddSum.get() << endl;   

    cout << "Completed!!" << endl;
    return 0;
}