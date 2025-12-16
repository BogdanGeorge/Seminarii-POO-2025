#include <iostream>
#include<string>
#include<fstream>

using namespace std;

enum TipContBancar { debit = 100, credit = 200 };

class contBancar;

class client {
	string nume;
	int varsta;
public:
	client(string nume, int varsta)
	{
		this->nume = nume;
		this->varsta = varsta;
	}

	string getNume() const
	{
		return this->nume;
	}

	friend istream& operator>>(istream& in, contBancar& cont);
	friend ofstream& operator<<(ofstream& out, const contBancar& cont);
	friend ifstream& operator>>(ifstream& in, contBancar& cont);
};

class contBancar {
	client client;
	TipContBancar tipCont;
	float* tranzactii;
	int nrTranzactii;
	static float rataDobanda;
public:
	contBancar(string denumireClient, int varsta, int tipContBancar, float* tranzactii, int nrTranzactii) : client(denumireClient, varsta)
	{
		if (tipContBancar == 100)
		{
			this->tipCont = TipContBancar::debit;

		}
		else
		{
			this->tipCont = TipContBancar::credit;
		}
		if (tranzactii != nullptr && nrTranzactii > 0)
		{
			this->tranzactii = new float[nrTranzactii];
			for (int i = 0; i < nrTranzactii; i++)
			{
				this->tranzactii[i] = tranzactii[i];
			}
		}
		else
			this->tranzactii = nullptr;

		this->nrTranzactii = nrTranzactii;


	}

	explicit operator float()
	{
		float suma = 0;
		for (int i = 0; i < this->nrTranzactii; i++)
		{
			suma = suma + this->tranzactii[i];
		}

		return suma;
	}

	explicit operator int()
	{
		return this->nrTranzactii;
	}

	contBancar operator+(int valoare)
	{
		contBancar cont = *this;

		for (int i = 0; i < nrTranzactii; i++)
		{
			cont.tranzactii[i] = cont.tranzactii[i] + valoare;
		}

		return cont;
	}

	float& operator[](int index)
	{
		if (index < 0 || index >= this->nrTranzactii)
		{
			throw exception("Index este invalid");
		}
		else {
			return this->tranzactii[index];
		}
	}

	contBancar operator+(contBancar& cont)
	{
		contBancar copie = *this;
		if (copie.tranzactii != nullptr)
		{
			delete[] copie.tranzactii;
			copie.tranzactii = nullptr;
			copie.nrTranzactii = 0;
		}
		copie.nrTranzactii = this->nrTranzactii + cont.nrTranzactii;
		copie.tranzactii = new float[copie.nrTranzactii];
		for (int i = 0; i < copie.nrTranzactii; i++)
		{
			if (i < this->nrTranzactii)
			{
				copie.tranzactii[i] = this->tranzactii[i];
			}
			else
				copie.tranzactii[i] = cont.tranzactii[i - this->nrTranzactii];
		}


		return copie;
	}

	void printTranzactii()
	{
		for (int i = 0; i < nrTranzactii; i++)
		{
			cout << tranzactii[i] << " ";
		}

		cout << endl;
	}

	~contBancar()
	{
		if (this->tranzactii != nullptr)
		{
			delete[] this->tranzactii;
			this->tranzactii = nullptr;
			this->nrTranzactii = 0;
		}
	}

	contBancar(const contBancar& cont) : client(cont.client)
	{
		this->client = cont.client;
		this->tipCont = cont.tipCont;
		this->nrTranzactii = cont.nrTranzactii;
		if (cont.tranzactii != nullptr && cont.nrTranzactii > 0)
		{
			this->tranzactii = new float[cont.nrTranzactii];
			for (int i = 0; i < cont.nrTranzactii; i++)
			{
				this->tranzactii[i] = cont.tranzactii[i];
			}
		}
		else
			this->tranzactii = nullptr;

	}

	contBancar& operator=(const contBancar& cont) {
		if (this == &cont) {
			return *this;
		}
		this->client = cont.client;
		this->tipCont = cont.tipCont;
		if (this->tranzactii != nullptr) {
			delete[] this->tranzactii;
			this->tranzactii = nullptr;
			this->nrTranzactii = 0;
		}
		if (cont.tranzactii != nullptr) {
			this->tranzactii = new float[cont.nrTranzactii];
			for (int i = 0; i < cont.nrTranzactii; i++) {
				this->tranzactii[i] = cont.tranzactii[i];
			}
			this->nrTranzactii = cont.nrTranzactii;
		}
		else {
			this->tranzactii = nullptr;
			this->nrTranzactii = 0;
		}

		return *this;
	}

	float operator()(int val)
	{
		if (nrTranzactii > 0) {
			tranzactii[0] = tranzactii[0] + val;

			return tranzactii[0];
		}
		else {
			throw exception("Nu exista tranzactii");
		}
	}

	friend contBancar operator+(int valoare, contBancar cont);
	friend ostream& operator<<(ostream& out, const contBancar& cont);
	friend istream& operator>>(istream& in, contBancar& cont);
	friend ofstream& operator<<(ofstream& out, const contBancar& cont);
	friend ifstream& operator>>(ifstream& in, contBancar& cont);
};

float contBancar::rataDobanda = 10;

contBancar operator+(int valoare, contBancar cont)
{
	for (int i = 0; i < cont.nrTranzactii; i++)
	{
		cont.tranzactii[i] = cont.tranzactii[i] + valoare;
	}

	return cont;
}

ostream& operator<<(ostream& out, const contBancar& cont)
{
	out << cont.client.getNume() << endl;

	for (int i = 0; i < cont.nrTranzactii; i++)
	{
		out << cont.tranzactii[i] << " ";
	}

	out << endl;

	return out;
}

ofstream& operator<<(ofstream& out, const contBancar& cont)
{
	out << cont.client.getNume() << endl;
	out << cont.client.varsta << endl;
	out << cont.tipCont << endl;
	out << cont.nrTranzactii << endl;

	for (int i = 0; i < cont.nrTranzactii; i++)
	{
		out << cont.tranzactii[i] << endl;
	}

	return out;
}

istream& operator>>(istream& in, contBancar& cont)
{
	cout << "Nume client: ";

	in >> ws;
	getline(in, cont.client.nume);

	cout << "Nr tranzactii: ";
	in >> cont.nrTranzactii;

	if (cont.tranzactii != nullptr) {
		delete[] cont.tranzactii;
		cont.tranzactii = nullptr;
	}

	cont.tranzactii = new float[cont.nrTranzactii];
	for (int i = 0; i < cont.nrTranzactii; i++) {
		cout << "Tranzactie[" << i << "]: ";
		in >> cont.tranzactii[i];
	}

	return in;
}

ifstream& operator>>(ifstream& in, contBancar& cont)
{
	in >> ws;
	getline(in, cont.client.nume);
	in >> cont.client.varsta;

	int tipContTemp = 0;

	in >> tipContTemp;

	if (tipContTemp == 200)
	{
		cont.tipCont == TipContBancar::credit;
	}
	else {
		cont.tipCont = TipContBancar::debit;
	}

	in >> cont.nrTranzactii;

	if (cont.tranzactii != nullptr) {
		delete[] cont.tranzactii;
		cont.tranzactii = nullptr;
	}

	cont.tranzactii = new float[cont.nrTranzactii];
	for (int i = 0; i < cont.nrTranzactii; i++)
	{
		in >> cont.tranzactii[i];
	}

	return in;
}

class contBancarDeCredit : public contBancar
{
	int limitaCredit;
	char* nrCard;
public:
	contBancarDeCredit() : contBancar("N/A", 0, 200, nullptr, 0)
	{
		this->limitaCredit = 0;
		this->nrCard = nullptr;
	}

	contBancarDeCredit(
		string denumireClient,
		int varsta,
		float* tranzactii,
		int nrTranzactii,
		int limitaCredit,
		const char* nrCard) : contBancar(denumireClient, varsta, 200, tranzactii, nrTranzactii)
	{
		this->limitaCredit = limitaCredit;
		if (nrCard != nullptr)
		{
			this->nrCard = new char[strlen(nrCard) + 1];
			strcpy_s(this->nrCard, strlen(nrCard) + 1, nrCard);
		}
		else
		{
			this->nrCard = nullptr;
		}
	}

	contBancarDeCredit(const contBancarDeCredit& cont) : contBancar(cont)
	{
		this->limitaCredit = cont.limitaCredit;
		if (cont.nrCard != nullptr)
		{
			this->nrCard = new char[strlen(cont.nrCard) + 1];
			strcpy_s(this->nrCard, strlen(cont.nrCard) + 1, cont.nrCard);
		}
		else
		{
			this->nrCard = nullptr;
		}
	}

	contBancarDeCredit& operator=(const contBancarDeCredit& cont)
	{
		if (this != &cont)
		{
			contBancar::operator=(cont);

			if (this->nrCard != nullptr)
			{
				delete[] this->nrCard;
				this->nrCard = nullptr;
			}

			this->limitaCredit = cont.limitaCredit;
			if (cont.nrCard != nullptr)
			{
				this->nrCard = new char[strlen(cont.nrCard) + 1];
				strcpy_s(this->nrCard, strlen(cont.nrCard) + 1, cont.nrCard);
			}
			else
			{
				this->nrCard = nullptr;
			}
		}

		return *this;
	}

	~contBancarDeCredit()
	{
		if (this->nrCard != nullptr)
		{
			delete[] this->nrCard;
			this->nrCard = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const contBancarDeCredit& cont);
	friend istream& operator>>(istream& in, contBancarDeCredit& cont);
	friend ofstream& operator<<(ofstream& out, const contBancarDeCredit& cont);
	friend ifstream& operator>>(ifstream& in, contBancarDeCredit& cont);
};

ostream& operator<<(ostream& out, const contBancarDeCredit& cont)
{
	out << (contBancar)cont;

	out << cont.nrCard << endl;
	out << cont.limitaCredit << endl;

	return out;
}


ofstream& operator<<(ofstream& out, const contBancarDeCredit& cont)
{
	out << (contBancar)cont;

	out << cont.nrCard << endl;
	out << cont.limitaCredit << endl;

	return out;
}


istream& operator>>(istream& in, contBancarDeCredit& cont)
{
	in >> (contBancar&)cont;

	if (cont.nrCard != nullptr)
	{
		delete[] cont.nrCard;
		cont.nrCard = nullptr;
	}

	cout << "Introduceti nr card ";
	string temp;
	in >> ws;
	getline(in, temp);

	cont.nrCard = new char[temp.length() + 1];
	strcpy_s(cont.nrCard, temp.length() + 1, temp.c_str());

	cout << "Limita de credit este ";
	in >> cont.limitaCredit;

	return in;
}

ifstream& operator>>(ifstream& in, contBancarDeCredit& cont)
{
	in >> (contBancar&)cont;
	if (cont.nrCard != nullptr)
	{
		delete[] cont.nrCard;
		cont.nrCard = nullptr;
	}

	string temp;
	in >> ws;
	getline(in, temp);

	cont.nrCard = new char[temp.length() + 1];
	strcpy_s(cont.nrCard, temp.length() + 1, temp.c_str());

	in >> cont.limitaCredit;

	return in;
}

int main()
{
	float tranzactii[2] = { 1,2 };
	contBancarDeCredit c1("Remus", 22, tranzactii, 2, 10, "ASD123");

	cout << c1;
	cin >> c1;
	cout << c1;

	ofstream f("test.txt");

	f << c1;

	f.close();

	contBancarDeCredit c2;

	ifstream fIn("test.txt");

	fIn >> c2;

	cout << c2;

	ofstream fBin("test.bin", ios::binary);

	int a = 100;
	fBin.write((char*)&a, sizeof(a));

	fBin.close();

	ifstream inBin("test.bin", ios::binary);

	int b = 0;
	inBin.read((char*)&b, sizeof(b));

	cout << b;

}