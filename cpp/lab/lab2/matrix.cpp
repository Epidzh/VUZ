//
//  matrix.h
//  cpp_solutions
//
//  Created by e1nfalt on 18/10/2018.
//  Copyright © 2018 SergioPetrovx. All rights reserved.
//

#include "matrix.h"

Matrix Matrix::T()
{
    
    Matrix M(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            M.elems[i][j] = elems[j][i];
    return M;
}

Matrix Matrix::operator*(Matrix M2)
{
    if (rows != M2.cols)
        throw MatrixExeption((char*)"Can't multiply matrices with dimensions A[n][q] * B[p][m], where q!=p");
    
    Matrix M(cols, M2.rows);
    
    for (int i = 0; i < cols; i++)
        for (int j = 0; j < M2.rows; j++)
        {
            M.elems[i][j] = 0;
            for (int k = 0; k < M2.cols; k++)
                M.elems[i][j] += elems[i][k] * M2.elems[k][j];
        }
    return M;
}

Matrix operator*(int left, Matrix right)
{

    Matrix M(right.rows, right.cols);
    for (int i = 0; i < right.cols; i++)
    {

        for (int j = 0; j < right.rows; j++)
            M.elems[i][j] = left * right.elems[j][i];
    }
    return M;
}

int* Matrix::operator[](int index)
{
    return elems[index];
}

Matrix Matrix::operator+(Matrix M2)
{
    if ((rows == M2.rows) && (cols == M2.cols))
    {
        Matrix M(cols, M2.rows);
        for (int i = 0; i < cols; i++)
            for (int j = 0; j < rows; j++)
                M.elems[i][j] = elems[i][j] + M2.elems[i][j];
        return M;
    }
    else throw MatrixExeption((char*)"Can't sum matrices with different dimensions");
}

Matrix Matrix::operator-(Matrix M2)
{
    if ((rows == M2.rows) && (cols == M2.cols))
    {
        Matrix M(cols, M2.rows);
        for (int i = 0; i < cols; i++)
            for (int j = 0; j < rows; j++)
                M.elems[i][j] = elems[i][j] - M2.elems[i][j];
        return M;
    }
    else throw MatrixExeption((char*)"Can't subtract matrices with different dimensions");
}

bool Matrix::operator!=(Matrix M2)
{
    if (cols != M2.cols || rows != M2.rows)
        return true;
    
    for (int i = 0; i < cols; i++)
        for (int j = 0; j < rows; j++)
            if (elems[i][j] != M2.elems[i][j])
                return true;
    return false;
}