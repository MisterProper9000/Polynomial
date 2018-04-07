#include "Polynomial.h"
#include <cstdarg>

#define UPPER_BOUND 10E100

Polynomial::Polynomial()
{
	_degree = 0;
	_koef = new double[1];
	_koef[0] = 0;
}

Polynomial::Polynomial(int degree, ...)
{
	double tmp;

	va_list argList;
	va_start(argList, degree);

	tmp = va_arg(argList, double);

	while (tmp == 0 && degree >= 0)
	{
		degree--;
		tmp = va_arg(argList, double);
	}

	_koef = new double[degree + 2];
	_degree = degree;
	_koef[0] = tmp;

	for (int i = 1; i < degree + 2; i++)
	{
		_koef[i] = va_arg(argList, double);
	}

	va_end(argList);
}

Polynomial::Polynomial(int degree, double* a)
{
	int dDegree = 0;

	while (dDegree <= degree && a[dDegree] == 0)
		dDegree++;

	_koef = new double[degree - dDegree + 1];
	_koef[0] = a[dDegree];
	_degree = degree - dDegree;

	for (int i = 1; i < degree -dDegree + 1; i++)
	{
		_koef[i] = a[i + dDegree];
	}
}

Polynomial::Polynomial(double num)
{
	_degree = 0;
	_koef = new double[1];
	_koef[0] = num;
}

Polynomial::Polynomial(const Polynomial& obj)
{
	_degree = obj._degree;
	_koef = new double[_degree + 1];
	for (int i = 0; i <= _degree; i++)
		_koef[i] = obj._koef[i];
}

Polynomial::Polynomial(Polynomial&& obj) : _degree(obj._degree), _koef(obj._koef)
{
	obj._degree = -1;
	obj._koef = nullptr;
}

Polynomial& Polynomial::operator=(Polynomial&& other)
{
	if (this != &other)
	{
		delete[] _koef;

		_koef = other._koef;
		_degree = other._degree;

		other._koef = nullptr;
		other._degree = -1;
	}
	return *this;
}

Polynomial::~Polynomial()
{
	//cout << "~P";
	delete[] _koef;
}

Polynomial Polynomial::operator+(const Polynomial& other)
{
	Polynomial poly;
	if (other._degree >= _degree)
	{
		poly = other;
		for (int i = 0; i <= _degree ; i++)
			poly._koef[other._degree - i] += _koef[_degree - i];
	}
	else
	{
		poly = *this;
		for (int i = 0; i <= other._degree; i++)
			poly._koef[_degree - i] += _koef[other._degree - i];
	}
	poly._normalization();
	return poly;
}

Polynomial Polynomial::operator-(const Polynomial& other)
{
	Polynomial poly;
	if (other._degree >= _degree)
	{
		poly = other;
		for (int i = 0; i <= _degree; i++)
			poly._koef[other._degree - i] -= _koef[_degree - i];
	}
	else
	{
		poly = *this;
		for (int i = 0; i <= other._degree; i++)
			poly._koef[_degree - i] -= _koef[other._degree - i];
	}
	poly._normalization();
	return poly;
}

bool Polynomial::operator==(const Polynomial& other)
{
	if (this == &other)
		return true;

	bool isEqual = (_degree == other._degree);

	if (isEqual)
		for (int i = 0; i <= _degree; i++)
		{
			if (_koef[i] != other._koef[i])
				return false;
		}

	return true;
}

Polynomial& Polynomial::operator=(const Polynomial& other)
{
	if (&other == this)
		return *this;
	else
	{
		delete[] _koef;
		_degree = other._degree;
		_koef = new double[_degree + 1];
		for (int i = 0; i <= _degree; i++)
			_koef[i] = other._koef[i];
	}
	return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& other)
{
	if (other._degree > _degree)
	{
		double* d = new double[other._degree + 1];
		memset(d, 0, (other._degree + 1) * sizeof(double));

		for (int i = _degree + 1; i <= other._degree; i++)
			d[other._degree-i] += other._koef[other._degree-i];

		for (int i = 0; i <= _degree; i++)
			d[other._degree - i] += (other._koef[other._degree - i] + _koef[_degree - i]);

		delete[] _koef;
		_degree = other._degree;
		_koef = new double[other._degree + 1];

		for (int i = 0; i <= other._degree; i++)
			_koef[i] = d[i];

		delete[] d;
	}
	else
	{
		for (int i = 0; i <= other._degree; i++)
			_koef[_degree - i] += other._koef[other._degree - i];
	}
	this->_normalization();
	return *this;
}

Polynomial& Polynomial::operator-=(const Polynomial& other)
{
	if (other._degree > _degree)
	{
		double* d = new double[other._degree + 1];
		memset(d, 0, (other._degree + 1) * sizeof(double));

		for (int i = _degree + 1; i <= other._degree; i++)
			d[other._degree - i] -= other._koef[other._degree - i];

		for (int i = 0; i <= _degree; i++)
			d[other._degree - i] -= (other._koef[other._degree - i] + _koef[_degree - i]);

		delete[] _koef;
		_degree = other._degree;
		_koef = new double[other._degree + 1];

		for (int i = 0; i <= other._degree; i++)
			_koef[i] = d[i];

		delete[] d;
	}
	else
	{
		for (int i = 0; i <= other._degree; i++)
			_koef[_degree - i] -= other._koef[other._degree - i];
	}
	this->_normalization();
	return *this;
}

ostream& operator<<(ostream& out, const Polynomial& pol)
{
	for (int i = 0; i <= pol._degree; i++)
	{
		if (pol._koef[i] != 0)
		{
			if (i != 0)
				out << " + ";
			out << pol._koef[i] << "x^" << pol._degree - i;
		}
	}
	return out << "\n";
}

istream& operator >> (istream &in, Polynomial& pol)
{
	cout << "Enter polynomial's power: ";
	cin >> pol._degree;
	cout << endl;

	delete[] pol._koef;
	pol._koef = new double[pol._degree + 1];

	for (int i = 0; i <= pol._degree; i++)
	{
		cout << "Enter a coefficient for the " << pol._degree - i << " degree: ";
		cin >> pol._koef[i];
		cout << endl;
	}

	return in;
}

//WARNING: при кратных корнях метод не сходится (но не циклится)
void Polynomial::findRealRoot(vector<double>* roots)
{
	double* st1 = new double[_degree + 1];
	double* st2 = new double[_degree + 1];
	double* st3 = new double[_degree + 1];

	double* vault = new double[_degree + 1];
	for (int i = 0; i <= _degree; i++)
		vault[i] = _koef[i];

	roots->clear();

	bool isNotEnoughAccurate = true;
	int iterator = 0;

	for (int i = 0; i <= _degree; i++)
	{
		st1[i] = 0;
		st2[i] = 0;
		st3[i] = 0;
		roots->push_back(0.);
	}

	do {
		for (int i = 0; i <= _degree; i++)
			st1[i] = vault[i] * vault[i];

		for (int i = 1; i < _degree; i++)
			st2[i] = -2 * vault[i - 1] * vault[i + 1];

		for (int i = 2; i < _degree - 1; i++)
			st3[i] = 2 * vault[i - 2] * vault[i + 2];

		for (int i = 0; i <= _degree; i++)
		{
			vault[i] = st1[i] + st2[i] + st3[i];
			if (vault[i] > UPPER_BOUND)
				isNotEnoughAccurate = false;
		}

		iterator = iterator++;
		if (iterator == INT_MAX)
			break;
	} while (isNotEnoughAccurate);

	int tmp = 1;
	double p = 1. / (tmp << (iterator));

	for (int i = 0; i < _degree; i++)
	{
		double c = (double)vault[i + 1] / vault[i];
		(*roots)[i] = pow((double)vault[i + 1] / vault[i], p);
	}


	for (int i = 0; i < _degree; i++)
		if (abs(at((*roots)[i])) > abs(at(-(*roots)[i])))
			(*roots)[i] = -(*roots)[i];

	for (int i = 0; i < _degree; i++)
		for (int j = i + 1; j < _degree; j++)
			if (abs((*roots)[i]) - abs((*roots)[j]) < 1./ 100.)
				(*roots)[i] = -(*roots)[i];

	for (int i = 0; i < _degree; i++)
		cout << "roots = " << (*roots)[i] << endl;

	delete[] st1;
	delete[] st2;
	delete[] st3;
	delete[] vault;
}

Polynomial Polynomial::operator*(const Polynomial& other)
{
	Polynomial tmp(_degree + other._degree);
	memset(tmp._koef, 0, (tmp._degree + 1) * sizeof(double));

	for (int i = 0; i <= _degree; i++)
		for (int j = 0; j <= other._degree; j++)
			tmp._koef[i + j] += _koef[i] * other._koef[j];

	tmp._normalization();
	return tmp;
}

Polynomial operator*(const Polynomial& left, const Polynomial& right)
{
	Polynomial tmp(left._degree + right._degree);
	memset(tmp._koef, 0, (tmp._degree + 1) * sizeof(double));

	for (int i = 0; i <= left._degree; i++)
		for (int j = 0; j <= right._degree; j++)
			tmp._koef[i + j] += left._koef[i] * right._koef[j];

	tmp._normalization();
	return tmp;
}

double Polynomial::at(double x)
{
	double val = 0;
	for (int i = 0; i <= _degree; i++)
	{
		val += _koef[i] * pow(x, _degree - i);
	}
	return val;
}


Polynomial operator+(const Polynomial& left, const Polynomial & right)
{
	Polynomial poly;
	if (left._degree >= right._degree)
	{
		poly = left;
		for (int i = 0; i <= right._degree; i++)
			poly._koef[left._degree - i] += right._koef[right._degree - i];
	}
	else
	{
		poly = right;
		for (int i = 0; i <= left._degree; i++)
			poly._koef[right._degree - i] += left._koef[left._degree - i];
	}
	poly._normalization();
	return poly;
}

Polynomial operator-(const Polynomial& left, const Polynomial & right)
{
	Polynomial poly;
	if (left._degree >= right._degree)
	{
		poly = left;
		for (int i = 0; i <= right._degree; i++)
			poly._koef[left._degree - i] -= right._koef[right._degree - i];
	}
	else
	{
		poly = right;
		for (int i = 0; i <= left._degree; i++)
			poly._koef[right._degree - i] -= right._koef[left._degree - i];
	}
	poly._normalization();
	return poly;
}

void Polynomial::_normalization()
{
	int zeroSlice = 0;
	while (_koef[zeroSlice] == 0)
		zeroSlice++;

	if (zeroSlice-1 == _degree)
	{
		_degree = 0;
		delete[] _koef;
		_koef = new double[1];
		_koef[0] = 0;
	}
	else if (zeroSlice > 0)
	{
		double* tmp = new double[_degree - zeroSlice + 1];

		for (int i = zeroSlice; i <= _degree; i++)
			tmp[i - zeroSlice] = _koef[i];

		delete[] _koef;
		_koef = tmp;
	}
}
