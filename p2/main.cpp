#include <iostream>
#include <pthread.h>
#include "nstack.h"     // use Stack

#define N_THREADS 6

int main(){
    cout << "\n========= BASIC PROGRAM =========\n\n";

    pthread_t th_children[N_THREADS];
    char values[N_THREADS];
    int i;

    for (i=0; i<N_THREADS; i++){
        values[i] = i % 2 ? 'A' : 'B';
        pthread_create(&th_children[i], NULL, Stack::push, (void *)&values[i]);
    }

    for (i=0; i<N_THREADS; i++){
        pthread_join(th_children[i], NULL);
    }

    cout << "Stack size: " << Stack::size() << "\nStack items: ";
    while (!Stack::empty()){
        cout << Stack::top() << " ";
        Stack::pop(nullptr);
    }
    
    cout << "\n\n========= END PROGRAM =========\n\n";

    return 0;
}