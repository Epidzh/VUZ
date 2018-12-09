//
//  matrix.h
//  cpp_solutions
//
//  Created by e1nfalt on 18/10/2018.
//  Copyright © 2018 SergioPetrovx. All rights reserved.
//

#ifndef matrix_h
#define matrix_h

class MatrixExeption
{
private:
    std::string message;
public:
    
    MatrixExeption(std::string str) : message(str) {};
    
    std::string what()
    {
        return message;
    }
};

class Matrix
{
public:
    
    int cols, rows;
    int** elems;
    
    Matrix(int cols_num, int rows_num)
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
    
    Matrix T()
    {
        
        Matrix M(rows, cols);
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                M.elems[i][j] = elems[j][i];
        return M;
    }
    
    friend Matrix operator*(Matrix M1, Matrix M2)
    {
        if (M1.rows != M2.cols)
            throw MatrixExeption("Can't multiply matrices with dimensions A[n][q] * B[p][m], where q!=p");
        
        Matrix M(M1.cols, M2.rows);
        
        for (int i = 0; i < M1.cols; i++)
            for (int j = 0; j < M2.rows; j++)
            {
                M.elems[i][j] = 0;
                for (int k = 0; k < M2.cols; k++)
                    M.elems[i][j] += M1.elems[i][k] * M2.elems[k][j];
            }
        return M;
    }
    
    friend Matrix operator*(int left, Matrix right)
    {
        
        Matrix M(right.rows, right.cols);
        for (int i = 0; i < right.cols; i++)
        {
            
            for (int j = 0; j < right.rows; j++)
                M.elems[i][j] = left * right.elems[j][i];
        }
        return M;
    }
    
    int* operator[](int index)
    {
        return elems[index];
    }
    
    friend Matrix operator+(Matrix M1, Matrix M2)
    {
        if ((M1.rows == M2.rows) && (M1.cols == M2.cols))
        {
            Matrix M(M1.cols, M2.rows);
            for (int i = 0; i < M1.cols; i++)
                for (int j = 0; j < M1.rows; j++)
                    M.elems[i][j] = M1.elems[i][j] + M2.elems[i][j];
            return M;
        }
        else throw MatrixExeption("Can't sum matrices with different dimensions");
    }
    
    friend Matrix operator-(Matrix M1, Matrix M2)
    {
        if ((M1.rows == M2.rows) && (M1.cols == M2.cols))
        {
            Matrix M(M1.cols, M2.rows);
            for (int i = 0; i < M1.cols; i++)
                for (int j = 0; j < M1.rows; j++)
                    M.elems[i][j] = M1.elems[i][j] - M2.elems[i][j];
            return M;
        }
        else throw MatrixExeption("Can't subtract matrices with different dimensions");
    }
    
    friend bool operator!=(Matrix M1, Matrix M2)
    {
        if (M1.cols != M2.cols || M1.rows != M2.rows)
            return true;
        
        for (int i = 0; i < M1.cols; i++)
            for (int j = 0; j < M1.rows; j++)
                if (M1.elems[i][j] != M2.elems[i][j])
                    return true;
        return false;
    }
    
};

#endif /* matrix_h */
