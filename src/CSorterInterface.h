#pragma once
#include <vector>


template <class T>
class CSorterInterface
{
public: 
    virtual std::vector<T> sort(const std::vector<T>& array) = 0;
};