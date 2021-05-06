#ifndef N_STACK_H
#define N_STACK_H

#include <list>
#include <thread>
#include <mutex>

using namespace std;

// encapsulate Stack implementation

namespace Stack {

    list<char> stk;
    mutex mtx;
 
    void* push(void* s) {
        const lock_guard<mutex> lock(mtx);
        stk.push_front(*(char*)s);
        return nullptr;
        // mtx is released when lock goes out of scope
    }
    void* pop(void* arg) {
        const lock_guard<mutex> lock(mtx);
        stk.pop_front();
        return nullptr;
        // mtx is released when lock goes out of scope
    }
    char top() {
        const lock_guard<mutex> lock(mtx);
        return stk.front();
        // mtx is released when lock goes out of scope
    }
    int size() {
        const lock_guard<mutex> lock(mtx);
        return stk.size();
        // mtx is released when lock goes out of scope
    }
    int empty() {
        const lock_guard<mutex> lock(mtx);
        return stk.empty();
        // mtx is released when lock goes out of scope
    }

} // namespace Stack

#endif //N_STACK_H