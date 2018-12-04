#include <cmath>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <time.h>
#include <vector>

#include "list.h"

using namespace std;

class INT {
    int b;
public:
    static int counter, cCounter;
    explicit INT(int a) : b(a) {}
    explicit operator int() { return b; }
    bool operator<(const INT &a) {
        counter++;
        return b < a.b;
    }
    bool operator<=(const INT &a) {
        counter++;
        return b <= a.b;
    }
    INT(const INT &a) {
        cCounter++;
        b=a.b;
    }
};
int INT::counter, INT::cCounter;
void test(vector<INT> v) {
    List<INT> l;
    for (size_t i = 0; i < v.size(); i++) {
        l.push_back(v[i]);
    }
    INT::counter = 0, INT::cCounter = 0;
    l.sort();
    int count = INT::counter, count2 = INT::cCounter;
    bool cheker = false;
    for (size_t i = 0; i < v.size() - 1; i++) {
        if (!(l[i] <= l[int(i + 1)])) {
            cheker = true;
            break;
        }
    }
    if (cheker) {
        throw std::logic_error("List not sorted!");
    }
    double nlogn = v.size() * log(v.size()) / log(4. / 3.);
    if (count <= nlogn) {
        cout << "this is less or queal O(n*log(n))" << endl;
    } else {
        cout << "this is more than O(n*log(n))" << endl;
    }
    if(count2 > 0){
        cout<<"coping is not allowed!"<<endl;
    }
}

int main() {
    int n = 5, m = 1000;
    srand(time(0));
    vector<INT> v1, v2, v3, v4;
    for (int i = 0; i < n; i++) {
        v1.push_back(INT(rand() % m));
        v2.push_back(INT(i));
        v3.push_back(INT(n - i));
        v4.push_back(INT(10));
    }
    
    cout << "Testing random shuffle... " << endl;
    test(v1);
    cout << "Testing sorted... " << endl;
    test(v2);
    cout << "Testing reverse sorted... " << endl;
    test(v3);
    cout << "Testing all equal list... " << endl;
    test(v4);
    cin.get();
    return 0;
}
