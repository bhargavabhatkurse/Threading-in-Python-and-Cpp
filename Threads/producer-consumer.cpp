// THE PROBLEM STATEMENT:

// 1. Producer will produce and consumer will consume with synchronisation of a common buffer.

// 2. Until producer thread produces any data consumer thread can't consume.

// 3. Threads will use condition_variable to notify each other.

// 4. We need mutex if we use condition_variable because CV waits on mutex.

// 5. This is one of the example of producer consumer there are many.



// PRODUCER thread steps:

// 1. lock mutex, if success then go ahead otherwise wait for mutex to get free.

// 2. check if buffer is full and if it is full then unlock mutex and sleep, if not then go ahead and produce.

// 3. insert item in buffer.

// 4. unlock mutex. 

// 5. notify consumer.



// CONSUMER thread steps:

// 1. lock mutex, if success then go ahead and consume otherwise wait for mutex to get free.

// 2. check if buffer is empty and if it is, then unlock the mutex and sleep, if not then go ahead and consume.

// 3. consume item from buffer.

// 4. unlock mutex.

// 5. notify producer.



// IMP:

// If you are talking about producer consumer then they have to notify each other.


#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <deque>
#include <condition_variable>
using namespace std;



std::mutex mu;
std::condition_variable cond; //to notify 
deque<int> buffer; //circular queue
const unsigned int maxBufferSize = 50;



void producer(int val) {

     while (val) {  //100 items are produced in total

        std::unique_lock<std::mutex> locker(mu);        //if not acquired, it waits for it.

        cond.wait(locker, [](){return buffer.size() < maxBufferSize;}); //if overflow, waits by releasing the lock

        
        //produces
        buffer.push_back(val);

        cout << "Produced: " << val << endl;

        val--;



        locker.unlock();        //releasing lock

        cond.notify_one();  //notifying consumer

       
       // std::this_thread::sleep_for (std::chrono::seconds(1)); if we do this producer will produce 1 item and it will get consumed immediately


    }

}



void consumer(){

    while (true) {

        std::unique_lock<std::mutex> locker(mu);

        cond.wait(locker, [](){return buffer.size() > 0;});  //if buffer empty, waits after releasing the lock

        
        //consume
        int val = buffer.back();

        buffer.pop_back();

        cout << "Consumed: " << val << endl;



        locker.unlock(); //unlock

        cond.notify_one();//notify producer

    }

}



int main() {

    //order of producer and consumer depends on who acquires the lock first each time 

    std::thread t1(producer, 100);

    std::thread t2(consumer);



    t1.join();

    t2.join();

    return 0;

}