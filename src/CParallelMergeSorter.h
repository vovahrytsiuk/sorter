#pragma once

#include <pthread.h>
#include "CSorterInterface.h"

template <class T>
class CParallelMergeSorter : public CSorterInterface<T>
{
    static const size_t buctetsCount = 10;

public:
    void sort(std::vector<T> &array) override
    {
    }
};