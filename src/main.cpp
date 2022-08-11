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
    CSorterInterface<int> *parallelBucketSorter = new CParallelBucketSorter<int>;
    CSorterInterface<int> *parallelMergeSorter = new CParallelMergeSorter<int>;
    CSorterInterface<int> *linearMergeSorter = new CLinearMergeSorter<int>;
    CSorterInterface<int> *linearBucketSorter = new CLinearBucketSorter<int>;
    CSorterInterface<int> *stdSorter = new CStdSorter<int>;

    // std::vector<int> arr1 = NSCourseWork::generateArray(5000000);
    // NSCourseWork::dumpDataToFile(arr1);
    // std::vector<int> arr2(arr1);
    // std::vector<int> arr3(arr1);
    // std::vector<int> arr4(arr1);

    // parallelBucketSorter->sortWithDebugInfo(arr1);
    // std::cout << "Sorted " << (NSCourseWork::isSorted(arr1) ? "true" : "false") << std::endl;

    // parallelMergeSorter->sortWithDebugInfo(arr2);
    // std::cout << "Sorted " << (NSCourseWork::isSorted(arr2) ? "true" : "false") << std::endl;

    // linearBucketSorter->sortWithDebugInfo(arr3);
    // std::cout << "Sorted " << (NSCourseWork::isSorted(arr3) ? "true" : "false") << std::endl;

    // linearMergeSorter->sortWithDebugInfo(arr4);
    // std::cout << "Sorted " << (NSCourseWork::isSorted(arr4) ? "true" : "false") << std::endl;

    // NSCourseWork::test(parallelBucketSorter, "../pbs128.csv");
    // NSCourseWork::test(parallelMergeSorter, "../pms128.csv");
    NSCourseWork::test(linearBucketSorter, "lbs10.csv");

    // NSCourseWork::test(linearBucketSorter, "../lbs.csv");
    // NSCourseWork::test(linearMergeSorter, "../lms.csv");

    delete parallelBucketSorter;
    delete parallelMergeSorter;
    delete linearBucketSorter;
    delete linearMergeSorter;
    delete stdSorter;

    return 0;
}