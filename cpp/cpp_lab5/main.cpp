#include <iostream>
#include <math.h>
using namespace std;

class Shape
{
protected:
    double eps;
public:
    Shape() : eps(0.0001) {}
    virtual bool isInside(int, int) = 0;
    virtual ~Shape() {}
};


class Circle : public Shape
{
private:
    int x, y, radius;
public:
    Circle(int x_, int y_, int radius_) : x(x_), y(y_), radius(radius_) {}
    
    bool isInside(int x_, int y_)
    {
        return sqrt((x_ - x)*(x_ - x) + (y_ - y)*(y_ - y)) - radius <= eps ;
    }
};

class Square : public Shape
{
private:
    int left_bottom_x, left_bottom_y, right_top_x, right_top_y;
public:
    Square(int x1, int y1, int x2, int y2) : left_bottom_x(x1), left_bottom_y(y1), right_top_x(x2), right_top_y(y2) {}
    
    bool isInside(int x_, int y_)
    {
        return (left_bottom_x <= x_ && x_ <= right_top_x) && (left_bottom_y <= y_ && y_ <= right_top_y);
    }
};

int main() {
    const int N = 50;
    Shape *ar[N];
    for (int i = 0; i < N; i++) {
        if (i % 2) {
            ar[i] = new Circle(i * 2, i, 40);
            // x, y, radius
        } else {
            ar[i] = new Square(i, i, (i + 1) * (i + 2), i + 10);
            // x, y of left bottom point, then x, y of right top point
        }
    }
    long long int ans = 0;
    
    for (int i = 0; i < N; i++) {
            ans = ans * 2 + (int)ar[i]->isInside(i * 2 - 1, i * 2 - 1);
        // count boundary points as inside points
        if (dynamic_cast<Circle*>(ar[i]))
            cout << "Circle!" << endl;
    }
    if (ans != 562766701483008) {
        cout << "testing fail" << endl;
    } else {
        cout << "all test passed" << endl;
    }
    for (int i = 0; i < N; i++) {
        delete ar[i];
    }
    cin.get();
    return 0;
}
