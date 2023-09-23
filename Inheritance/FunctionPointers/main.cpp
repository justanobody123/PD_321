#include<iostream>
using namespace std;

const char* Hello()
{
	return "Hello";
}
int Sum(int a, int b)
{
	return a + b;
}

void main()
{
	setlocale(LC_ALL, "");
	cout << Hello << endl;	//Адрес функции
	const char*(*pHello)() = Hello;
	cout << pHello << endl;	//Адрес той же фукнции, сохраненный в указателе
	cout << pHello() << endl;	//Вызов функции 'Hello()' через указатель 'pHello'

	cout << Sum(2, 3) << endl;
	cout << Sum << endl;
	int(*pSum)(int a, int b) = Sum;
	cout << pSum << endl;
	cout << pSum(2, 3) << endl;
}