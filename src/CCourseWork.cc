#include "CCourseWork.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>

namespace
{
    const size_t kMaxValue = 1000000000;
    const size_t kTestCaseCount = 9;
    const size_t kTestCaseSizes[] = {10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
}

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
    std::generate(arr.begin(), arr.end(),
                  []
                  { return std::rand() % kMaxValue; });
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

void NSCourseWork::dumpDataToFile(const std::vector<int> &array)
{
    std::ofstream out("array.csv");
    for (size_t i = 0; i < array.size(); ++i)
    {
        out << i << "," << array[i] << "\n";
    }
}

void NSCourseWork::test(CSorterInterface<int> *sorter, const std::string &fileName)
{
    std::ofstream out(fileName, std::ofstream::out | std::ofstream::trunc);
    for (size_t i = 0; i < kTestCaseCount; ++i)
    {
        std::vector<int> arr = generateArray(kTestCaseSizes[i]);
        out << kTestCaseSizes[i] << "," << sorter->sortWithDebugInfo(arr) << std::endl;
    }
}