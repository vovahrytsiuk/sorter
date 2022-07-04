#pragma once

#include "CSorterInterface.h"


template <class T>
class CStdSorter : public CSorterInterface<T>
{
public: 
    std::vector<T> sort(const std::vector<T>& array) override;
};