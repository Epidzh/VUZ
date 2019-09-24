#include <iostream>
#include "test.cpp"

using namespace std;

int main()
{
    int a = 0;
    for (int i = 1; i < 5; i++)
        for (int j = 1; j < 5; j++)
            for (int k = 1; k < 5; k++)
                for (int t = 1; t < 5; t++)
                    if (i != j && i != k && i != t && j != k && j != t && k != t)
                    {
                        if (i == 1 ^ j == 2 ^ k == 3 ^ t == 4)
                        {
                            cout << i << j << k << t << endl;
                            a++;
                        }
                    }
    cout << a;
    return 0;    
}