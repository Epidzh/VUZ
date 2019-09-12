#include <iostream>
#include <math.h>

static const double EPS = 0.000001;
static const double ln_10 = log(10);
static const double ARG = M_PI / 2;

template<class T>
T m_exp(T x, int n)
{
    if (n == 1)
        return x;
    else if (n % 2 == 0)
    {
        T temp = m_exp(x, n / 2);
        return temp * temp;
    }
    else
    {
        return x * m_exp(x, n - 1);
    }
}

double m_sin(double x, double EPS = 0.000001)
{
    if (x > ARG)
        x = (x > 0) ? x - (x / M_PI) : x + (x / M_PI);
    double ans = 0;
    int n = 1;
    double elem = x;
    while (elem < EPS)
    {
        ans += elem;
        n += 2;
        elem *= -(m_exp(x, n) / ((n - 1) * n));
    }
    return ans;
}

double m_cos(double x, double EPS = 0.000001)
{
    if (fabs(x) > ARG)
        x = (x > 0) ? x - (x / M_PI) : x + (x / M_PI);
    double ans = 0;
    int n = 0;
    double elem = 1;
    while (elem < EPS)
    {
        ans += elem;
        n += 2;
        elem *= -(m_exp(x, n) / ((n - 1) * n));
    }
    return ans;
}

double m_lg(double x, double EPS = 0.000001)
{
    
}

int main()
{
    
    double arg;
    std::cout << "Input sin arg: ";
    std::cin >> arg;
    std::cout << "sin = " << sin(arg) << "; m_sin=" << m_sin(arg) << std::endl;
    
    std::cout << "Input cos arg: ";
    std::cin >> arg;
    std::cout << "cos = " << cos(arg) << "; m_cos=" << m_cos(arg) << std::endl;
    
    std::cout << "Input lg arg: ";
    std::cin >> arg;
    std::cout << "lg = " << log10(arg) << "; m_lg=" << m_lg(arg) << std::endl;
    
    return 0;
}
