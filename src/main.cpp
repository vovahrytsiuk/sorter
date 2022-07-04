#include <iostream>
#include "CCourseWork.h"
#include "CStdSorter.h"

int main()
{
    std::cout << "Hello world" << std::endl;
    const CCourseWork worker;
    CStdSorter<int> sorter;

    const auto arr = worker.generateArray(100);
    std::cout << worker.isSorted(sorter.sort(arr)) << std::endl;
    return 0;
}