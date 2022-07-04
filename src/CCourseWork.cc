#include "CCourseWork.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <vector>


bool CCourseWork::isSorted(const std::vector<int>& array) const
{
    for (size_t i = 1; i < array.size(); i++)
    {
        if (array[i] > array[i - 1])
        {
            return false;
        }
    }
    return true;
}


std::vector<int> CCourseWork::generateArray(const size_t size) const
{
    std::vector<int> arr(size, 0);
    srand(time(0));
    std::generate(arr.begin(), arr.end(), rand);
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
  
    return arr;
}