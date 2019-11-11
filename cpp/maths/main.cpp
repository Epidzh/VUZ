#include <iostream>
#include <math.h>

using namespace std;
static const double ln_10 = log(10);
int num = 0;

double m_sin(double x, double EPS = 0.00000001) {
    double ARG = M_PI;
    if (x > ARG)
        x = (x > 0) ? x - int((x / ARG)) * ARG : x + int((x / ARG)) * ARG;
    double ans = 0;
    int n = 1;
    double elem = x;
    while (fabs(elem) > EPS) {
        ans += elem;
        n += 2;
        elem *= -(x * x / ((n - 1) * n));
    }
    return ans;
}

double m_cos(double x, double EPS = 0.000000001) {
    double ARG = 2 * M_PI;
    if (x > ARG) {
        x = (x > 0) ? x - int((x / ARG)) * ARG : x + int((x / ARG)) * ARG;
    }
    double ans = 0;
    int n = 0;
    double elem = 1;
    while (fabs(elem) > EPS) {
        ans += elem;
        n += 2;
        elem *= -(x * x / ((n - 1) * n));
    }
    return ans;
}

double m_ln(double x, double EPS = 0.0001) {
    x = - 1 + x;
    double ans = 0;
    int n = 1;
    double elem = x;
    int sign = 1;
    while (fabs(elem) > EPS) {
        ans += elem;
        n++;
        sign *= -1;
        elem = sign * pow(x, n) / n;
    }
    num += n;
    return ans;
}

double m_lg(double x, double EPS = 0.0001) {
    if (x <= 0)
        return NAN;
    double ans = 0;
    if (fabs(x) > 1) {
        int n = 2;
        while (fabs(x) / pow(10, n) >= 1 - EPS)
            n += 2;
        x = x / pow(10, n);
        ans += n;
    }
    ans += m_ln(x) / log(10);
    return ans;
}

double m_exp(double x, double EPS = 0.000001) {
    double ans = 0;
    double elem = 1;
    int n = 0;
    while (elem > EPS) {
        ans += elem;
        n++;
        elem *= x / n;
    }
    return ans;
}

int main() {
    
    double arg;
    cout << "Input exp arg: ";
    cin >> arg;
    cout << "exp = " << exp(arg) << "; m_exp = " << m_exp(arg) << endl;

    cout << "Input cos arg: ";
    cin >> arg;
    cout << "cos = " << cos(arg) << "; m_cos = " << m_cos(arg) << endl;
    
    cout << "Input lg arg: ";
    cin >> arg;
    cout << "lg = " << log10(arg) << "; m_lg = " << m_lg(arg) << endl;
    cout << "num = " << num << endl;
    return 0;
}
