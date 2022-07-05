#pragma once

#include "CSorterInterface.h"


template <class T>
class CLinearMergeSorter : public CSorterInterface<T>
{
    void mergeSort(std::vector<T>& array, const size_t begin, const size_t end)
    {
        if (begin >= end)
            return;

        auto mid = begin + (end - begin) / 2;
        mergeSort(array, begin, mid);
        mergeSort(array, mid + 1, end);
        merge(array, begin, mid, end);
    }

    void merge(std::vector<T>& array, const size_t left, const size_t mid, const size_t right)
    {
        const auto leftSubArraySize = mid - left + 1;
        const auto rightSubArraySize = right - mid;

        std::vector<T>::const_iterator leftFirst = array.begin() + left;
        std::vector<T>::const_iterator leftLast = array.begin() + mid + 1;
        std::vector<T> leftArray(leftFirst, leftLast);

        std::vector<T>::const_iterator rightFirst = array.begin() + mid + 1;
        std::vector<T>::const_iterator rightLast = array.begin() + right + 1;
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
    void sort(std::vector<T>& array) override 
    {
        mergeSort(array, 0, array.size() - 1);
    }
};