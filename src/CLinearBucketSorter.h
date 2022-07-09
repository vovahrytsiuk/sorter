#pragma once

#include "CSorterInterface.h"

template <class T>
class CLinearBuckerSorter : public CSorterInterface<T>
{
    static const size_t bucketCount = 5;
    void internalSorter(std::vector<T> &subarray)
    {
        std::sort(begin(subarray), end(subarray));
    }

    void getMaxAndMinValue(const std::vector<T> &array, T &max, T &min)
    {
        max = array.front();
        min = array.front();

        for (size_t i = 1; i < array.size(); i++)
        {
            if (array[i] > max)
            {
                max = array[i];
            }
            else if (array[i] < min)
            {
                min = array[i];
            }
        }
    }

public:
    void sort(std::vector<T> &array) override
    {
        std::vector<T> buckets[bucketCount];

        T max, min;
        getMaxAndMinValue(array, max, min);

        for (const auto &el : array)
        {
            size_t i = (el - min) / (max - min) * (bucketCount - 1);
            buckets[i].push_back(el);
        }

        for (size_t i = 0; i < bucketCount; i++)
        {
            internalSorter(buckets[i]);
        }

        array.clear();

        for (const auto &bucket : buckets)
        {
            for (const auto &el : bucket)
            {
                array.push_back(el);
            }
        }
    }
};