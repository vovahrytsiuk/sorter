#include "CCourseWork.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <vector>


bool CCourseWork::isSorted(const std::vector<int>& array) const
{
    for (size_t i = 1; i < array.size(); i++)
    {
        if (array[i] < array[i - 1])
        {
            return false;
        }
    }
    return true;
}


std::vector<int> CCourseWork::generateArray(const size_t size) const
{
    std::vector<int> arr(size, 0);
    srand(time(NULL));
    std::generate(arr.begin(), arr.end(), rand);
    return arr;
}


void CCourseWork::printArray(const std::vector<int>& array) const
{
    for (const auto e : array)
    {
        std::cout << e << " \t";
    }
    std::cout << "\n";
}