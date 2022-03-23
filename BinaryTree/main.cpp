#include<iostream>
using namespace std;

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;	//корень дерева (указатель на корневой элемент)
	// Element* Root; можно так
public:
	Element* getRoot()const
	{
		return this->Root;
	}
	Tree() : Root(nullptr)
	{
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			insert(*it, Root);
		}
	}
	Tree(const Tree& other) : Tree()
	{
		copy(other.Root);
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Tree()
	{
		clear();
		cout << "TDestructor:\t" << this << endl;
	}

	void insert(int Data)
	{
		insert(Data, this->Root);
	}

	int minValue()const
	{
		return minValue(Root);
	}

	int maxValue()const
	{
		return maxValue(Root);
	}

	int count()const
	{
		return count(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}

	void clear()
	{
		clear(Root);
	}

	void erase(int Data)
	{
		erase(Data, Root);
	}

	void print()const
	{
		print(Root);
		cout << endl;
	}

private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

	int minValue(Element* Root)const
	{
		if (Root == nullptr)return int();
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		//return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		return Root->pLeft ? minValue(Root->pLeft) : Root->Data;
	}

	int maxValue(Element* Root)const
	{
		if (Root == nullptr)return int();
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
		//return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
		return !Root->pRight ? Root->Data : maxValue(Root->pRight);
	}

	int count(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return 1 + count(Root->pLeft) + count(Root->pRight);*/
		return Root == nullptr ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}

	int sum(Element* Root)const
	{
		if (Root == nullptr)return 0;
		//else return sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}

	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}

	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}

	void copy(Element* Root)
	{
		if (Root == nullptr)return;
		insert(Root->Data, this->Root);
		copy(Root->pLeft);
		copy(Root->pRight);
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
};

class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Ввeдите размер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	/*int value;
	cout << "\nВведите добовляемое значение: "; cin >> value;
	tree.insert(value, tree.getRoot());
	tree.print(tree.getRoot());*/
	cout << "\nМинимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << tree.count() << endl;
	cout << "Сумма элементов дерева: " << tree.sum() << endl;
	cout << "Среднее арифмитическое элементов дерева: " << tree.avg() << endl;
	int value;
	cout << "Введите значение удаляемого элемента дерева: "; cin >> value;
	tree.erase(value);
	tree.print();
	cout << "\n----------------------------------------------------------------\n";
	Tree tree2 = { 50, 25, 75, 16, 32, 64, 80 };
	tree2.print();
	Tree tree3 = tree2;
	tree3.print();

	UniqueTree unique_tree;
	for (int i = 0; i < n; i++)
	{
		unique_tree.insert(rand() % 100);
	}
	unique_tree.print();
	/*int value;
	cout << "\nВведите добовляемое значение: "; cin >> value;
	tree.insert(value, tree.getRoot());
	tree.print(tree.getRoot());*/
	cout << "\nМинимальное значение в дереве: " << unique_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << unique_tree.maxValue() << endl;
	cout << "Количество элементов в дереве: " << unique_tree.count() << endl;
}