#pragma once
#include <vector>


class CCourseWork final
{
public: 
    std::vector<int> generateArray(const size_t size) const;
    bool isSorted(const std::vector<int>& array) const;
    void printArray(const std::vector<int>& array) const;
};