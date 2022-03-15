#include<iostream>
using namespace std;

void elevator(int floor)
{
	if (floor == 0)
	{
		cout << "�� � �������" << endl;
		return;
	}
	cout << "�� �� " << floor << " �����" << endl;
	elevator(floor - 1);
	cout << "�� �� " << floor << " �����" << endl;
}

int factorial(int n)
{
	if (n < 0)
	{
		cout << "Error!!!" << endl;
		return 0;
	}
	if (n == 0) return 1;
	else return n * factorial(n - 1);
}
double power(double a, int n)
{
	if (n < 0) return power(1 / a, -n);
	if (n == 0) return 1;
	else return a * power(a, n - 1);
}

//#define ELEVATOR
//#define FACTORIAL
#define POWER

void main()
{
	setlocale(LC_ALL, "");
#ifdef ELEVATOR
	int floor;
	cout << "������� ����� �����:"; cin >> floor;
	elevator(floor);
#endif // ELEVATOR

#ifdef FACTORIAL
	int n;
	cout << "������� �����:"; cin >> n;
	cout << "��������� ����� " << n << "!" << " = " << factorial(n) << endl;
#endif // FACTORIAL

#ifdef POWER
	double a;
	int n;
	cout << "������� �����:"; cin >> a;
	cout << "������� �������:"; cin >> n;
	cout << "����� " << a << " ^ " << n << " = " << power(a, n) << endl;
#endif // POWER

}