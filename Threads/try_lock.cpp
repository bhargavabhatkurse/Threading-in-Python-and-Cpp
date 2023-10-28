
/*
0. std::try_lock() tries to lock all the mutexes passed in it one by one in given order.

1. On success this function returns -1 otherwise it will return 0-based mutex index number which it could not lock.

2. If it fails to lock any of the mutex then it will release all the mutex it locked before.

3. If a call to try_lock results in an exception, unlock is called for any locked objects before rethrowing.

*/


#include <mutex>
#include <thread>
#include <iostream>
#include <chrono>
using namespace std;



int X=0, Y=0;

std::mutex m1, m2;



void doSomeWorkForSeconds(int seconds) { std::this_thread::sleep_for(std::chrono::seconds(seconds)); }



void incrementXY(int& XorY, std::mutex& m, const char* desc) {

    for(int i=0; i<5; ++i){
        m.lock();		//blocking lock

            ++XorY;

        cout<< desc << XorY << '\n';

        m.unlock();

       doSomeWorkForSeconds(1);		//this is so that another thread can acquire the lock
       								//the same thread cannot acquire the lock again. for that we will have to use recursive mutex

   }

}



void consumeXY () {

    int useCount = 5;		//do it 5 times

    int XplusY = 0;

    while(1){

        int lockResult = std::try_lock(m1,m2); //acquire locks

        if(lockResult == -1){

            if(X!=0 && Y!=0){   //while x and y buffers are not empty

                --useCount;

                XplusY+=X+Y;

               //set the buffers as empty
                X = 0;

                Y = 0;

                cout << "XplusY " << XplusY << '\n';

            }

            //release locks 
            m1.unlock();

            m2.unlock();
   

            if(useCount == 0) break;

        }

    }

}



int main() {

    std::thread t1(incrementXY, std::ref(X), std::ref(m1), "X ");

    std::thread t2(incrementXY, std::ref(Y), std::ref(m2), "Y ");

    

    std::thread t3(consumeXY);



    t1.join();

    t2.join();

    t3.join();

    return 0;

}
