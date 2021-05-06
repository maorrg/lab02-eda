#include <pthread.h>
#include <atomic> 
#include <iostream>
#include <vector>
#include <chrono>
#include "constants.h"
#include "fileSystem.h"

atomic <int> thread_number(0);
atomic <numeric> max_value(0);

void updateMaxValue(numeric new_value){
    if(new_value > max_value) max_value = new_value;
}

void* getMax(void* arguments){
    struct arg_struct *args = (struct arg_struct*) arguments;
    vector<numeric> array = args->array;
    int i, num = thread_number++;
    numeric max = 0;
    for(i = args->start; i < args->end; i++){
        if(array[i] > max) max = array[i];
    }
    updateMaxValue(max);
    return NULL;
}

numeric execute(arg_struct* args) {
    int i;
    int range = args->NUM_ELEMENTS/args->NUM_THREADS;
    max_value = 0;
    pthread_t threads[args->NUM_THREADS];
    for(i=0; i < args->NUM_THREADS; i++){
        args->start = i*range;
        if(i == args->NUM_THREADS - 1) args->end = args->array.size();
        else args->end = (i+1)*range;
        pthread_create(&threads[i], NULL, getMax, (void*)args); //CREATE
    }
    for(i=0; i < args->NUM_THREADS; i++){
        pthread_join(threads[i], NULL); //JOIN THREADS
    }
    return max_value;
}

int main(){
    vector<Object> input = getAllVectors();
    double sum_time = 0;
    cout << "-------------- TESTING ATOMIC --------------\n";
    for(int i=0; i < input.size(); i++){
        arg_struct* args = new arg_struct(input[i].num_threads, input[i].numbers.size(),input[i].numbers);
        auto t1 = high_resolution_clock::now();
        numeric result = execute(args);
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms = t2 - t1;
        sum_time += ms.count();
        if( result == input[i].max_number) cout << "Test " << i << " succeed --> [current_max_value = " << result << " & expected_max_value = " << input[i].max_number << "] (# threads = " << input[i].num_threads << ") [" << ms.count() << " ms]\n" << endl;
        else cout << "Test " << i << " failed --> [current_max_value = " << result << " & expected_max_value = " << input[i].max_number << "] (# threads = " << input[i].num_threads << ") [" << ms.count() << " ms]\n";
    }
    cout << "AVERAGE TIME: " << sum_time/input.size() << " ms\n";
    return 0;
}