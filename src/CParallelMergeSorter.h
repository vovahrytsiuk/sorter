#pragma once

#include <thread>
#include "CSorterInterface.h"
#include "CCourseWork.h"

template <class T>
class CParallelMergeSorter : public CSorterInterface<T>
{
    static const size_t threadCount = 2;
    static void mergeSort(std::vector<T> &array, const size_t begin, const size_t end)
    {
        const size_t finish = (end >= array.size() ? (array.size() - 1) : end);

        if (begin >= finish)
            return;

        auto mid = begin + (finish - begin) / 2;
        mergeSort(array, begin, mid);
        mergeSort(array, mid + 1, finish);
        merge(array, begin, mid, finish);
    }

    static void merge(std::vector<T> &array, const size_t left, const size_t mid, const size_t right)
    {
        const auto leftSubArraySize = mid - left + 1;
        const auto rightSubArraySize = right - mid;

        if (leftSubArraySize == 0 && rightSubArraySize == 0)
            return;

        typedef typename std::vector<T>::const_iterator iterator;
        iterator leftFirst = array.begin() + left;
        iterator leftLast = array.begin() + mid + 1;
        std::vector<T> leftArray(leftFirst, leftLast);

        iterator rightFirst = array.begin() + mid + 1;
        iterator rightLast = array.begin() + right + 1;
        std::vector<T> rightArray(rightFirst, rightLast);

        size_t indexOfSubArrayOne = 0;
        size_t indexOfSubArrayTwo = 0;
        size_t indexOfMergedArray = left;

        while (indexOfSubArrayOne < leftSubArraySize && indexOfSubArrayTwo < rightSubArraySize)
        {
            if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo])
            {
                array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            }
            else
            {
                array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }
            indexOfMergedArray++;
        }

        while (indexOfSubArrayOne < leftSubArraySize)
        {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
            indexOfMergedArray++;
        }

        while (indexOfSubArrayTwo < rightSubArraySize)
        {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
            indexOfMergedArray++;
        }
    }

public:
    // clang-format off
    void sort(std::vector<T> &array) override
    {
        // std::cout << "Parallel Merge Sorter " << std::endl;
        const size_t intervalSize = array.size() / threadCount + 1;

        std::vector<std::thread> mergeSortTasks;

        std::vector<size_t> beginSubArrayIndexes(threadCount);
        std::vector<size_t> finishSubArrayIndexes(threadCount);


        for (size_t i = 0; i < threadCount; ++i)
        {
            mergeSortTasks.emplace_back(mergeSort, std::ref(array), i * intervalSize, (i + 1) * intervalSize - 1);
            beginSubArrayIndexes[i] = std::min(i * intervalSize, array.size() - 1);
            finishSubArrayIndexes[i] = std::min((i + 1) * intervalSize, array.size()) - 1;
        }

        for (auto& t : mergeSortTasks)
        {
            if (t.joinable())
            {
                t.join();
            }
        }

        // merging sorted parts of array
        const size_t begin = 0;
        size_t mid = finishSubArrayIndexes[0];
        size_t finish = 0;

        for (size_t i = 1; i < threadCount; ++i)
        {
            finish = finishSubArrayIndexes[i];
            merge(array, begin, mid, finish);
            mid = finishSubArrayIndexes[i];
        }
    }
    // clang-format on
};