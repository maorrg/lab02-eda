#ifndef TESTER_H
#define TESTER_H

#include <stdexcept>
#include <iostream>
#include <stack>
#include <map>
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
            testCorrectItems();
            testPushStack();
            testPopStack();
            cout << "= pass\n";
        }

        cout << "=============== END TESTING ===============\n\n";
        
    }

    static void testSinglePush(bool unit = false) {
        if (unit) cout << "\n=== TESTING SINGLE PUSH\n";
        pthread_t thread;
        char item = 'A';
        dummyData(0);

        stk.push(item);

        pthread_create(&thread, NULL, Stack::push, (void*)&item);
        pthread_join(thread, NULL);

        ASSERT(Stack::size() == stk.size(), "\n= [The push operation has a problem]\n");
        ASSERT(Stack::top() == stk.top(), "\n= [The push operation has a problem]\n");
        if (unit) cout << "= pass \n\n";
    }

    static void testCorrectItems(bool unit = false) {
        if (unit) cout << "\n=== TESTING CORRECT ITEMS\n";
        pthread_t th_children[7];
        char values[7] = {'A','B','B','B','C','A','B'};
        dummyData(0);
        map<char, int> validator;
        int i;

        for (i=0; i<7; i++) 
            pthread_create(&th_children[i], NULL, Stack::push, (void*)&values[i]);
        
        for (i=0; i<7; i++) pthread_join(th_children[i], NULL);

        ASSERT(Stack::size() == 7, "\n= [The push operation has a problem]\n");

        while(!Stack::empty()) {
            validator[Stack::top()]++;
            Stack::pop(nullptr);
        }

        ASSERT(validator['A'] == 2, "\n= [The push or pop operation has a problem]\n");
        ASSERT(validator['B'] == 4, "\n= [The push or pop operation has a problem]\n");
        ASSERT(validator['C'] == 1, "\n= [The push or pop operation has a problem]\n");

        if (unit) cout << "= pass \n\n";
    }

    static void testSinglePop(bool unit = false) {
        if (unit) cout << "\n=== TESTING SINGLE POP\n";
        pthread_t thread;
        dummyData(5);
        
        stk.pop();

        pthread_create(&thread, NULL, Stack::pop, NULL);
        pthread_join(thread, NULL);

        ASSERT(Stack::size() == stk.size(), "\n= [The pop operation has a problem]\n");
        if (unit) cout << "= pass \n\n";
    }

    static void testPushStack(bool unit = false) {
        if (unit) cout << "\n=== TESTING MULTIPLE PUSH\n";
        srand (time(NULL));
        pthread_t th_children[MAX_N_THREADS];
        dummyData(0);
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
        if (unit) cout << "= pass \n\n";
    }
    
    static void testPopStack(bool unit = false) {
        if (unit) cout << "\n=== TESTING MULTIPLE POP\n";
        srand (time(NULL));
        pthread_t th_children[MAX_N_THREADS];
        dummyData(50);
        ui nvalues = (ui)rand()%stk.size() + 1;
        int i;
        
        for (i=0; i<nvalues; i++) stk.pop();

        for (i=0; i<nvalues; i++)
            pthread_create(&th_children[i], NULL, Stack::pop, NULL);

        for (i=0; i<nvalues; i++) pthread_join(th_children[i], NULL);

        ASSERT(Stack::size() == stk.size(), "\n= [The pop operation has a problem]\n");
        if (unit) cout << "= pass \n\n";
    }

private:
    static void dummyData(ui n) {
        Stack::stk.clear();
        stk = stack<char>();
        if (n>0) {
            deque<char> support(n, 'A');
            Stack::stk = list<char>(n, 'A');
            stk = stack<char>(support);
        }
    }
};

#endif