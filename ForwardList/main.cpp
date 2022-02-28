#include<iostream>
using namespace std;

class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Адресс следующего элемента
	static unsigned int count;
public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}

	friend class ForwardList;
};

unsigned int Element::count = 0; //Инициализация статической переменной

class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		Head = nullptr; //Если Голова указывает на 0, то список пуст, т.е. не содежрит элементов
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other) : ForwardList()
	{
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "LCopyConstructor: " << this << endl;
	}
	ForwardList(ForwardList&& other)
	{
		this->Head = other.Head;
		other.Head = nullptr;
		cout << "LMoveConstructor: " << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	//						Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "LCopyAssignment: " << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		while (Head)pop_front();
		this->Head = other.Head;
		other.Head = nullptr;
		cout << "LMoveAssignment: " << this << endl;
	}
	//						Adding elements
	void push_front(int Data)
	{
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
	}
	void insert(int index, int Data)
	{
		if (index > Head->count)
		{
			cout << "Error: Выход за пределы списка" << endl;
			return;
		}
		if (index == 0)
		{
			push_front(Data);
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}

	//					Removing elements:
	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}
	void erase(int index)
	{
		if (index > Head->count)
		{
			cout << "Error: Выход за пределы списка" << endl;
			return;
		}
		if (index == 0)
		{
			pop_front();
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
	}
	void uniqe()
	{
		Element* Temp = Head;
		while (Temp->pNext == Temp->pNext)Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
	
	}

	//					Methods:
	void print()const
	{
		Element* Temp = Head;//Temp - это итератор
		while (Temp)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Количество элементов списка: " << Head->count << endl;
	}
	
};

void main()
{
	setlocale(LC_ALL, "");
	cout << "--------------------------------------------------------------------\n";
	int n;
	cout << "Ввидите размер списка:  "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	cout << "\n--------------------------------------------------------------------\n";
	int index;
	int value;
	cout << "Введите индекс добавленного элемента: "; cin >> index;
	cout << "Введите значение добавленного элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	cout << "\n--------------------------------------------------------------------\n";
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	cout << "\n--------------------------------------------------------------------\n";
	ForwardList list2;
	list2 = list;
	list2.print();
	cout << "\n--------------------------------------------------------------------\n";
}