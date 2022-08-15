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

    NSCourseWork::test(linearBucketSorter, "lbs.csv");

    NSCourseWork::test(linearMergeSorter, "lms.csv");

    delete parallelBucketSorter;
    delete parallelMergeSorter;
    delete linearBucketSorter;
    delete linearMergeSorter;

    return 0;
}