// 1. Condition variables allow us to synchronise threads via notifications.
//    a. notify_one();
//    b. notify_all();
// 2. You need mutex to use condition variable
// 3. Condition variable is used to synchronise two or more threads.
// 4. Best use case of condition variable is Producer/Consumer problem.
// 5. Condition variables can be used for two purposes:
//     a. Notify other threads
//     b. Wait for some condition


#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

condition_variable cv;
mutex m;
int balance =0;

void addmoney(int money) {
   lock_guard<mutex> lg(m);      //acquire lock, or wait if not available
   balance += money;
   cout<<"amount added";
   cv.notify_one();
}

void withdraw(int money) {
   unique_lock<mutex> ul(m); //acquire lock, or wait if not available
   cv.wait(ul, [] {return (balance!=0)?true:false; });      //wait till someone notifies
   //cv.wait() will release the lock m and will wait till notified. 
   //after getting notified, it will check its own condition (balance!=0), before proceeding

   if(balance>=money) {
      balance-=money;
      cout<<endl<<"amount deducted "<<endl;
   }
   else 
         cout<<endl<<"insufficient balance"<<endl;
  
}
int main(){

   //t2 will always run first, and then notify t1;
   thread t1(withdraw,500);
   thread t2(addmoney,500);


   t1.join();
   t2.join();

   return 0;
}