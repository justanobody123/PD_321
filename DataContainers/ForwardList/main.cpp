﻿#include<iostream>
#include<ctime>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

#define DEBUG
#define delimeter "\n----------------------------------------------\n"

class Element
{
	int Data;
	Element* pNext;
	static int count;	//объявление статической переменной
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
		cout << delimeter;
#endif // DEBUG
	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
	}
	friend class ForwardList;
	friend class Iterator;
	friend class Stack;
};

int Element::count = 0;	//определение статической переменной

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
#ifdef DEBUG
		cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
	}
	Iterator(const Iterator& other)
	{
		this->Temp = other.Temp;
#ifdef DEBUG
		cout << "ItCopyConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Iterator()
	{
#ifdef DEBUG
		cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
	}

	Iterator& operator++()	//Prefix increment
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	int operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	//Forward - односвязный, однонаправленный
protected:
	Element* Head;
	unsigned int size;
public:
	//type name ( parameters )
	const Iterator begin()const
	{
		return Head;
	}
	const Iterator end()const
	{
		return nullptr;
	}
	ForwardList()
	{
		//Конструктор по умолчанию создает пустой список.
		this->Head = nullptr;	//Если список пуст, его Голова указывает на 0.
		this->size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const initializer_list<int>& il) :ForwardList()
	{
		//initializer_list - это контейнер.
		//Контейнер - это объект, который организует хранение других объектов в памяти.
		//Как и у любого другого контейнера, у initializer_list есть методы begin() и end()
		//begin() - возвращает итератор на начало контейнера;
		//end()   - возвращает итератор на конец контейнера;
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		//this - этот список
		//other - тот список
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;	//Из конструктора копирования повторно используем код CopyAssignment
		cout << "LCopyConstructor:" << this  << "<-" << &other << endl;
	}
	ForwardList(ForwardList&& other):ForwardList()
	{
		/*this->Head = other.Head;
		this->size = other.size;

		other.Head = nullptr;
		other.size = 0;*/
		*this = std::move(other);
		cout << "MoveConstructor:" << this << "<-" << &other << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//				Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);
		reverse();
		cout << "CopyAssignemnt:\t" << this << "<-" << &other << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();

		this->Head = other.Head;
		this->size = 0;

		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << " <- " << &other << endl;
		return *this;
	}

	//				Adding elements:
	void push_front(int Data)
	{
		/*//1) Создаем элемент для добавляемого значения:
		Element* New = new Element(Data);
		//2) Пристыковываем элемент к списку:
		New->pNext = Head;
		//3) Теперь новый элемент является начальным элементом списка:
		Head = New;*/

		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);

		//1) Создаем новый элемент:
		//Element* New = new Element(Data);

		//2) Доходим до конца списка:
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		// Сейчас 'Temp' указывает на последний элемент.

		//3) Добавляем новый элемент в конец списка:
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index == 0)return push_front(Data);
		//1) Создаем новый элемент:
		//Element* New = new Element(Data);
		//2) Доходим до нужного элемента:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (Temp->pNext == nullptr)return push_back(Data);
			Temp = Temp->pNext;
		}
		//3) Вставляем новый элемент по указанному индексу:
		/*New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	//					Removing elements:
	int pop_front()
	{
		Element* Erased = Head;	//1) Запоминаем адрес удаляемого элемента
		int Data = Erased->Data;
		Head = Head->pNext;	//2) Исключаем удаляемый элемент из списка
		delete Erased;	//3) Удаляем элемент из памяти
		size--;
		return Data;
	}
	void pop_back()
	{
		//1) Доходим до предпоследнего элемента:
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//2) Удаляем последний элемент из памяти:
		delete Temp->pNext;
		//3) Обнуляем указательна последний элемент:
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int index)
	{
		if (index == 0)return pop_front();

		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			if (Temp == nullptr)return;
			Temp = Temp->pNext;
		}
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
		size--;
	}

	//					Methods:
	void reverse()
	{
		ForwardList reverse;
		while (Head)
		{
			reverse.push_front(Head->Data);
			this->pop_front();
		}
		this->Head = reverse.Head;
		reverse.Head = nullptr;
	}
	void print()const
	{
		/*Element* Temp = Head;	//Temp - это итератор.
		//Итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных.

		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//Переход на следующий элемент
		}*/
		for(Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << this->size << endl;	//к статическим полям принято обращаться через имя класса и оператор разрешения видимости
		cout << "Общее количество элементов списка: " << Element::count << endl;	//к статическим полям принято обращаться через имя класса и оператор разрешения видимости
		//cout << "Количество элементов списка: " << Head->count << endl;
	}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList result = left;
	for (Iterator it = right.begin(); it != right.end(); ++it)
		result.push_back(*it);
	return result;
}

class Stack : protected ForwardList
{
public:
	void push(int data)
	{
		push_front(data);
	}
	int pop()
	{
		return pop_front();
	}
	int peek()
	{
		return Head->Data;
	}
	int height() const
	{
		return ForwardList::size;
	}
	void print()
	{
		ForwardList::print();
	}
	
};
//#define BASE_CHECK
//#define INSERT_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST
//#define OPERATOR_PLUS_CHECK
#define FORWARD_LIST_PREFORMANCE_TEST


void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	/*list.push_front(123);
	list.print();
	list.pop_front();
	list.pop_back();*/
	list.print();

#ifdef INSERT_CHECK
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
#endif // INSERT_CHECK

#endif // BASE_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	// https://legacy.cplusplus.com/doc/tutorial/control/#:~:text=equal%20to%2050.-,Range%2Dbased%20for%20loop,-The%20for%2Dloop
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3, 5, 8, 13, 21 };
	list.print();

	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (Iterator it = list.begin(); it != list.end(); it++)	//Postfix increment
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST

#ifdef OPERATOR_PLUS_CHECK
	ForwardList list1 = { 3, 5, 8, 13, 21 };
	list1 = list1;
	for (int i : list1)cout << i << tab; cout << endl;

	//ForwardList list2 = list1;	//Copy constructor
	ForwardList list2 = { 34, 55, 89 };
	//list2 = list1;
	for (int i : list2)cout << i << tab; cout << endl;

	//ForwardList list3 = list1 + list2;
	ForwardList list3;
	list3 = list1 + list2;		//Move assignment
	for (int i : list3)cout << i << tab; cout << endl;

	list1.print();
	list2.print();
#endif // OPERATOR_PLUS_CHECK

#if PERFORMANCE_TEST
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	clock_t start = clock();
	for (int i = 0; i < n; i++)
	{
		int value = rand() % 100;
		//cout << value << tab;
		list.push_front(value);
	}
	cout << endl;
	//for (int i : list)cout << i << tab; cout << endl;
	clock_t end = clock();
	cout << "Data loaded for " << double(end - start) / CLOCKS_PER_SEC << endl;
	cout << "Copying list...." << endl;
	start = clock();
	ForwardList list2 = list;
	//for (int i : list2)cout << i << tab; cout << endl;
	end = clock();
	cout << "List copied for " << double(end - start) / CLOCKS_PER_SEC << endl;
#endif // PERFORMANCE_TEST
	Stack stack;
	int n;
	cout << "Введите размер списка: ";
	cin >> n;
	for (size_t i = 0; i < n; i++)
	{
		stack.push(rand() % 100);
	}
	//stack.print();
	/*for (size_t i = 0; i < stack.height(); i++)
	{
		cout << stack.pop();
	}*/
	cout << delimeter;
	while (stack.height())
	{
		cout << stack.pop() << "\t";
		cout << delimeter;
	}
}