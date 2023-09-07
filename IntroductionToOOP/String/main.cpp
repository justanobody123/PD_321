#include"String.h"

//#define CONSTRUCTORS_CHECK
//#define OPERATOR_PLUS_CHECK

void main()
{
	setlocale(LC_ALL, "");
	//Deep copy
	//---------------------------------------

	//Shallow copy
	//Move constructor
	//Move assignment

#ifdef CONSTRUCTORS_CHECK
	String str(5);
	str.print();

	//cout << typeid("Hello").name() << endl;
	String str1 = "Hello";
	str1 = str1;
	cout << str1 << endl;

	String str2 = str1;		//Copy constructor
	cout << str2 << endl;

	String str3;
	str3 = str2;			//Copy assignment
	cout << str3 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATOR_PLUS_CHECK
	String str1 = "Hello";
	String str2 = "World";
	/*String str3 = "str3";
	try
	{
		str3 = str1 + str2;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	cout << str3 << endl;*/
	cout << delimiter << endl;
	//String str3 = str1 + str2;	//Move constructor
	String str3;
	str3 = str1 + str2;
	cout << delimiter << endl;
	cout << str3 << endl;
#endif // OPERATOR_PLUS_CHECK


	String str1;	//Default constructor
	str1.print();

	String str2(5);	//Single-Argument Constructor
	str2.print();

	String str3 = "Hello";	//Single-Argument constructor
	str3.print();

	String str4();	//Здесь не создается никакой объект, здесь объявляется функция 'str4()',
					//которая ничего не принимает, и возвращает объект класса 'String';
	//str4.print();

	String str5{};	//Явно вызывается конструктор по умолчанию
	str5.print();

	String str6("World");
	str6.print();

	String str7{ "Compile" };
	str7.print();

	String str8 = str3;	//Copy constructor
	str8.print();

	String str9;
	str9 = str6;
	str9.print();

}

/*
--------------------------------------------------
				Move-методы:
r-value reference to Class:	Class&&
--------------------------------------------------
*/