//
//  main.cpp
//  derive
//
//  Created by Сергей Петров on 27/09/2019.
//  Copyright © 2019 SergioPetrovx. All rights reserved.
//

#include <iostream>

using namespace std;

double f(double x)
{
    double eps = 0.000001;
    if (x + 0.2 < eps)
        return 1.7722;
    if (x < eps)
        return 1.5708;
    if (x - 0.2 < eps)
        return 1.3694;
    if (x - 0.4 < eps)
        return 1.1593;
    if (x - 0.6 < eps)
        return 0.9273;
    return 0;
}

double derive1_center(double (*f)(double), double point, double step)
{
    return (f(point + step + step) - f(point)) / (2*step);
}

double derive1_left(double (*f)(double), double point, double step)
{
    return (f(point + step) - f(point)) / step;
}

double derive1_right(double (*f)(double), double point, double step)
{
    return (f(point + step + step) - f(point + step)) / step;
}

double derive2(double (*f)(double), double point, double step)
{
    return (f(point + step + step) - 2*f(point + step) + f(point)) / (step * step);
}

int main(int argc, const char * argv[]) {
    
    double x = 0.2;
    double h = 0.2;
    double (*t)(double) = f;
    cout << "First (center) = " << derive1_center(t, x, h) << endl;
    cout << "First (left) = " << derive1_left(t, x, h) << endl;
    cout << "First (right) = " << derive1_right(t, x, h) << endl;
    cout << "Second = " << derive2(t, x, h) << endl;
    return 0;
}
