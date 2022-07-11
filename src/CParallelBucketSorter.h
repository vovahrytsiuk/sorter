#pragma once
#include "CSorterInterface.h"
#include <thread>
#include <mutex>

template <class T>
void internalSorter(std::vector<T> &subarray)
{
    // auto start = std::chrono::steady_clock::now();
    std::sort(begin(subarray), end(subarray));
    // auto finish = std::chrono::steady_clock::now();

    // std::cout << "Bucket sorted: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << std::endl;
}

static std::mutex mtx;

template <class T>
class CParallelBucketSorter : public CSorterInterface<T>
{
    static const size_t bucketCount = 4;

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

    static void splitDataToBuckets(const std::vector<T> &array, std::vector<std::vector<T> >& buckets, const T &max, const T &min, const size_t startIndex, const size_t finalIndex)
    {
        auto start = std::chrono::steady_clock::now();
        for (size_t i = startIndex; i < finalIndex && i < array.size(); ++i)
        {
            size_t pos = double((array[i] - min)) / (max - min + 1) * (bucketCount);

            mtx.lock();
            buckets[pos].push_back(array[i]);
            mtx.unlock();
        }
        auto finish = std::chrono::steady_clock::now();

        std::cout << "Bucket plitted: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << std::endl;
    }

    void splitData(const std::vector<T>& array, std::vector<std::vector<T> >& buckets)
    {
        T max, min;
        getMaxAndMinValue(array, max, min);

        for (const auto &el : array)
        {
            size_t i = size_t(double((el - min)) / (max - min + 1) * (bucketCount));
            buckets[i].push_back(el);
        }
    }

    void parallelSplitData(const std::vector<T>& array, std::vector<std::vector<T> >& buckets)
    {
        size_t intervalSize = array.size() / bucketCount + 1;
        std::vector<std::thread> splitTasks;

        for (size_t i = 0; i < bucketCount; ++i)
        {
            splitTasks.push_back(std::thread(splitDataToBuckets, std::ref(array), std::ref(buckets), std::ref(max), std::ref(min), i * intervalSize, (i + 1) * intervalSize));
        }

        for (std::thread &t : splitTasks)
        {
            if (t.joinable())
            {
                t.join();
            }
        }
    }

    static void pourBucket(std::vector<T>& array, const std::vector<T>& bucket, const size_t startPos)
    {
        std::cout << startPos << "\n";
        for (size_t i = 0; i < bucket.size(); ++i)
        {
            array[i + startPos] = bucket[i];
        }
    }

    void pourBuckets(std::vector<T>& array, const std::vector<std::vector<T> >& buckets)
    {
        size_t index = 0;
        for (const auto& bucket: buckets)
        {
            pourBucket(array, bucket, index);
            index += bucket.size();
        }
    }

    void pourBucketsParallel(std::vector<T>& array, const std::vector<std::vector<T> >& buckets)
    {
        std::vector<std::thread> pourTasks;

        size_t index = 0;
        for (const auto& bucket : buckets)
        {
            pourTasks.emplace_back(pourBucket, std::ref(array), std::ref(bucket), index);
            index += bucket.size();
        }

        for (std::thread &t : pourTasks)
        {
            if (t.joinable())
            {
                t.join();
            }
        }
    }

public:
    void sort(std::vector<T> &array) override
    {
        std::vector<std::vector<T> > buckets(bucketCount);

        T max, min;
        getMaxAndMinValue(array, max, min);

        // for (const auto &el : array)
        // {
        //     size_t i = double((el - min)) / (max - min + 1) * (bucketCount);
        //     buckets[i].push_back(el);
        // }
        auto start1 = std::chrono::steady_clock::now();
        // size_t intervalSize = array.size() / bucketCount + 1;
        // std::vector<std::thread> splitTasks;
        // for (size_t i = 0; i < bucketCount; ++i)
        // {
        //     splitTasks.push_back(std::thread(splitDataToBuckets, std::ref(array), std::ref(buckets), std::ref(max), std::ref(min), i * intervalSize, (i + 1) * intervalSize));
        // }
        // for (std::thread &t : splitTasks)
        // {
        //     if (t.joinable())
        //     {
        //         t.join();
        //     }
        // }
        splitData(array, buckets);
        auto finish1 = std::chrono::steady_clock::now();

        std::cout << "All bucket splitted: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish1 - start1).count() << std::endl;

        auto start = std::chrono::steady_clock::now();

        std::vector<std::thread> tasks;
        for (size_t i = 0; i < bucketCount; ++i)
        {
            tasks.push_back(std::thread(internalSorter<T>, std::ref(buckets[i])));
        }

        for (std::thread &t : tasks)
        {
            if (t.joinable())
            {
                t.join();
            }
        }

        auto finish = std::chrono::steady_clock::now();

        std::cout << "All bucket sorted: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << std::endl;

        auto timebox6 = std::chrono::steady_clock::now();

        pourBucketsParallel(array, buckets);

        auto timebox7 = std::chrono::steady_clock::now();

        std::cout << "All bucket poured: " << std::chrono::duration_cast<std::chrono::milliseconds>(timebox7 - timebox6).count() << std::endl;
    }
};