#include<iostream>
using namespace std;

class String
{
	int size;	//размер строки в Байтах
	char* str;	//адрес строки в динамической памяти
public:
	const char* get_str()const
	{
		return str;
	}
	//				Constructors:
	explicit String(int size = 80)
	{
		this->size = size;
		this->str = new char[size] {};
		cout << "DefaultConstruct:" << this << endl;
	}
	String(const char* str)
	{
		this->size = strlen(str) + 1;
		this->str = new char[size] {};
		for (int i = 0; str[i]; i++)this->str[i] = str[i];
		cout << "Constructor:\t" << this << endl;
	}
	String(const String& other)
	{
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyConstructor:" << this << endl;
	}
	~String()
	{
		delete[] str;
		cout << "Destructor:\t" << this << endl;
	}

	//						Operators:
	String& operator=(const String& other)
	{
		if (this == &other)return *this;
		delete[] this->str;
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	//						Methods:
	void print()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};
std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

//#define CONSTRUCTORS_CHECK
#define OPERATOR_PLUS_CHECK

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
	String str3 = str1 + str2;
	cout << str3 << endl;
#endif // OPERATOR_PLUS_CHECK

}