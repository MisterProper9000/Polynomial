#pragma once
#include "Polynomial.h"

class QuadEquation : public Polynomial
{
private:
	double _discriminant();

public:
	QuadEquation() {};
	QuadEquation(int degree):Polynomial(degree > 2? 2 :degree) {};
	QuadEquation(int degree, double* a) :Polynomial(degree > 2 ? 2 : degree, a) {};
	QuadEquation(const double& a, const double& b, const double& c) : Polynomial(2, a, b, c) {};
	QuadEquation(double num) :Polynomial(num) {};
	~QuadEquation() {/* cout << "~Q"; */};
	void findRealRoot(vector<double>* roots);

	QuadEquation& operator+=(const QuadEquation& other);
	QuadEquation& operator-=(const QuadEquation& other);
	bool operator==(const QuadEquation& other);

	friend QuadEquation operator+(const QuadEquation& left, const QuadEquation & right);
	friend QuadEquation operator-(const QuadEquation& left, const QuadEquation & right);
	friend ostream& operator<<(ostream& out, const QuadEquation& pol);
	friend istream& operator>>(istream& in, QuadEquation& pol);

	void whoAmI() const { printf_s("I'm not just a polynomial, I'm a quadratic equation!\n"); };

	QuadEquation operator*(const QuadEquation& other);
	friend QuadEquation operator*(const QuadEquation& left, const QuadEquation& right);
};
