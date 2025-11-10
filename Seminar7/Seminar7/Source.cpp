#include <iostream>
using namespace std;

enum tipCurs
{
	IT, matematica
};

class Curs
{
	char* nume;
	int nrStudenti;
	tipCurs tip;

public:
	Curs(const char* nume, int nrStudenti, tipCurs tip)
	{

		if (nume != nullptr)
		{
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else
			this->nume = nullptr;
		this->nrStudenti = nrStudenti;
		this->tip = tip;
	}

	Curs(const Curs& curs)
	{

		if (curs.nume != nullptr)
		{
			this->nume = new char[strlen(curs.nume) + 1];
			strcpy_s(this->nume, strlen(curs.nume) + 1, curs.nume);
		}
		else
			this->nume = nullptr;
		this->nrStudenti = curs.nrStudenti;
		this->tip = curs.tip;
	}
	Curs& operator=(const Curs& curs)
	{
		if (&curs == this)
		{
			return *this;
		}

		if (this->nume != nullptr)
		{
			delete[]nume;
			this->nume = nullptr;
		}

		if (curs.nume != nullptr)
		{
			this->nume = new char[strlen(curs.nume) + 1];
			strcpy_s(this->nume, strlen(curs.nume) + 1, curs.nume);
		}
		else
			this->nume = nullptr;

		this->nrStudenti = curs.nrStudenti;
		this->tip = curs.tip;
		return *this;
	}

	Curs& operator++()
	{
		this->nrStudenti = this->nrStudenti + 1;

		return *this;
	}

	Curs operator++(int i)
	{
		Curs copy = *this;

		this->nrStudenti = this->nrStudenti + 1;

		return copy;
	}

	bool operator!()
	{
		if (nrStudenti == 0)
		{
			return true;
		}
		else {
			return false;
		}
	}


	~Curs()
	{
		if (this->nume != nullptr)
		{
			delete[]nume;
			this->nume = nullptr;
		}
	}

	char* getName()
	{
		if (this->nume != nullptr)
		{
			char* copy = new char[strlen(this->nume) + 1];
			strcpy_s(copy, strlen(this->nume) + 1, this->nume);
			return copy;
		}
		else
			return nullptr;
	}

	int getNumberOfStudents()
	{
		return this->nrStudenti;
	}

	void setName(const char* nume)
	{
		if (this->nume != nullptr)
		{
			delete[] this->nume;
			this->nume = nullptr;
		}
		if (nume != nullptr)
		{
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
	}

	void setName(const string name)
	{
		if (this->nume != nullptr)
		{
			delete[] this->nume;
			this->nume = nullptr;
		}

		this->nume = new char[name.length() + 1];
		strcpy_s(this->nume, name.length() + 1, name.c_str());

	}

	//friend Curs& operator++(Curs& curs);
};
//
//Curs& operator++(Curs& curs)
//{
//	curs.nrStudenti = curs.nrStudenti + 1;
//
//	return curs;
//}

int main()
{
	Curs curs("POO", 20, tipCurs::IT);
	curs = curs;
	char* numeCurs = curs.getName();
	cout << numeCurs << endl;

	delete[] numeCurs;
	numeCurs = nullptr;

	curs.setName("Programare orientata obiect");

	numeCurs = curs.getName();
	cout << numeCurs << endl;


	delete[] numeCurs;
	numeCurs = nullptr;

	string newName = "Test";

	curs.setName(newName);

	numeCurs = curs.getName();
	cout << numeCurs << endl;

	delete[] numeCurs;
	numeCurs = nullptr;

	int i = 1;
	int j = i++;

	cout << "i=" << i << endl;
	cout << "j=" << j << endl;

	j = ++i;

	cout << "i=" << i << endl;
	cout << "j=" << j << endl;

	Curs newCurs = ++curs;

	cout << "nr studenti pt curs = " << curs.getNumberOfStudents() << endl;
	cout << "nr studenti pt newCurs = " << newCurs.getNumberOfStudents() << endl;


	newCurs = curs++;

	cout << "nr studenti pt curs = " << curs.getNumberOfStudents() << endl;
	cout << "nr studenti pt newCurs = " << newCurs.getNumberOfStudents() << endl;

	if (!curs)
	{
		cout << "numarul studentilor este 0" << endl;
	}
	else
	{
		cout << "am studenti pentru cursul apelat" << endl;
	}
}