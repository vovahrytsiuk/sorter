#include "CStdSorter.h"


template <class T>
std::vector<T> CStdSorter<T>::sort(const std::vector<T>& array)
{
    std::vector<T> sorted(array);
    std::sort(sorted.begin(), sorted.end(), [](int i, int j) {return i > j; });
    return sorted;
}