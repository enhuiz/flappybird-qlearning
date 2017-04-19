#include <vector>
#include <list>
#include <iostream>
using namespace std;

int main()
{
    list<int> a = {1,
                     2,
                     8,
                     3,
                     4,
                     5,
                     6};

    for (auto x : a)
    {
        a.clear();
        cout << " fuck" << endl;
    }
}