#include<iostream>

namespace myNamespace
{
	int cout = 2;
}

int sum(int a, int b)
{
	int suma = a + b;

	return suma;
}

int increment(int a) {

	if (a < 10) {
		std::cout << increment(a + 1) << " ";
	}
	std::cout << std::endl;
	return a;
}

int divide(int a, int b)
{
	if (b == 0)
	{
		return 0;
	}

	return a / b;
}

void switchVariableIfGreater(int a, int b)
{
	if (a > b)
	{
		int aux = a;
		a = b;
		b = aux;
	}
}

void switchVariableIfGreaterUsingReference(int& a, int& b)
{
	if (a > b)
	{
		int aux = a;
		a = b;
		b = aux;
	}
}

int main()
{
	myNamespace::cout++;

	std::cout << "Salutare " << myNamespace::cout << std::endl;

	int a = 1;
	int b = 0;
	int suma = sum(a, b);
	int dev = divide(a, b);

	std::cout << "Suma este " << suma << std::endl;
	std::cout << "Devide este " << dev << std::endl;
	increment(a);

	switchVariableIfGreater(a, b);

	std::cout << std::endl << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;

	switchVariableIfGreaterUsingReference(a, b);

	std::cout << std::endl << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;

	return 0;
}