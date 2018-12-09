#include <iostream>
#include <string>
#include "matrix.h"

void passed() {
    static int n=0;
    std::cout << "Test " << ++n << " passed" << std::endl;
}

void testMatrix() {
    
    Matrix a(2, 3), b(2, 3), c(3, 3);
    
    c = 2 * c; //Multiply all elements by number.
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            a[j][i] = i + j + i*j * 2;
            b[j][i] = i - j * 7;
        }
    }
    
    try {
        c = c * (a*b);
        std::cout << "Error. (a*b) should throw MatrixExeption exception." << std::endl;
    }
    catch (MatrixExeption e) {
        if (e.what() != std::string("Can't multiply matrices with dimensions A[n][q] * B[p][m], where q!=p")) {
            std::cout << "Wrong exeption message" << std::endl;
        }
        else {
            passed();
        }
    }
    
    a = a.T(); //transposition
    c = c * (a*b).T();
    
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sum += c[i][j]*(i+1)*(j+1);
        }
    }
    
    if (sum != -1912) {
        std::cout << "Error in calculating c = c * (a*b).T();" << std::endl;
    }
    else {
        passed();
    }
    
    if (c != c.T().T()) {
        std::cout << "A twice-transposed matrix is not equal to the matrix itself." << std::endl;
        return;
    }
    else {
        passed();
    }
    Matrix d(2, 2);
    
    try {
        d = c + d;
        std::cout << "Error. c + d should throw MatrixExeption exception." << std::endl;
    }
    catch (MatrixExeption e) {
        if (e.what() != std::string("Can't sum matrices with different dimensions")) {
            std::cout << "Wrong exeption message" << std::endl;
        }
        else {
            passed();
        }
    }
    
    try {
        d = c - d;
        std::cout << "Error. c - d should throw MatrixExeption exception." << std::endl;
    }
    catch (MatrixExeption e) {
        if (e.what() != std::string("Can't subtract matrices with different dimensions")) {
            std::cout << "Wrong exeption message" << std::endl;
        }
        else {
            passed();
        }
    }
}

int main() {
    
    testMatrix();
    
    std::cin.get();
    
    return 0;
}
