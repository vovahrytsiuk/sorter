#pragma once
#include <vector>
#include <chrono>
#include <iostream>
#include <string>

template <class T>
class CSorterInterface
{
    static const size_t maxSizeToPrint = 30;

public:
    virtual ~CSorterInterface() = default;
    virtual void sort(std::vector<T> &array) = 0;
    long long sortWithDebugInfo(std::vector<T> &array)
    {
        auto start = std::chrono::steady_clock::now();

        this->sort(array);

        auto finish = std::chrono::steady_clock::now();

        return std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    }
};
