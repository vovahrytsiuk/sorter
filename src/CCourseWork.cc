#include "CCourseWork.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <vector>

bool NSCourseWork::isSorted(const std::vector<int> &array)
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

std::vector<int> NSCourseWork::generateArray(const size_t size)
{
    std::vector<int> arr(size, 0);
    srand(time(NULL));
    std::generate(arr.begin(), arr.end(), rand);
    return arr;
}

void NSCourseWork::printArray(const std::vector<int> &array)
{
    for (const auto e : array)
    {
        std::cout << e << " \t";
    }
    std::cout << "\n";
}