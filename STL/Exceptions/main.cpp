#include<iostream>
#include<exception>
using namespace std;

void main()
{
	setlocale(LC_ALL, "");
	/*try
	{
		throw 0;
	}
	catch (int e)
	{
		std::cerr << "Error# " << e << endl;
	}*/
	try
	{
		throw std::exception("throwing exception from main()");
		int a, b;
		cout << "Введите два числа: "; cin >> a >> b;
		cout << a / b << endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	catch (...)
	{
		//Универсальный обработчик, который выполняется, если не подошел ни один другой обработчик.
		//Универсальный обработчик не распознает типы исключений
		std::cerr << "Error: Что-то пошло не так...." << endl;
	}

}