#pragma once

#include "CSorterInterface.h"
#include <algorithm>

template <class T>
class CStdSorter : public CSorterInterface<T>
{
public: 
    void sort(std::vector<T>& array) override
    {
        std::sort(array.begin(), array.end());
    }
};