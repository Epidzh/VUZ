#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

class Complex {
  private:
	double re, im;
  public:
	Complex(double re_ = 0, double im_ = 0) : re(re_), im(im_){};
	double real() { return re; }
	double imag() { return im; }
	double abs() { return sqrt(re * re + im * im); }
	friend Complex operator+(Complex left, Complex right) {
		return Complex(left.re + right.re, left.im + right.im);
	}
	friend Complex operator-(Complex left, Complex right) {
		return Complex(left.re - right.re, left.im - right.im);
	}
	friend Complex operator*(Complex left, Complex right) {
		return Complex(left.re * right.re - left.im * right.im,
					   left.im * right.re + left.re * right.im);
	}
} I(0, 1);

void testComplex() {
	Complex a, b, c;

	a = 1 - 2 * I;
	b = a * I;
	c = a * b * 17.7 + a * 3.14;

	if (abs(c.real() - 73.94) > 0.00001) {
		cout << "Error in counting real part of c = a*b*17.7 - a*3.14.\n"
				"Result must be 73.94 but result is "
			 << c.real() << endl;
	} else {
		cout << "test 1 passed." << endl;
	}

	if (abs(c.imag() + 59.38) > 0.00001) {
		cout << "Error in counting imag part of c = a*b*17.7 - a*3.14.\n"
				"Result must be -59.38 but result is "
			 << c.imag() << endl;
	} else {
		cout << "test 2 passed." << endl;
	}

	double lenght = c.abs();
	if (abs(lenght - 94.832) > 0.00001) {
		cout << "Error in counting c.abs()\n"
				"Result must be 94.832 but result is "
			 << lenght << endl;
	} else {
		cout << "test 3 passed." << endl;
	}
}

int main() {
	testComplex();

	cin.get();

	return 0;
}

