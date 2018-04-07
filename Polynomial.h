#pragma once
#include <iostream>  
#include <algorithm>
#include <vector>

using namespace std;

class Polynomial
{
protected:
	int _degree;
	double *_koef;                //_koef[0] = a_{degree}, _koef[1] = a_{degree-1}, ...,  _koef[degree-1] = a_0

	void _normalization();

public:
	Polynomial(); 
	Polynomial(int degree, ...);        //перечисление коэффициентов
	Polynomial(int degree, double* a);  //массив
	Polynomial(double num);             //полином-чиселко
	Polynomial(const Polynomial& other);
	Polynomial(Polynomial&& obj);
	virtual ~Polynomial();

	Polynomial operator+(const Polynomial & other);
	Polynomial operator-(const Polynomial& other);
	friend Polynomial operator+(const Polynomial& left, const Polynomial & right);
	friend Polynomial operator-(const Polynomial& left, const Polynomial & right);

	bool operator==(const Polynomial& other);

	Polynomial& operator=(Polynomial&& obj);
	Polynomial& operator=(const Polynomial& other);
	Polynomial& operator+=(const Polynomial& other);
	Polynomial& operator-=(const Polynomial& other);
	
	friend ostream& operator<<(ostream& out, const Polynomial& pol);
	friend istream& operator>>(istream& in, Polynomial& pol);

	virtual void whoAmI() const { printf_s("I'm a polynomial!\n"); };
	virtual void findRealRoot(vector<double>* roots);                                     //Метод Лобачевского — Греффе (возвращает сначала вещ. корни, потом, если есть комплексные -- мусор
	virtual Polynomial operator*(const Polynomial& other);
	friend Polynomial operator*(const Polynomial& left, const Polynomial& right);

	double at(double x);
};
