#ifndef TIMSORT_H
#define TIMSORT_H

#include <vector>
#include <iostream>
using namespace std;

class Timsort
{
private:
    int getMinrun(int n);
    void insertionSort(vector<int> *run);
    void mergeSort(vector<vector<int>> *runs);
public:
    void timsort(vector<int> *list);
    vector<vector<int>> slicer(vector<int> *list);
};

void Timsort::timsort(vector<int> *list)
{
    int minrun = getMinrun(list->size());

}


int Timsort::getMinrun(int n)
{
//    Наиболее эффективно использовать значения из диапазона (32;65).
//    Исключение — если N < 64, тогда minrun = N и timsort превращается в
//    простую сортировку вставкой. В данный момент алгоритм расчёта minrun
//    просто до безобразия: берём старшие 6 бит из N и добавляем единицу,
//    если в оставшихся младших битах есть хотя бы один ненулевой.
    int r = 0;
    while (n >= 64)
    {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

vector<vector<int>> Timsort::slicer(vector<int> *list)
{
    // TODO: FIX THAT KIDDO
    int minrun = getMinrun(list->size());
    vector<vector<int>> result;
    size_t i = 0;
    while (i < list->size())
    {
        vector<int> cur;
        for (;cur.size() < 2; ++i)
        {
            cur.push_back((*list)[i]);
        }
        if (cur[0] <= cur[1])
        {
            for (; (*list)[i] <= cur[cur.size() - 1] ; ++i)
            {
                cur.push_back((*list)[i]);
            }
        }
        else
        {
            for (; (*list)[i] > cur[cur.size() - 1]; ++i)
            {
                cur.push_back((*list)[i]);
            }
            for (size_t j = 0; j < cur.size() / 2; ++j)
            {
                swap(cur[j], cur[cur.size() - 1 - j]);
            }
        }
        for (; i < size_t(minrun); ++i)
        {
            cur.push_back((*list)[i]);
        }
        result.push_back(cur);
    }
    return result;
}

void Timsort::insertionSort(vector<int> *run)
{
    for (size_t j = 1; j < (*run).size(); ++j)
    {
        int value = (*run)[j];
        for (size_t i = j - 1; i >= 0  && (*run)[i] > value; --i)
        {
            (*run)[i+1] = (*run)[i];
            (*run)[i] = value;
        }
    }
}

void Timsort::mergeSort(vector<vector<int>> *runs)
{

}

#endif // TIMSORT_H
