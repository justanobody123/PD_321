#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n-----------------------------------------------------------------\n"

/////////////////////////////////////////////////////////////////////////////////////////
////////////			ОБЪЯВЛЕНИЕ КЛАССА - CLASS DECLARARTION				/////////////

class String
{
	int size;	//размер строки в Байтах
	char* str;	//адрес строки в динамической памяти
public:
	int get_size()const;
	const char* get_str()const;
	char* get_str();

	//				Constructors:
	explicit String(int size = 80);
	String(const char* str);
	String(const String& other);
	String(String&& other);
	~String();

	//						Operators:
	String& operator=(const String& other);
	String& operator=(String&& other);

	char operator[](int i)const;
	char& operator[](int i);

	//						Methods:
	void print()const;
};
////////////		КОНЕЦ ОБЪЯВЛЕНИЯ КЛАССА - CLASS DECLARARTION END		/////////////
/////////////////////////////////////////////////////////////////////////////////////////

///-----------------------------------------------------------------------------------///

/////////////////////////////////////////////////////////////////////////////////////////
////////////			ОПРЕДЕЛЕНИЕ КЛАССА - CLASS DEFINITION				/////////////

//	:: - Scope operator (оператор разрешения видимости)
int String::get_size()const
{
	return size;
}
const char* String::get_str()const
{
	return str;
}
char* String::get_str()
{
	return str;
}

//				Constructors:
//Ключевое слово 'explicit' можно писать только внутри класса.
String::String(int size) :size(size), str(new char[size] {})
{
	//this->size = size;
	//this->str = new char[size] {};
	cout << "DefaultConstruct:" << this << endl;
}
String::String(const char* str) :String(strlen(str) + 1)
{
	//this->size = strlen(str) + 1;
	//this->str = new char[size] {};
	for (int i = 0; str[i]; i++)this->str[i] = str[i];
	cout << "Constructor:\t" << this << endl;
}
String::String(const String& other) :String(other.str)
{
	//Deep copy
	//this->size = other.size;
	//this->str = new char[size] {};
	//for (int i = 0; i < size; i++)this->str[i] = other.str[i];
	cout << "CopyConstructor:" << this << endl;
}
String::String(String&& other) :size(other.size), str(other.str)
{
	//Shallow copy
	//this->size = other.size;
	//this->str = other.str;
	other.size = 0;
	other.str = nullptr;
	cout << "MoveConstructor:" << this << endl;
}
String::~String()
{
	delete[] str;
	cout << "Destructor:\t" << this << endl;
}

//						Operators:
//type	  name	 (	parameters	)
String& String::operator=(const String& other)
{
	if (this == &other)return *this;
	delete[] this->str;
	this->size = other.size;
	this->str = new char[size] {};
	for (int i = 0; i < size; i++)this->str[i] = other.str[i];
	cout << "CopyAssignment:\t" << this << endl;
	return *this;
}
String& String::operator=(String&& other)
{
	if (this == &other)return *this;
	this->size = other.size;
	this->str = other.str;
	other.size = 0;
	other.str = nullptr;
	cout << "MoveAssignment:\t" << this << endl;
}

char String::operator[](int i)const
{
	return str[i];
}
char& String::operator[](int i)
{
	if (i >= size)throw std::out_of_range("Error:sdflksdjflsjfdlkdsjf");
	return str[i];
}

//						Methods:
void String::print()const
{
	cout << "Size:\t" << size << endl;
	cout << "Str:\t" << str << endl;
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

String operator+(const String& left, const String& right)
{
	String cat(left.get_size() + right.get_size() - 1);
	for (int i = 0; i < left.get_size(); i++)
		cat[i] = left[i];
	//cat.get_str()[i] = left.get_str()[i];
	for (int i = 0; i < right.get_size(); i++)
		cat[left.get_size() - 1 + i] = right[i];
	//cat.get_str()[left.get_size() - 1 + i] = right.get_str()[i];
	return cat;
}

////////////		КОНЕЦ ОПРЕДЕЛЕНИЕ КЛАССА - CLASS DEFINITION	END			/////////////
/////////////////////////////////////////////////////////////////////////////////////////

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