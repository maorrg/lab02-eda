#ifndef TESTER_H
#define TESTER_H

#include <stdexcept>
#include <iostream>
#include <stack>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "../nstack.h"

typedef unsigned int ui;

#ifndef NDEBUG
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` fail in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif

#define NUMBER_OF_TESTS 20
#define MAX_N_THREADS 100

stack<char> stk;

class Tester {
public:
    static void execute() {
        cout << "============= TESTING OPERATIONS =============\n";

        for (int i=0; i<NUMBER_OF_TESTS; i++){
            cout << "=== TEST " << i+1 << "\n";
            testSinglePush();
            testSinglePop();
            testPushStack();
            testPopStack();
            cout << "= pass\n";
        }

        cout << "=============== END TESTING ===============\n\n";
        
    }
private:
    static void testSinglePush() {
        pthread_t thread;
        char item = 'A';
        stk.push(item);

        pthread_create(&thread, NULL, Stack::push, (void*)&item);
        pthread_join(thread, NULL);

        ASSERT(Stack::size() == stk.size(), "\n= [The push operation has a problem]\n");
        ASSERT(Stack::top() == stk.top(), "\n= [The push operation has a problem]\n");
    }

    static void testSinglePop() {
        pthread_t thread;
        stk.pop();

        pthread_create(&thread, NULL, Stack::pop, NULL);
        pthread_join(thread, NULL);

        ASSERT(Stack::size() == stk.size(), "\n= [The pop operation has a problem]\n");
    }

    static void testPushStack() {
        srand (time(NULL));
        pthread_t th_children[MAX_N_THREADS];
        ui nvalues = (ui)rand()%30 + 10;
        char values[MAX_N_THREADS];
        int i;
        
        for (i=0; i<nvalues; i++){
            values[i] = (char)rand()%26 + 65; 
            stk.push(values[i]);
        }

        for (i=0; i<nvalues; i++)
            pthread_create(&th_children[i], NULL, Stack::push, (void*)&values[i]);

        for (i=0; i<nvalues; i++) pthread_join(th_children[i], NULL);

        ASSERT(Stack::size() == stk.size(), "\n= [The push operation has a problem]\n");
    }
    
    static void testPopStack() {
        srand (time(NULL));
        pthread_t th_children[MAX_N_THREADS];
        ui nvalues = (ui)rand()%stk.size() + 1;
        int i;
        
        for (i=0; i<nvalues; i++) stk.pop();

        for (i=0; i<nvalues; i++)
            pthread_create(&th_children[i], NULL, Stack::pop, NULL);

        for (i=0; i<nvalues; i++) pthread_join(th_children[i], NULL);

        ASSERT(Stack::size() == stk.size(), "\n= [The pop operation has a problem]\n");
    }
};

#endif