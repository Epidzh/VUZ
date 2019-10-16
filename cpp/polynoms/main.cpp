//
//  main.cpp
//  polynoms
//
//  Created by Сергей Петров on 06/10/2019.
//  Copyright © 2019 SergioPetrovx. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>

using namespace std;

static const int N = 4;

double lagrange(double x, double *args, double *values, int n)
{
    double sum = 0;
    
    for (int i = 0; i < n; i++)
    {
        double P = 1.0;

        for (int j = 0; j < n; j++)
            if (j != i)
                P *= (x - args[j]) / (args[i] - args[j]);

        sum += P * values[i];
    }
    return sum;
}

double func(double x)
{
    return x * x * exp(x);
}

void display(double x, double *args, double *values)
{
}

int main(int argc, const char * argv[]) {
    
    double points[] = {-1.2, -0.7, -0.2, 0.3};
    double values[N];
    transform(&points[0], &points[N], values, &func);
    
    double x = -0.5;
    
    
    display(x, points, values);
    return 0;
}
