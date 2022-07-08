#include <iostream>
#include "CCourseWork.h"
#include "CStdSorter.h"
#include "CSorterInterface.h"
#include "CLinearMergerSorter.h"
#include "CLinearBucketSorter.h"

int main()
{
    std::cout << "Hello world" << std::endl;
    CSorterInterface<int> *sorter = new CLinearBuckerSorter<int>;

    auto arr = NSCourseWork::generateArray(5000);
    sorter->sortWithDebugInfo(arr);

    std::cout << NSCourseWork::isSorted(arr) << std::endl;
    std::cout << arr.size() << std::endl;
    return 0;
}