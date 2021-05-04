#include <pthread.h>
#include <mutex> 
#include <iostream>

#define N_ELEMENTS 8
#define TH_NUMBER 4

typedef float numeric;
typedef unsigned int ui;
using namespace std;

numeric a[N_ELEMENTS] = {0,1,8.8,3,8,5,6,7};
int thread_number = 0;
numeric max_value = 0;
mutex mtx; 

int accesThreadNumer(){
    int id = 0;
    mtx.lock();
    id = thread_number++;
    mtx.unlock();
    return id;
}

void updateMaxValue(numeric new_value){
    mtx.lock();
    if(new_value > max_value) max_value = new_value;
    mtx.unlock();
}

void* getMax(void*){
    int i, num = accesThreadNumer();
    numeric max = 0;
    for(i = num * (N_ELEMENTS/4); i < (num+1) * (N_ELEMENTS/4); i++){
        if(a[i] > max) max = a[i];
    }
    updateMaxValue(max);
    return NULL;
}

int main() {
    int i;
    pthread_t threads[TH_NUMBER];
    for(i=0; i < TH_NUMBER; i++){
        pthread_create(&threads[i], NULL, getMax, (void*) NULL); //CREATE
    }
    for(i=0; i < TH_NUMBER; i++){
        pthread_join(threads[i], NULL); //JOIN THREADS
    }
    cout << "El valor máximo calculado entre " << TH_NUMBER << " threads es " << max_value << endl;
}