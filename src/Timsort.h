#ifndef TIMSORT_H
#define TIMSORT_H

#include <vector>
#include <iostream>
#include <stack>
#include <algorithm>

class Timsort
{
private:
    int getMinrun(int n);
    void insertionSort(unsigned begin, unsigned size, std::vector<int> *run);
    void merge(std::vector<int> *list, std::pair<size_t, size_t> A, std::pair<size_t, size_t> B);
public:
    void timsort(std::vector<int> *list);

};

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

void Timsort::timsort(std::vector<int> *list)
{
    int minrun = getMinrun(list->size());
    std::stack<std::pair<size_t, size_t>> stack;
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
        stack.push({start, runLength});


        while (stack.size() >= 3)
        {
            std::pair<size_t, size_t> X = stack.top();
            stack.pop();
            std::pair<size_t, size_t> Y = stack.top();
            stack.pop();
            std::pair<size_t, size_t> Z = stack.top();
            stack.pop();

            if (Z.second > Y.second + X.second && Y.second > X.second)
            {
                stack.push(Z);
                stack.push(Y);
                stack.push(X);
                break;
            }
            else
            {
                if (X.second < Z.second)
                {
                    merge(list, Y, X);
                    stack.push(Z);
                    stack.push({std::min(Y.first, X.first), Y.second + X.second});
                }
                else
                {
                    merge(list, Y, Z);
                    stack.push({std::min(Y.first, Z.first), Y.second + Z.second});
                    stack.push(X);
                }
            }

        }
        while (stack.size() >= 2)
        {
            std::pair<size_t, size_t> X = stack.top();
            stack.pop();
            std::pair<size_t, size_t> Y = stack.top();
            stack.pop();
            merge(list, X, Y);
            stack.push({std::min(X.first, Y.first), X.second+Y.second});
        }
    }
}

void Timsort::insertionSort(unsigned begin, unsigned size, std::vector<int> *run)
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

void Timsort::merge(std::vector<int> *list, std::pair<size_t, size_t> A, std::pair<size_t, size_t> B) {
    // Определяем начальные и конечные индексы для обоих диапазонов

    if (A.first > B.first)
        std::swap(A, B);

    const size_t startA = A.first;
    const size_t endA = A.first + A.second;
    const size_t startB = B.first;
    const size_t endB = B.first + B.second;

    // Создаем временный вектор для хранения объединенных результатов

    std::vector<int> temporary;

    // Заполняем временный вектор

    for (size_t i = startA; i < endA; ++i)
    {
        temporary.push_back((*list)[i]);
    }
    size_t indexA = 0;  // Индекс для временного вектора
    size_t indexB = startB;  // Индекс для второго диапазона
    size_t i = startA;  // Индекс для записи в оригинальный список

    // Слияние двух диапазонов
    size_t gallopCounterA = 0;
    size_t gallopCounterB = 0;
    const size_t gallopStart = 7;
    while (indexA < temporary.size() && indexB < endB)
    {
        if (temporary[indexA] <= (*list)[indexB])
        {
            (*list)[i++] = temporary[indexA++];
            gallopCounterA++;

            if (gallopCounterA == gallopStart)
            {
                size_t step = 1;
                while (indexA + step < temporary.size() && temporary[indexA + step] <= (*list)[indexB])
                {
                    step *= 2;
                }
                // Проверка на пересечение границ
                const size_t maxGallop = std::min(step / 2, temporary.size() - indexA);
                for (size_t iter = 0; iter < maxGallop; ++iter)
                {
                    (*list)[i++] = temporary[indexA++];
                }
                gallopCounterA = 0;
            }
        }
        else
        {
            (*list)[i++] = (*list)[indexB++];
            gallopCounterB++;

            if (gallopCounterB == gallopStart)
            {
                size_t step = 1;
                while (indexB + step < endB && (*list)[indexB + step] < temporary[indexA])
                {
                    step *= 2;
                }
                // Проверка на пересечение границ
                const size_t maxGallop = std::min(step, endB - indexB);
                for (size_t iter = 0; iter < maxGallop; ++iter)
                {
                    (*list)[i++] = (*list)[indexB++];
                }
                gallopCounterB = 0;
            }
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

#endif // TIMSORT_H
