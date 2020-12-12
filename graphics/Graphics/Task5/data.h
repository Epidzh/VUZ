#ifndef data_h
#define data_h


struct Point {
    double x, y, z;
    Point(double, double, double);
};

struct Section {
    Point P1, P2;
    Section (Point, Point);
};

#endif /* data_h */
