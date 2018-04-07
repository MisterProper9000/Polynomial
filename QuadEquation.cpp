#include "QuadEquation.h"
#define eps 0.0000000001

double QuadEquation::_discriminant()
{
	return _koef[1] * _koef[1] - 4. * _koef[0] * _koef[2];
}

void QuadEquation::findRealRoot(vector<double>* roots)
{
	roots->clear();

	switch (_degree)
	{
	case 0:
		if (_koef[0] == 0)
			roots->push_back(0);
		break;
	case 1:
		roots->push_back(_koef[1] / _koef[0] == 0 ? 0 : -_koef[1] / _koef[0]);
		break;
	default:
		double d = _discriminant();
		if (d > 0)
		{
			roots->push_back((-_koef[1] - sqrt(d)) / (2.*_koef[0])); 
			roots->push_back((-_koef[1] + sqrt(d)) / (2.*_koef[0]));
		}
		else if (d == 0)
			roots->push_back(-_koef[1] / (2.*_koef[0]));
		break;
	}
}

QuadEquation QuadEquation::operator*(const QuadEquation& other)
{
	if (other._degree + _degree <= 2)
	{
		Polynomial pOther = static_cast<const Polynomial&>(other);
		Polynomial pThis = static_cast<const Polynomial&>(*this);
		Polynomial pRes = pThis * pOther;

		QuadEquation qRes = static_cast<QuadEquation&>(pRes);

		return qRes;
	}
	else
	{
		QuadEquation n;
		return n;
	}
}

QuadEquation operator*(const QuadEquation& left, const QuadEquation& right)
{
	if (left._degree + right._degree <= 2)
	{
		Polynomial pLeft = static_cast<const Polynomial&>(left);
		Polynomial pRight = static_cast<const Polynomial&>(right);
		Polynomial pRes = pLeft * pRight;

		QuadEquation qRes = static_cast<QuadEquation&>(pRes);

		return qRes;
	}
	else
	{
		QuadEquation n;
		return n;
	}
}

ostream& operator<<(ostream& out, const QuadEquation& pol)
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
	return out << " = 0\n";
}

istream& operator >> (istream &in, QuadEquation& pol)
{
	pol._degree = 3;
	while (pol._degree > 2)
	{
		cout << "Enter polynomial's power: ";
		cin >> pol._degree;
		cout << endl;
		if (pol._degree > 2)
			cout << "QUADRATIC equation is too difficult for you" << endl;
	}

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

QuadEquation operator+(const QuadEquation& left, const QuadEquation & right)
{
	Polynomial pLeft = static_cast<const Polynomial&>(left);
	Polynomial pRight = static_cast<const Polynomial&>(right);
	Polynomial pRes = pLeft + pRight;

	QuadEquation qRes = static_cast<QuadEquation&>(pRes);

	return qRes;
}

QuadEquation operator-(const QuadEquation& left, const QuadEquation & right)
{
	Polynomial pLeft = static_cast<const Polynomial&>(left);
	Polynomial pRight = static_cast<const Polynomial&>(right);
	Polynomial pRes = pLeft - pRight;

	QuadEquation qRes = static_cast<QuadEquation&>(pRes);

	return qRes;
}

QuadEquation& QuadEquation::operator+=(const QuadEquation& other)
{
	Polynomial pOther = static_cast<const Polynomial&>(other);
	Polynomial pThis = static_cast<const Polynomial&>(*this);
	pThis += pOther;
	QuadEquation qThis = static_cast<QuadEquation&>(pThis);
	*this = qThis;
	return *this;
}

QuadEquation& QuadEquation::operator-=(const QuadEquation& other)
{
	Polynomial pOther = static_cast<const Polynomial&>(other);
	Polynomial pThis = static_cast<const Polynomial&>(*this);
	pThis -= pOther;
	QuadEquation qThis = static_cast<QuadEquation&>(pThis);
	*this = qThis;
	return *this;
}

bool QuadEquation::operator==(const QuadEquation& other)
{
	Polynomial pOther = static_cast<const Polynomial&>(other);
	Polynomial pThis = static_cast<const Polynomial&>(*this);
	return pThis == pOther;
}