#include "application.h"
#include "Timsort.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int Application::exec()
{
    srand(time(0));
    Timsort ts;

    while (true)
    {
        std::vector<int> list;
        srand(time(0));

        std::cout << "enter arr length or 0 to exit" << "\n" << "> ";
        int size = getInt();
        if (size < 0)
        {
            std::cout << "wrong arr length" << "\n\n";
        }
        else if (size == 0)
        {
            break;
        }
        else
        {
            for (int i = 0; i < size; ++i)
            {
                int randInt = rand() % 99 + 1;
                list.push_back(randInt);
            }
            std::cout << "unsorted: \n";
            for (size_t i = 0; i < list.size(); ++i)
            {
                std::cout << list[i] << " ";
            }
            std::cout << "\n\n";

            ts.timsort(&list);
            std::cout << "sorted: \n";
            for (size_t i = 0; i < list.size(); ++i)
            {
                std::cout << list[i] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    return 0;
}

int Application::getInt()
{
    int a;
      std::cin >> a;
      while (std::cin.fail())
      {
        std::cin.clear();
        std::cin.ignore();
        std::cin >> a;
      }
      return a;
}
