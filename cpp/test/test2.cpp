#include <iostream>
#include <vector>

using namespace std;

class Matrix
{
private:
    vector<vector<int> > a, start_matrix;
    int n, m;
public:

    int get_ans()
    {
        return 
    }
    Matrix(vector<vector<int> > a_, int u1, int u2) : n(a_.size()), m (a_[0].size())
    {
        n = a_.size();
        m = a_[0].size();
        a.assign(n, 0);
        start_matrix.assign(n, 0);
        for (int i = 0; i < n; i++)
        {
            a[i].assign(m, 0);
            start_matrix[i].assign(m, 0);
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                a[i][j] = a_[i][j];
        start_matrix[0][1] = 1;
        start_matrix[1][0] = u2;
        start_matrix[1][1] = u1;
    }

    Matrix pow(int t)
    {
        Matrix m(vector<vector<int> > (n, vector<int> (m, 0)));
        if (t == 1)
            return start_matrix;
        if (t % 2 == 0)
            m = pow(t / 2) * pow(t / 2);
        else 
            m = pow(t - 1) * start_matrix;
        return m;
    }

    Matrix operator*(Matrix t)
    {
        Matrix M(vector<vector<int> > (m, vector<int> (n, 0)));
        
        for (int i = 0; i < t.m; i++)
            for (int j = 0; j < t.n; j++)
            {
                for (int k = 0; k < t.n; k++)
                    M.a[i][j] += a[i][k] * t.a[k][j];
            }
        return M;
    }

    Matrix operator*(vector<vector<int> > t)
    {
        Matrix M(vector<vector<int> > (m, vector<int> (n, 0)));
        
        for (int i = 0; i < t[0].size(); i++)
            for (int j = 0; j < t.size(); j++)
            {
                for (int k = 0; k < t.size(); k++)
                    M.a[i][j] += a[i][k] * t.a[k][j];
            }
        return M;
    }
};
int main(int argc, char const *argv[])
{
    int a, b, m, A, B;
    cout << "Input a and b :";
    cin >> a >> b;
    cout << "Input A and B :";
    cin >> a >> b;
    cout << "Input m :";
    cin >> m;
    vector<vector<int> > arr(2, vector<int> (2, 0));
    Matrix mm = new Matrix(arr, A, B);
    mm.pow(m);
    cout << mm.get_ans();
    return 0;
}
