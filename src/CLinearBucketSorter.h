#pragma once

#include "CSorterInterface.h"
#include "CLinearMergerSorter.h"
#include <thread>

template <class T>
class CLinearBucketSorter : public CSorterInterface<T>
{
    static const size_t bucketCount = 100;
    void internalSorter(std::vector<T> &subarray)
    {
        static CLinearMergeSorter<T> sorter;
        sorter.sort(subarray);
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


    void splitData(const std::vector<T>& array, std::vector<T> buckets[])
    {
        T max, min;
        getMaxAndMinValue(array, max, min);

        for (const auto &el : array)
        {
            size_t i = double((el - min)) / (max - min + 1) * (bucketCount);
            buckets[i].push_back(el);
        }
    }

public:
    void sort(std::vector<T> &array) override
    {
        // std::cout << "Linear Bucket Sorter " << std::endl;
        std::vector<T> buckets[bucketCount];

        auto timebox1 = std::chrono::steady_clock::now();

        splitData(array, buckets);

        auto timebox2 = std::chrono::steady_clock::now();

        std::cout << "All bucket splitted: " << std::chrono::duration_cast<std::chrono::milliseconds>(timebox2 - timebox1).count() << std::endl;

        auto start = std::chrono::steady_clock::now();

        for (size_t i = 0; i < bucketCount; i++)
        {
            internalSorter(buckets[i]);
        }
        auto finish = std::chrono::steady_clock::now();

        std::cout << "All bucket sorted: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << std::endl;

        array.clear();

        auto timebox5 = std::chrono::steady_clock::now();

        for (const auto &bucket : buckets)
        {
            for (const auto &el : bucket)
            {
                array.push_back(el);
            }
        }

        auto timebox7 = std::chrono::steady_clock::now();

        std::cout << "All bucket sorted: " << std::chrono::duration_cast<std::chrono::milliseconds>(timebox7 - timebox5).count() << std::endl;
    }
};