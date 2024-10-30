#include "application.h"
#include "Timsort.h"
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int Application::exec()
{
    Timsort ts;
    vector<int> list = {7, 18, 21, 34, 1, 6, 7, 14, 5, 23, 41, 88, 0, 2, 33, 49, 54, 61, 76, 82, 9, 19, 25, 31, 38, 47, 52, 58, 65, 70, 74, 80, 86, 92, 97, 4, 10, 17, 22, 29, 36, 43, 50, 33, 49, 54, 61, 76, 82, 9, 19, 25, 31, 38, 47, 52, 58, 65, 70, 74, 80, 86, 92, 97, 4, 10, 17, 22, 29, 36, 43, 50, 57, 64, 71, 78, 83, 90, 5, 28, 37, 42, 56, 73, 89, 12, 34, 67, 5, 23, 41, 88, 0, 2, 33, 49, 54, 61, 76, 82, 9, 19, 25, 31, 38, 47, 52, 58, 65, 70, 74, 80, 86, 92, 97, 4, 10, 17, 22, 29, 36, 43, 50, 57, 64, 71, 78, 83, 90};

    ts.timsort(&list);

    for (size_t i = 0; i < list.size(); ++i)
    {
        cout << list[i] << " ";
    }
    cout << endl;
    cout << endl;

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
