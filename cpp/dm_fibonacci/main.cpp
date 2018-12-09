//
//  main.cpp
//  dm_fibonacci
//
//  Created by Сергей Петров on 08/12/2018.
//  Copyright © 2018 SergioPetrovx. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

class MatrixException : exception
{
private:
    string message;
public:
    
    MatrixException(string message_) : message(message_) {}
    
    string what()
    {
        return message;
    }
    
};

template<class T>
class Matrix
{
private:
    int n, m, p;
    vector<vector<T> > elems;
public:
    
    Matrix(int n_, int m_, int p_)
    {
        n = n_;
        m = m_;
        p = p_;
        elems.assign(n, vector<T> (m, 0));
    }
    
    Matrix(vector<T> elems_, int n_, int m_, int p_)
    {
        if (elems_.size() != n_ * m_)
            throw MatrixException("Input vector is incorrect!");
        n = n_;
        m = m_;
        p = p_;
        elems.assign(n, vector<T> (m, 0));
        for (int i = 0; i < elems_.size(); i++)
            //elems[i / n][i % m] = elems_[i];
            elems[i / m][i % m] = elems_[i];
    }
    
    Matrix operator*(Matrix obj)
    {
        if (m != obj.n)
            throw MatrixException("Dimension is not equal!");
        Matrix matrix(n, obj.m, p);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < obj.m; j++)
                for (int k = 0; k < obj.n; k++)
                    matrix.elems[i][j] = (matrix.elems[i][j] + (elems[i][k] * obj.elems[k][j])) % p;
        return matrix;
    }
    
    Matrix pow(int power)
    {
        if (power == 1)
            return *this;
        else if (power % 2)
            return *this * pow(power - 1);
        else
        {
            Matrix u = pow(power / 2);
            return u*u;
        }
    }
    
    int get_first()
    {
        return elems[0][0];
    }
};


int main()
{
    int a, b, A, B, power, p;
    cout << "Input a, b: ";
    cin >> a >> b;
    cout << "Input A, B: ";
    cin >> A >> B;
    cout << "Input power: ";
    cin >> power;
    cout << "Input p: ";
    cin >> p;
    
    Matrix<int> T({0, 1, b, a}, 2, 2, p);
    Matrix<int> X({A, B}, 2, 1, p);
    Matrix<int> ans = T.pow(power-1) * X;
    cout << ans.get_first() << endl;
    return 0;
}
