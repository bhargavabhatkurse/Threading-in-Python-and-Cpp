// NOTES:

// 1. std::promise

//      a. Used to set values or exceptions.

// 2. std::future

//      a. Used to get values from promise.

//      b. Ask promise if the value is available.

//      c. Wait for the promise.


#include <iostream>

#include <thread>

#include <chrono>

#include <algorithm>

#include <future>

using namespace std;

using namespace std::chrono;

typedef long int ull;



void findOdd(std::promise<ull>&& OddSumPromise, ull start, ull end) {

    ull OddSum = 0;

    for (ull i = start; i <= end; ++i){

        if (i & 1){

            OddSum += i;

        }

    }

    OddSumPromise.set_value(OddSum);        //setting the promise

    //assume this calculation takes 3 seconds

}



int main() {


    // with promise and future, we can return a value from the thread to the main thread
    

    ull start = 0, end = 1900000000;



    std::promise<ull> OddSum;   //promise is created

    std::future<ull> OddFuture = OddSum.get_future();       //oddfuture will contain the future value of the promise

    

    cout << "Thread Created!!" << endl;

    std::thread t1(findOdd, std::move(OddSum), start, end);   //as soon as this is done, the oddSum calculation will start

    

    cout << "Waiting For Result!!" << endl;

    //assume there are more commands and they take 5 seconds



    cout << "OddSum : " << OddFuture.get() << endl;     //if the value of  OddFuture.get() is not available, it will wait
                                                        //assume in 3 seconds, it arrives

    //so the final time is 5 seconds not 8 seconds (5+3) because oddsum calculation was happening simultaneously

    //in this was not used, total time wouldve been 8 sec as first we will execute the commands which take 5 seconds and then 
    //do a function call to oddsum;

    cout << "Completed!!" << endl;

    t1.join();

    return 0;

}