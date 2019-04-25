#include <iosream>

using namespace std;


void transform(vector<int> &a, vector<int> &c, int p)
{
    
}


void min_pow(vector<int> &a, vector<int> &b, int p, int pow)
{
    int u = 2;
    vector<int> c = b;
    while (u <= pow)
    {
        c = mult_poly(c, b);
        transform(a, c, p);
        for (int i = 0; i < c.size(); i++)
            if ((i != c.size) && (c[i] != 0))
                break;
            else if (i == c.size() && c[i] == 1)
                cout << c;
        u++;
    }
}


void find_and_print(vector<int> &a, vector<int> &b, int p, int pow, int v = 0)
{
    for (int i = 0; i < p; i++)
    {
        b[v] = i;
        if (v + 1 != a.size())
            find_and_print(a, b, p, pow, v + 1)
        min_pow(a, b, p, pow);
    }
}


int main()
{
    int n, p, pow;
    cout << "Input polynom size: ";
    cin >> n;
    cout << "Input mod: ";
    cin >> p;
    vector<int> a(n+1, 0);
    cout << "Input arr: "
    for (int i = a.size() - 1; i >= 0; i--)
        cout << a[i];
    cout << "Input pow";
    cin >> pow;

    vector<int> b(a.size(), 0);
    find_and_print(a, b, p, pow);
    return 0;
}