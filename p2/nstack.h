#ifndef N_STACK_H
#define N_STACK_H

#include <list>
#include <thread>
#include <mutex>

using namespace std;

class Stack {
   private:
    list<string> stk;
    //std::mutex mtx;
   public:
    Stack();
    void push(string s) {
        //mtx.lock();
        stk.push_front(s);
        //mtx.unlock();
    }
    void pop() {
        //mtx.lock();
        stk.pop_front();
        //mtx.unlock();
    }
    ~Stack();
};

#endif //N_STACK_H