#include <iostream>
#include "CCourseWork.h"
#include "CStdSorter.h"
#include "CSorterInterface.h"
#include "CLinearMergerSorter.h"
#include "CLinearBucketSorter.h"
#include "CParallelBucketSorter.h"
#include "CParallelMergeSorter.h"

int main()
{
    CSorterInterface<int> *sorter = new CParallelBucketSorter<int>;

    auto arr = NSCourseWork::generateArray(500);
    NSCourseWork::dumpArrayToFile(arr);
    sorter->sortWithDebugInfo(arr);

    std::cout << NSCourseWork::isSorted(arr) << std::endl;
    std::cout << arr.size() << std::endl;

    return 0;
}