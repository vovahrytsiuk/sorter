#pragma once

#include <pthread.h>
#include "CSorterInterface.h"

template <class T>
class CParallelMergeSorter : public CSorterInterface<T>
{
public:
    void sort(std::vector<T> &array) override
    {
    }
};