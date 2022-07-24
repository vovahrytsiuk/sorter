#pragma once
#include <vector>

namespace NSCourseWork
{
    std::vector<int> generateArray(const size_t size);
    bool isSorted(const std::vector<int> &array);
    void printArray(const std::vector<int> &array);

    void dumpArrayToFile(const std::vector<int> &array);
};