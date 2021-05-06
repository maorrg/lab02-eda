#ifndef LAB1_GLOBALVARIABLES_H
#define LAB1_GLOBALVARIABLES_H

typedef float numeric;
typedef unsigned int ui;
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

struct arg_struct {
    int NUM_THREADS;
    int NUM_ELEMENTS;
    int start;
    int end;
    vector<numeric> array; 

    arg_struct(int num_threads, int num_elements, vector<numeric> _array){
        NUM_THREADS = num_threads;
        NUM_ELEMENTS = num_elements;
        array = _array;
    }
};

#endif //LAB1_GLOBALVARIABLES_H
