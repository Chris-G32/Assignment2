#ifndef PROCESS_HPP_
#define PROCESS_HPP_
#include "Resources.hpp"

class ProcessResources{
public:
    ProcessResources();
    ~ProcessResources(){
        delete[] maxAlloc;
        delete[] allocated;
    }
    int *maxAlloc;
    int *allocated;
};

#endif