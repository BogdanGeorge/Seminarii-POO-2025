#include<iostream>

using namespace std;

class invalidSizeForVector : public exception
{
	string message;
public:
	invalidSizeForVector(string message)
	{
		this->message = message;
	}

	const char* what()
	{
		return message.c_str();
	}
};

class Person
{
protected:
	string name;
public:
	Person(string name)
	{
		this->name = name;
	}

	virtual void printDetails()
	{
		cout << "Name: " << this->name << endl;
	}
};

class Student : public Person
{
	string universityName;
public:
	Student(string name, string universityName) : Person(name)
	{
		this->universityName = universityName;
	}

	void printDetails()
	{
		Person::printDetails();
		cout << "Numele universitatii:" << this->universityName << endl;
	}
};

class Employee : public Person
{
	string companyName;
public:
	Employee(string name, string companyName) : Person(name)
	{
		this->companyName = companyName;
	}

	void printDetails()
	{
		Person::printDetails();
		cout << "Numele companiei:" << this->companyName << endl;
	}
};

class Intern : public Student, public Employee
{
	int intershipDuration;
public:
	Intern(string name, string universityName, string companyName, int intershipDuration)
		: Student(name, universityName), Employee(name, companyName)
	{
		this->intershipDuration = intershipDuration;
		Student::name = "Gigel";
		Employee::name = "Vasile";
	}
};


template <typename T>
T sum(T a, T b)
{
	return a + b;
}

template <typename T>
class Vector
{
	int size;
	T* elements;
public:
	Vector()
	{
		this->size = 0;
		this->elements = nullptr;
	}

	void push(T val)
	{
		T* newElements = new T[size + 1];
		for (int i = 0; i < size; i++)
		{
			newElements[i] = elements[i];
		}

		newElements[size] = val;
		if (this->elements != nullptr)
		{
			delete[] this->elements;
		}

		this->elements = newElements;
		this->size = size + 1;
	}

	void pop()
	{
		if (size == 0)
		{
			throw invalidSizeForVector("Size este deja 0");
		}
		else if (size == 1)
		{
			size = 0;
			delete[] this->elements;
			this->elements = nullptr;
		}
		else
		{
			T* newElements = new T[size - 1];
			for (int i = 0; i < size - 1; i++)
			{
				newElements[i] = elements[i];
			}

			if (elements != nullptr)
			{
				delete[] this->elements;
			}

			this->elements = newElements;
			this->size = this->size - 1;

		}
	}

	int getSize()
	{
		return this->size;
	}

	T* getElements()
	{
		T* copy = new T[size];
		for (int i = 0; i < size; i++)
		{
			copy[i] = elements[i];
		}

		return copy;
	}
};

int main()
{
	Student student1("Bogdan", "ASE");
	Employee empl1("Razvan", "IBM");

	student1.printDetails();

	cout << "=============" << endl;

	empl1.printDetails();

	cout << "=======================================" << endl;

	Intern intern1("Ana", "ASE", "Google", 1);

	intern1.Student::printDetails();

	cout << "=============" << endl;

	intern1.Employee::printDetails();

	cout << "====================================" << endl;

	cout << sum<int>(1, 2) << endl;

	cout << sum<double>(0.2, 0.3) << endl;


	cout << "====================================" << endl;

	Vector<int> v;
	v.push(1);
	v.push(2);
	v.push(3);

	int* elements = v.getElements();
	for (int i = 0; i < v.getSize(); i++)
	{
		cout << elements[i] << " ";
	}

	cout << endl << "====================================" << endl;

	Vector<string> vString;
	vString.push("Ana");
	vString.push("Razvan");
	vString.push("Dorin");

	string* vStringElements = vString.getElements();
	for (int i = 0; i < vString.getSize(); i++)
	{
		cout << vStringElements[i] << " ";
	}

	vString.pop();
	vString.pop();
	vString.pop();
	cout << endl << "Dimensiunea este: " << vString.getSize() << endl;


	try {
		vString.pop();
		vString.pop();
		vString.pop();
	}
	catch (invalidSizeForVector ex)
	{
		cout << "invalidSizeForVector " << endl;
		cout << ex.what() << endl;

	}
	catch (exception ex)
	{
		cout << "exception " << endl;

		cout << ex.what() << endl;
	}


	return 0;
}