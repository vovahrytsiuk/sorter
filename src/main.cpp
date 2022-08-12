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
    // CSorterInterface<int> *parallelBucketSorter = new CParallelBucketSorter<int>;
    // CSorterInterface<int> *parallelMergeSorter = new CParallelMergeSorter<int>;
    // CSorterInterface<int> *linearMergeSorter = new CLinearMergeSorter<int>;
    // CSorterInterface<int> *linearBucketSorter = new CLinearBucketSorter<int>;

    // NSCourseWork::test(parallelMergeSorter, "parallelMergeSorter4.csv");
    // NSCourseWork::test(parallelBucketSorter, "parallelBucketSorter4.csv");
    // //NSCourseWork::test(linearBucketSorter, "linearBucketSorter.csv");
    // //NSCourseWork::test(linearMergeSorter, "linearMergeSorter.csv");


    // delete parallelBucketSorter;
    // delete parallelMergeSorter;
    // delete linearBucketSorter;
    // delete linearMergeSorter;

    CParallelBucketSorter<int> sorter;
    static std::vector<int> elementsCount {10, 100, 1000, 10000};
    for (const auto count : elementsCount)
    {
        std::cout << "test on array with " << count << " elements" << std::endl;
        std::vector<int> arr = NSCourseWork::generateArray(count);
        std::cout << "Array is " << (NSCourseWork::isSorted(arr) ? "sorted" : "not sorted") << std::endl;
        std::cout << "sorting" << std::endl;
        sorter.sort(arr);
        std::cout << "Array is " << (NSCourseWork::isSorted(arr) ? "sorted" : "not sorted") << std::endl;
        std::cout << "---------------------------------------------------------------------" << std::endl;
    }

    return 0;
}