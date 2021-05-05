#include <iostream>
#include <list>
#include <thread>
#include <mutex>

using namespace std;
using stack = list<string>;

stack stk;
//mutex mtx;

void stk_push(string s) {
    //mtx.lock();
    stk.push_front(s);
    //mtx.unlock();
}

void stk_pop() {
    //mtx.lock();
    stk.pop_front();
    //mtx.unlock();
}

int main() {
    //thread threads[10];
    
    //for (int i=0; i<10; ++i) threads[i] = thread(stk_pop,i+1);

    //for (auto& th : threads) th.join();

    stk.push_front("A");
    stk.push_front("B");
    stk.push_front("C");
    stk.push_front("A");
    while (!stk.empty()){
        cout << stk.front() << endl;
        stk.pop_front();
    }
    

    return 0;
}