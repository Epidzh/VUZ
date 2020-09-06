// kursach.cpp : Этот файл содержит функцию "main". �-десь начинается и заканчивается выполнение программы.

// #include "pch.h"
// #include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

class Drob
{
public:
    int ch;
    int zn;

    Drob(int c, int z)
    {
        ch = c;
        zn = z;
    }
    Drob()
    {
    }

    void Vvod()
    {
        int znach, chisl;
        cout << "Vvedite chislitel: ";
        cin >> chisl;
        cout << "Vvedite znamenatel: ";
        cin >> znach;
        ch = chisl;
        zn = znach;
    }

    bool operator<(Drob b) // перегрузка оператора <
    {
        double d1 = (double)ch / (double)zn;
        double d2 = (double)b.ch / (double)b.zn;
        if (d1 < d2)
            return true;
        else
            return false;
    }

    bool operator>(Drob b) // перегрузка оператора >
    {
        double d1 = (double)ch / (double)zn;
        double d2 = (double)b.ch / (double)b.zn;
        if (d1 > d2)
            return true;
        else
            return false;
    }

    Drob operator+(Drob b) // перегрузка оператора +
    {
        int zn1 = zn * b.zn;
        int ch1 = ch * b.zn + b.ch * zn;

        int nod = NOD(ch1, zn1);

        Drob c(ch1 / nod, zn1 / nod);
        return c;
    }

    Drob operator-(Drob b) // перегрузка оператора -
    {
        int zn1 = zn * b.zn;
        int ch1 = ch * b.zn - b.ch * zn;
        int nod = NOD(ch1, zn1);

        Drob c(ch1 / nod, zn1 / nod);

        return c;
    }

    Drob operator*(Drob b) // перегрузка оператора *
    {
        int zn1 = zn * b.zn;
        int ch1 = ch * b.ch;
        int nod = NOD(ch1, zn1);

        Drob c(ch1 / nod, zn1 / nod);
        return c;
    }

    Drob operator/(Drob b) // перегрузка оператора /
    {
        int zn1 = zn * b.ch;
        int ch1 = ch * b.zn;
        int nod = NOD(ch1, zn1);

        Drob c(ch1 / nod, zn1 / nod);
        return c;
    }

    bool operator==(Drob b) // перегрузка оператора ==
    {
        if (zn == b.zn && ch == b.ch)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool operator!=(Drob b) // перегрузка оператора !=
    {
        if (zn != b.zn || ch != b.ch)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void operator=(Drob a) // перегрузка оператора = (с другой дробью)
    {
        this->ch = a.ch;
        this->zn = a.zn;
    }
    bool operator!() // перегрузка унарного оператора !
    {
        if (ch == 0)
            return true;
        else
            return false;
    }
    void operator=(int a) // перегрузка оператора = (с целым числом)
    {
        this->ch = 0;
        this->zn = 0;
    }

    int NOD(int x, int y) // функция поиска наименьшего целого делителя
    {
        if (y == 0)
            return x;
        return NOD(y, x % y);
    }

    void sokr() // функция смены знака у числителя и знаменателя
    {

        if (ch >= 0 && zn <= 0)
        {
            ch = -ch;
            zn = -zn;
        }
    }
    friend ostream &operator<<(ostream &os, const Drob &d); // перегрузка оператора <<, реализация которой будет в дружественной функции (необходимо для работы с стандартным потоком вывода)
};

ostream &operator<<(ostream &os, Drob &d) // перегрузка оператора <<
{

    d.sokr();
    return os << d.ch << "/" << d.zn << endl;
}

template <typename T>
class matrix
{
    int N;
    T **mat;
public:
    matrix(int n) // конструктор класса
    {
        N = n;
        mat = new T*[N];
        for (int i = 0; i < N; ++i)
            mat[i] = new T[N + 1];
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N + 1; j++)
            {
                T p;
                p.Vvod();
                mat[i][j] = p;
            }
        }
        gaussianElimination(mat);
    }

    ~matrix() {
        for (int i = 0; i < N; i++)
            delete mat[i];
        delete mat;
    }

    void gaussianElimination(T **mat) //функция решения методом Гаусса
    {
        int singular_flag = forwardElim(mat);
        if (singular_flag != -1)
        {
            if (mat[singular_flag][N].ch)
                cout << "Neposledovatelnaya sistema!";
            else
                cout << "Mojet imet neskolko resheniy!";
            return;
        }
        backSub(mat);
    }

    void swap_row(T **mat, int i, int j) // метод перестановки 2-х строк
    {

        for (int k = 0; k <= N; k++)
        {
            T temp = mat[i][k];
            mat[i][k] = mat[j][k];
            mat[j][k] = temp;
        }
    }

    int forwardElim(T **mat) // прямой ход метода Гаусса
    {
        for (int k = 0; k < N; k++)
        {
            int i_max = k;
            T v_max = mat[i_max][k];

            for (int i = k + 1; i < N; i++)
                if (mat[i][k] > v_max)
                    v_max = mat[i][k], i_max = i;

            if (!mat[k][i_max])
                return k;
            if (i_max != k)
                swap_row(mat, k, i_max);
            for (int i = k + 1; i < N; i++)
            {
                T f = mat[i][k] / mat[k][k];
                for (int j = k + 1; j <= N; j++)
                    mat[i][j] = mat[i][j] - mat[k][j] * f;

                mat[i][k] = 0;
            }
        }
        return -1;
    }

    void backSub(T **mat) // обратный ход метода Гаусса
    {
        T *x = new T[N];
        for (int i = N - 1; i >= 0; i--)
        {
            x[i] = mat[i][N];
            for (int j = i + 1; j < N; j++)
            {
                x[i] = x[i] - mat[i][j] * x[j];
            }
            x[i] = x[i] / mat[i][i];
        }

        cout << "\nResheniye uravneniya:\n";
        for (int i = 0; i < N; i++)
        {
            cout << x[i] << endl;
        }
    }

    matrix& operator+(matrix& other) {
        if (this->N != other.N)
            return this;
        matrix m = new matrix(this->N);
        for (int i = 0; i < this->N; i++){
            for (int j = 0; j < this->N; j++)
                m.mat[i][j] = this->mat[i][j] + other.mat[i][j];
        }
        return m;
    }

    matrix& operator-(matrix& other) {
        if (this->N != other.N)
            return this;
        matrix m = new matrix(this->N);
        for (int i = 0; i < this->N; i++){
            for (int j = 0; j < this->N; j++)
                m.mat[i][j] = this->mat[i][j] - other.mat[i][j];
        }
        return m;
    }

    matrix& operator*(matrix& other) {
        if (this->N != other.N)
            return this;
        matrix m = new matrix(this->N);
        for (int i = 0; i < this->N; i++){
            for (int j = 0; j < this->N; j++) {
                T sm = mat[i][0] * other.mat[0][j];
                for (int k = 1; k < this->N; k++) {
                    sm += mat[i][k] * other.mat[k][j];
                }
                m.mat[i][j] = sm;
            }
        }
        return m;
    }
};

int main()
{
    int n;
    cout << "Vvedite kol-vo uravneniy: ";
    cin >> n;
    matrix<Drob> a(3);
    system("pause");
    return 0;
}
