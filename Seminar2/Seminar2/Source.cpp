#include<iostream>

void switchNumbers(int a, int b)
{
	int aux = a;
	a = b;
	b = aux;
}

void switchNumersUsingReference(int& a, int& b)
{
	int aux = a;
	a = b;
	b = aux;
}

void switchNumbersUsingPointer(int* a, int* b)
{
	std::cout << "Adresa lui a din functia switchNumbersUsingPointer este" << &a << std::endl;
	std::cout << "Adresa lui b din functia switchNumbersUsingPointer este" << &b << std::endl;

	std::cout << "Valoarea lui a din functia switchNumbersUsingPointer este" << a << std::endl;
	std::cout << "Valoarea lui b din functia switchNumbersUsingPointer este" << b << std::endl;


	std::cout << "Valoarea de la adresa retinuta de a din functia switchNumbersUsingPointer este" << *a << std::endl;
	std::cout << "Valoarea de la adresa retinuta de b din functia switchNumbersUsingPointer este" << *b << std::endl;

	int aux = *a;
	*a = *b;
	*b = aux;

}

void toUpper(char* charArr)
{
	int i;
	for (i = 0; i < strlen(charArr); i++)
		if (charArr[i] >= 'a' && charArr[i] <= 122)
			charArr[i] = charArr[i] - 32;
}

char* toUpperWithReturn(const char* charArr)
{
	//char newCharArr[100]; // ====> aloca memorie pe stack si va fi dezalocata automat cand se termina functiei toUpperWithReturn
	char* newCharArr = new char[strlen(charArr) + 1]; // aloca memorie pe heap, iar noi vom fi responsabili sa dezalocam memoria

	strcpy_s(newCharArr, strlen(charArr) + 1, charArr);

	int i;
	for (i = 0; i < strlen(newCharArr); i++)
		if (newCharArr[i] >= 'a' && newCharArr[i] <= 122)
			newCharArr[i] = newCharArr[i] - 32;

	return newCharArr;
}

void printChars(const char charArr[])
{
	char* newCharArrUppercased = toUpperWithReturn(charArr);

	std::cout << "Old char array: " << charArr << std::endl;
	std::cout << "New char array uppercased: " << newCharArrUppercased << std::endl;

	delete[] newCharArrUppercased; // Pentru a evita memory leak
	newCharArrUppercased = nullptr;
}


int main()
{
	int a = 1;
	int b = 2;
	int* pa = &a;
	int* pb = &b;

	std::cout << "Adresa lui pa din functia main este" << &pa << std::endl;
	std::cout << "Adresa lui pb din functia main este" << &pb << std::endl;

	std::cout << "Valoarea lui pa din functia main este" << pa << std::endl;
	std::cout << "Valoarea lui pb din functia main este" << pb << std::endl;


	std::cout << "Valoarea de la adresa retinuta de pa din functia main este" << *pa << std::endl;
	std::cout << "Valoarea de la adresa retinuta de pb din functia main este" << *pb << std::endl;

	std::cout << "=======================================" << std::endl;

	switchNumbers(a, b);
	switchNumersUsingReference(a, b);
	switchNumbersUsingPointer(pa, pb);

	std::cout << "valoarea de la adresa retinuta de pa este: " << *pa << std::endl;
	std::cout << "valoarea de la adresa retinuta de pb este: " << *pb << std::endl;

	std::cout << "valoarea lui a este: " << a << std::endl;
	std::cout << "valoarea lui b este: " << b << std::endl;

	//char c2 = "T"; include si '\0'
	char c3 = 'T';
	char c = 120;
	std::cout << c << std::endl;

	c = c + 8;

	std::cout << (int)c << " " << c << std::endl;


	char charArr[] = "Text";

	printChars(charArr);

}