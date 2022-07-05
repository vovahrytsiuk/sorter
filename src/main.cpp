#include <iostream>
#include "CCourseWork.h"
#include "CStdSorter.h"
#include "CSorterInterface.h"
#include "CLinearMergerSorter.h"

int main()
{
    std::cout << "Hello world" << std::endl;
    const CCourseWork worker;
    CSorterInterface<int>* sorter = new CLinearMergeSorter<int>;

    auto arr = worker.generateArray(500000);
    // worker.printArray(arr);
    sorter->sortWithDebugInfo(arr);
    // worker.printArray(arr);

    std::cout << worker.isSorted(arr) << std::endl;
    std::cout << arr.size();
    
    delete sorter;
    return 0;
}