#pragma once

#include "CSorterInterface.h"
#include <thread>

template <class T>
class CLinearBucketSorter : public CSorterInterface<T>
{
    static const size_t bucketCount = 10;
    void internalSorter(std::vector<T> &subarray)
    {
        // auto start = std::chrono::steady_clock::now();
        std::sort(begin(subarray), end(subarray));
        // auto finish = std::chrono::steady_clock::now();

        // std::cout << "Bucket sorted: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << std::endl;
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
            size_t i = double((el - min)) / (max - min + 1) * (bucketCount);
            buckets[i].push_back(el);
        }
        auto start = std::chrono::steady_clock::now();

        for (size_t i = 0; i < bucketCount; i++)
        {
            internalSorter(buckets[i]);
        }
        auto finish = std::chrono::steady_clock::now();

        std::cout << "All bucket sorted: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << std::endl;

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