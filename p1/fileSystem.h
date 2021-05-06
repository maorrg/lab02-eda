#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "constants.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

struct Object{
    vector<numeric> numbers;
    int num_threads;
    numeric max_number;
};

vector<string> split(const string &s, char delim) {
        vector<string> elems;
        stringstream ss(s);
        string item;
        while (getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
}

vector<Object> getAllVectors(){
    vector<Object> result;
    ifstream file("./data/input.txt");
    string line;
    getline(file, line);
    while(getline(file, line)){
        vector<string> split_line = split(line, ' ');
        Object object;
        object.num_threads = stoi(split_line[0]);
        object.max_number = stof(split_line[1]);
        for(int i=2; i < split_line.size(); i++){
            object.numbers.push_back(stof(split_line[i]));
        }
        result.push_back(object);
    }
    return result;
}




#endif //FILE_SYSTEM_H
