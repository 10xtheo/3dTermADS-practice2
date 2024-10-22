#include "application.h"
#include "Timsort.h"
#include <iostream>
#include <vector>
using namespace std;

int Application::exec()
{
    Timsort ts;
    vector<int> list =
    {5, 4, 3, 2, 8, 7, 9, };
    vector<vector<int>> slices = ts.slicer(&list);
    for (size_t i = 0; i < slices.size(); ++i)
    {
        for (size_t j = 0; j < (slices[i]).size(); ++j)
        {
            cout << slices[i][j] << "x";
        }
        cout << "a";
    }

    return 0;
}

int Application::startMenu()
{
   int ch = getInt();
   return ch;
}

int Application::getInt()
{
    int a;
      cin >> a;
      while (cin.fail())
      {
        cin.clear();
        cin.ignore();
        cin >> a;
      }
      return a;
}
