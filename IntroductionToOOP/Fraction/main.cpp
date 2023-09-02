#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(const Fraction& left, const Fraction& right);

class Fraction
{
	int integer;		//Целая часть
	int numerator;		//Числитель
	int denominator;	//Знаменатель
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

	//				Constructors:
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstruct:\t" << this << endl;
	}
	explicit Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "1ArgConstructor:" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//					Operators:
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignment:\t\t" << this << endl;
		return *this;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this*other;
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}

	//					Increment/Decrement:
	Fraction& operator++()
	{
		integer++;
		return *this;
	}
	Fraction operator++(int)
	{
		Fraction old = *this;
		integer++;
		return old;
	}

	//					Type-cast operators:
	explicit operator int()
	{
		return to_proper().integer;
	}
	operator double()
	{
		return integer + (double)numerator / denominator;
	}

	//					Methos:
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		swap(inverted.numerator, inverted.denominator);
		return inverted;
	}
	Fraction& reduce()
	{
		if (numerator == 0)return *this;
		//https://www.webmath.ru/poleznoe/formules_12_7.php
		int more, less, rest;
		if (numerator > denominator)more = numerator, less = denominator;
		else less = numerator, more = denominator;
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more;	//Gratest Common Divisor
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}
	void print()const
	{
		if (integer)cout << integer;
		if (numerator)
		{
			if (integer)cout << "(";
			cout << numerator << "/" << denominator;
			if (integer)cout << ")";
		}
		else if (integer == 0)cout << 0;
		cout << endl;
	}
};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	/*Fraction result;
	result.set_numerator(left.get_numerator()*right.get_numerator());
	result.set_denominator(left.get_denominator()*right.get_denominator());
	result.to_proper();
	return result;*/
	/*Fraction result(left.get_numerator()*right.get_numerator(), left.get_denominator()*right.get_denominator());
	result.to_proper();
	return result;*/
	return Fraction
	(
		left.get_numerator()*right.get_numerator(),
		left.get_denominator()*right.get_denominator()
	).to_proper().reduce();
	//В этом выражении явно вызывается конеструктор, и создается временный безымянный объект.
	//Этот временный безымянный объект сразу же возвращается на место вызова функции.
	//Временные безымянные объекты существуют в пределах одного выражения.
}
Fraction operator/(const Fraction& left, const Fraction& right)
{
	return left * right.inverted();
}

bool operator==(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	/*if (left.get_numerator()*right.get_denominator() == right.get_numerator()*left.get_denominator())
		return true;
	else
		return false;*/
	return left.get_numerator()*right.get_denominator() == right.get_numerator()*left.get_denominator();
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);
}
bool operator>(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return left.get_numerator()*right.get_denominator() > right.get_numerator()*left.get_denominator();
}
bool operator<(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return left.get_numerator()*right.get_denominator() < right.get_numerator()*left.get_denominator();
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	return !(left < right);
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	return !(left > right);
}

std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	else if (obj.get_integer() == 0)os << 0;
	return os;
}

std::istream& operator>>(std::istream& is, Fraction& obj)
{
	/*int integer, numerator, denominator;
	is >> integer >> numerator >> denominator;
	obj.set_integer(integer);
	obj.set_numerator(numerator);
	obj.set_denominator(denominator);*/
	/*
	-----------------------------
	5
	1/2
	5(1/2)
	-----------------------------
	*/
	const int SIZE = 256;
	char sz_buffer[SIZE]{};
	is >> sz_buffer;
	//https://legacy.cplusplus.com/reference/cstring/strtok/
	int number[3] = {};

	char delimiters[] = "()/";
	int n = 0;
	for (char* pch = strtok(sz_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
	{
		number[n++] = std::atoi(pch);	//atoi() - ASCII-string to integer. Преобразует строку в целое число
	}

	switch (n)
	{
	case 1: obj = Fraction(number[0]); break;
	case 2: obj = Fraction(number[0], number[1]); break;
	case 3: obj = Fraction(number[0], number[1], number[2]);
	}

	return is;
}

//#define CONSTRUCTORS_CHECK
//#define ARITHMETICAL_OPERATORS_CHECK
//#define INCREMENT_CHECK

//#define TYPE_CONVERSIONS_BASICS
//#define CONVERSIONS_FROM_OTHER_TO_CLASS
//#define CONVERSIONS_FROM_CLASS_TO_OTHER
#define CONVERSIONS_HOME_WORK

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	Fraction A;		//Default constructor
	A.print();

	Fraction B = 5;//Single-argument constructor
	B.print();

	Fraction C(1, 2);
	C.print();

	Fraction D(2, 3, 4);
	D.print();
#endif // CONSTRUCTORS_CHECK

#ifdef ARITHMETICAL_OPERATORS_CHECK
	Fraction A(2, 3, 4);
	A.print();

	Fraction B(3, 4, 5);
	B.print();

	Fraction C = A * B;
	C.print();

	C = A / B;
	C.print();

	A *= B;
	A.print();

	A /= B;
	A.print();

	C = 5;
	C.reduce();
	C.print();
#endif // ARITHMETICAL_OPERATORS_CHECK

#ifdef INCREMENT_CHECK
	for (double i = .25; i < 10; i++)
	{
		cout << i << "\t";
	}
	cout << endl;

	for (Fraction i(1, 4); i.get_integer() < 10; ++i)
	{
		i.print();
	}
#endif // INCREMENT_CHECK

	//cout << (2 == 3) << endl;
	//cout << (Fraction(1, 2) >= Fraction(5, 10)) << endl;

	/*Fraction A;
	cout << "Введите простую дробь: "; cin >> A;
	cout << A << endl;*/

	//(type)value;	//C-like notation
	//type(value);	//Functional notation

#ifdef TYPE_CONVERSIONS_BASICS
	int a = 2;		//No conversions
	double b = 3;	//Conversion from less to more
	int c = b;		//Conversion from more to less without data loss
	int d = 3.14;	//Conversion from more to less with data loss

	cout << 7 / 2. << endl;
#endif // TYPE_CONVERSIONS_BASICS

	/*
	-------------------------------------------
	1. From other to Class;
		Single-agrument constructor;
		Assignment operator;
	2. From Class to other;
		type-cast operators
	-------------------------------------------
	*/

#ifdef CONVERSIONS_FROM_OTHER_TO_CLASS
	Fraction A = (Fraction)5;		//Conversion from 'int' to 'Fraction'
	cout << A << endl;

	Fraction B;
	B = Fraction(8);
	cout << B << endl;
#endif // CONVERSIONS_FROM_OTHER_TO_CLASS

#ifdef CONVERSIONS_FROM_CLASS_TO_OTHER
	Fraction A(52, 10);
	cout << A << endl;
	int a = (int)A;
	cout << a << endl;

	Fraction B(2, 3, 4);
	cout << B << endl;
	double b = B;
	cout << b << endl;
#endif // CONVERSIONS_FROM_CLASS_TO_OTHER

#ifdef CONVERSIONS_HOME_WORK
	Fraction A = 2.75;
	cout << A << endl;
#endif // CONVERSIONS_HOME_WORK

}

/*
--------------------------------
operator type()
{
	........
	conversion code;
	........
}
--------------------------------
*/