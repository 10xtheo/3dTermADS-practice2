#ifndef TIMSORT_H
#define TIMSORT_H

#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

class Timsort
{
private:
    int getMinrun(int n);
public:
    void timsort(vector<int> *list);
    void insertionSort(unsigned begin, unsigned size, vector<int> *run);
    std::stack<std::pair<size_t, size_t>> slicer(vector<int> *list);
    void merge(vector<int> *list, std::pair<size_t, size_t> A, std::pair<size_t, size_t> B);
    void mergeSort(vector<int> *list, std::stack<std::pair<size_t, size_t>> stack);
    size_t binarySearch(const std::vector<int>& arr, int target, size_t start, size_t end);
};

void Timsort::timsort(vector<int> *list)
{
    stack<pair<size_t, size_t>> stack = slicer(list);
    mergeSort(list, stack);
}

int Timsort::getMinrun(int n)
{
    int r = 0;
    while (n >= 64)
    {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

std::stack<std::pair<size_t, size_t>> Timsort::slicer(vector<int> *list)
{
    int minrun = getMinrun(list->size());
    std::stack<std::pair<size_t, size_t>> result;
    for (size_t i = 0; i < list->size(); i++)
    {
        size_t start = i;
        if ((*list)[i] <= (*list)[i + 1] && i + 1 < list->size())
        {
            for (;(*list)[i] <= (*list)[i + 1] && i + 1 < list->size(); ++i);
        }
        else
        {
            for (;i + 1 < list->size() && (*list)[i] >= (*list)[i + 1]; ++i);
            std::reverse(list->begin() + start, list->begin() + i + 1);
        }
        size_t runLength = i - start + 1;
        for (; runLength < size_t(minrun) && i + 1 < list->size(); ++i, ++runLength);
        insertionSort(start, runLength, list);
        result.push({start, runLength});
    }
    return result;
}

void Timsort::insertionSort(unsigned begin, unsigned size, vector<int> *run)
{
    for (size_t j = begin+1; j < size+begin; ++j)
    {
        int value = (*run)[j];
        for (size_t i = j - 1; i >= begin && (*run)[i] > value; i--)
        {
            (*run)[i+1] = (*run)[i];
            (*run)[i] = value;
        }
    }
}

void Timsort::mergeSort(vector<int> *list, std::stack<std::pair<size_t, size_t>> stack)
{
    while (stack.size() >= 3)
    {
        std::pair<size_t, size_t> X = stack.top();
        stack.pop();

        std::pair<size_t, size_t> Y = stack.top();
        stack.pop();

        std::pair<size_t, size_t> Z = stack.top();
        stack.pop();

        if (!(Z.second > Y.second + X.second) || !(Y.second > X.second))
        {
            std::pair<size_t, size_t> minXZ = (X.second < Z.second) ? X : Z;
            std::pair<size_t, size_t> maxXZ = (X.second > Z.second) ? X : Z;
            merge(list, Y, minXZ);
            stack.push(maxXZ);
            stack.push({std::min(Y.first, minXZ.first), Y.second+minXZ.second});
        }
    }
    if (stack.size() == 2)
    {
        std::pair<size_t, size_t> X = stack.top();
        stack.pop();

        std::pair<size_t, size_t> Y = stack.top();
        stack.pop();

        merge(list, X, Y);
    }
}

void Timsort::merge(vector<int> *list, std::pair<size_t, size_t> A, std::pair<size_t, size_t> B) {
    // Определяем начальные и конечные индексы для обоих диапазонов

    if (A.first > B.first)
        swap(A, B);

    size_t startA = A.first;
    size_t endA = A.first + A.second;
    size_t startB = B.first;
    size_t endB = B.first + B.second;

    // Создаем временный вектор для хранения объединенных результатов

    vector<int> temporary;

    // Заполняем временный вектор

    for (size_t i = startA; i < endA; ++i)
    {
        temporary.push_back((*list)[i]);
    }
    size_t indexA = 0;  // Индекс для временного вектора
    size_t indexB = startB;  // Индекс для второго диапазона
    size_t i = startA;  // Индекс для записи в оригинальный список

    // Слияние двух диапазонов
    while (indexA < temporary.size() && indexB < endB)
    {
        if (temporary[indexA] <= (*list)[indexB])
        {
            (*list)[i++] = temporary[indexA++];
        }
        else
        {
            (*list)[i++] = (*list)[indexB++];
        }
    }

    // Копируем оставшиеся элементы из временного вектора, если они есть
    while (indexA < temporary.size())
    {
        (*list)[i++] = temporary[indexA++];
    }

    // Копируем оставшиеся элементы из второго диапазона, если они есть
    while (indexB < endB)
    {
        (*list)[i++] = (*list)[indexB++];
    }
}

size_t Timsort::binarySearch(const std::vector<int>& arr, int target, size_t start, size_t end)
{
    while (start < end)
    {
        size_t mid = start + (end - start) / 2;
        if (arr[mid] < target)
        {
            start = mid + 1;
        }
        else
        {
            end = mid;
        }
    }
    return start; // Возвращаем позицию для вставки
}

#endif // TIMSORT_H
