#pragma once
#include <vector>
#include "CSorterInterface.h"

namespace NSCourseWork
{
    std::vector<int> generateArray(const size_t size);
    bool isSorted(const std::vector<int> &array);
    void printArray(const std::vector<int> &array);

    void dumpDataToFile(const std::vector<int> &array);
    void test(CSorterInterface<int> *sorter, const std::string& fileName);
};