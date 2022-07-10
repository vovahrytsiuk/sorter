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

    static void splitDataToBuckets(const std::vector<T> &array, std::vector<T> buckets[], const T &max, const T &min, const size_t startIndex, const size_t finalIndex)
    {
        auto start = std::chrono::steady_clock::now();
        for (size_t i = startIndex; i < finalIndex && i < array.size(); ++i)
        {
            size_t pos = double((array[i] - min)) / (max - min + 1) * (bucketCount);
            mtx.lock();
            buckets[pos].push_back(array[i]);
            // std::cout << std::this_thread::get_id() << " " << i << "\n";
            // std::cout << i << "\n";
            mtx.unlock();
        }
        auto finish = std::chrono::steady_clock::now();

        std::cout << "Bucket plitted: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << std::endl;
    }

public:
    void sort(std::vector<T> &array) override
    {
        std::vector<T> buckets[bucketCount];

        T max, min;
        getMaxAndMinValue(array, max, min);

        // for (const auto &el : array)
        // {
        //     size_t i = double((el - min)) / (max - min + 1) * (bucketCount);
        //     buckets[i].push_back(el);
        // }
        auto start1 = std::chrono::steady_clock::now();
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
        auto finish1 = std::chrono::steady_clock::now();

        std::cout << "All bucket splitted: " << std::chrono::duration_cast<std::chrono::milliseconds>(finish1 - start1).count() << std::endl;

        // for (const auto &bucket : buckets)
        // {
        //     std::cout << "bucket";
        //     for (const auto &el : bucket)
        //         std::cout << el << " ";
        //     std::cout << "\n";
        // }

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
        array.clear();

        for (const auto &bucket : buckets)
        {
            for (const auto &el : bucket)
            {
                array.emplace_back(el);
            }
        }
    }
};