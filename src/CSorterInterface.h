#pragma once
#include <vector>
#include <chrono>
#include <iostream>
#include "CCourseWork.h"

template <class T>
class CSorterInterface
{
    static const size_t maxSizeToPrint = 30;

public:
    virtual void sort(std::vector<T> &array) = 0;
    void sortWithDebugInfo(std::vector<T> &array)
    {
        auto start = std::chrono::steady_clock::now();

        if (array.size() <= maxSizeToPrint)
        {
            NSCourseWork::printArray(array);
        }

        this->sort(array);

        if (array.size() <= maxSizeToPrint)
        {
            NSCourseWork::printArray(array);
        }

        auto finish = std::chrono::steady_clock::now();

        std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << std::endl;
    }
};
