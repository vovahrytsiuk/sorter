#pragma once
#include <vector>
#include <chrono>
#include <iostream>


template <class T>
class CSorterInterface
{
public: 
    virtual void sort(std::vector<T>& array) = 0;
    void sortWithDebugInfo(std::vector<T>& array)
    {
        auto start = std::chrono::high_resolution_clock::now();

        this->sort(array);

        auto finish = std::chrono::high_resolution_clock::now();

        std::cout << "Time: " << (finish - start).count() << std::endl;
    }
};
