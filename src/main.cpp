#include <iostream>
#include "CCourseWork.h"
#include "CStdSorter.h"
#include "CSorterInterface.h"
#include "CLinearMergerSorter.h"
#include "CLinearBucketSorter.h"
#include "CParallelBucketSorter.h"

int main()
{
    std::cout << "Hello world" << std::endl;
    CSorterInterface<int> *sorter = new CParallelBucketSorter<int>;

    auto arr = NSCourseWork::generateArray(5000000);
    sorter->sortWithDebugInfo(arr);

    std::cout << NSCourseWork::isSorted(arr) << std::endl;
    std::cout << arr.size() << std::endl;

    std::vector<int> arr1(100);
    return 0;
}