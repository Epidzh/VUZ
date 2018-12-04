//
//  matrix.h
//  cpp_solutions
//
//  Created by e1nfalt on 18/10/2018.
//  Copyright © 2018 SergioPetrovx. All rights reserved.
//

#ifndef _MATRIX_H_
#define _MATRIX_H_

class MatrixExeption
{
private:
    char* message;
public:
    
    MatrixExeption(char* str) : message(str) {};
    
    char* what()
    {
        return message;
    }
};

class Matrix
{
private:
    
    int cols, rows;
    int** elems;
    
public:
    Matrix(int cols_num, int rows_num) : rows(rows_num), cols(cols_num), elems(new )
    {
        
        rows = rows_num;
        cols = cols_num;
        elems = new int*[cols];
        for (int i = 0; i < cols; i++)
        {
            elems[i] = new int[rows];
            for (int j = 0; j < rows; j++)
                elems[i][j] = i == j;
        }
    }
    
    Matrix T();
    Matrix operator*(Matrix);
    friend Matrix operator*(int, Matrix);
    Matrix operator+(Matrix);
    Matrix operator-(Matrix);
    bool operator!=(Matrix);
    int* operator[](int);
};

#endif