#include <iostream>
#include<string>
#include<fstream>

using namespace std;

enum TipContBancar { debit = 100, credit = 200 };

class contBancar;
class contBancarDeCredit;

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
	friend contBancarDeCredit;
};

class contBancar {
protected:
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

	virtual void printTranzactii()
	{
		for (int i = 0; i < nrTranzactii; i++)
		{
			cout << tranzactii[i] << " ";
		}

		cout << endl;
	}

	virtual ~contBancar()
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

	virtual void GetDescription() = 0;

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

	friend ostream& operator<<(ostream& out, const contBancar& cont);
	friend istream& operator>>(istream& in, contBancar& cont);
	friend ofstream& operator<<(ofstream& out, const contBancar& cont);
	friend ifstream& operator>>(ifstream& in, contBancar& cont);
};

float contBancar::rataDobanda = 10;

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
		cont.tipCont = TipContBancar::credit;
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

	void writeToBinaryFile(string numeFisier)
	{
		ofstream f(numeFisier, ios::binary);

		int lungimeNume = this->client.nume.length();
		f.write((char*)&lungimeNume, sizeof(lungimeNume));
		f.write(this->client.nume.c_str(), lungimeNume + 1);

		f.write((char*)&this->client.varsta, sizeof(this->client.varsta));
		f.write((char*)&this->tipCont, sizeof(this->tipCont));
		f.write((char*)&this->nrTranzactii, sizeof(this->nrTranzactii));
		for (int i = 0; i < this->nrTranzactii; i++)
		{
			f.write((char*)&this->tranzactii[i], sizeof(this->tranzactii[i]));
		}

		int lungimeNrCard = strlen(this->nrCard);
		f.write((char*)&lungimeNrCard, sizeof(lungimeNrCard));
		f.write(this->nrCard, lungimeNrCard + 1);
		f.write((char*)&this->limitaCredit, sizeof(this->limitaCredit));

		f.close();
	}


	void GetDescription()
	{
		cout << "Cont bancar de credit" << endl;
	}

	void readFromBinaryFile(string numeFisier)
	{
		ifstream f(numeFisier, ios::binary);

		int lungimeNume = 0;
		f.read((char*)&lungimeNume, sizeof(lungimeNume));

		char* temp = new char[lungimeNume + 1];
		f.read(temp, lungimeNume + 1);

		this->client.nume = temp;

		delete[] temp;
		temp = nullptr;

		f.read((char*)&this->client.varsta, sizeof(this->client.varsta));
		f.read((char*)&this->tipCont, sizeof(this->tipCont));
		f.read((char*)&this->nrTranzactii, sizeof(this->nrTranzactii));

		if (this->tranzactii != nullptr)
		{
			delete[] this->tranzactii;
			this->tranzactii = nullptr;
		}

		this->tranzactii = new float[this->nrTranzactii];
		for (int i = 0; i < this->nrTranzactii; i++)
		{
			f.read((char*)&this->tranzactii[i], sizeof(this->tranzactii[i]));
		}

		int lungimeNrCard = 0;

		f.read((char*)&lungimeNrCard, sizeof(lungimeNrCard));

		if (this->nrCard != nullptr)
		{
			delete[] this->nrCard;
			this->nrCard = nullptr;
		}

		this->nrCard = new char[lungimeNrCard + 1];
		f.read(this->nrCard, lungimeNrCard + 1);
		f.read((char*)&this->limitaCredit, sizeof(this->limitaCredit));
	}

	void printTranzactii()
	{
		cout << "Tranzactiile contului de credit sunt: " << endl;
		contBancar::printTranzactii();
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
	out << (contBancar&)cont;

	out << cont.nrCard << endl;
	out << cont.limitaCredit << endl;

	return out;
}


ofstream& operator<<(ofstream& out, const contBancarDeCredit& cont)
{
	out << (contBancar&)cont;

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

class contBancarDebit :public contBancar
{
	float soldDebit;
public:
	contBancarDebit() : contBancar("N/A", 0, 200, nullptr, 0)
	{
		soldDebit = 0;
	}

	contBancarDebit(
		string denumireClient,
		int varsta,
		float* tranzactii,
		int nrTranzactii
	) : contBancar(denumireClient, varsta, 200, tranzactii, nrTranzactii)
	{
		this->soldDebit = 0;

		for (int i = 0; i < this->nrTranzactii; i++)
		{
			soldDebit = soldDebit + this->tranzactii[i];
		}
	}

	void printTranzactii()
	{
		cout << "Tranzactiile contului de debit sunt: " << endl;
		contBancar::printTranzactii();
	}

	void GetDescription()
	{
		cout << "Cont bancar de debit" << endl;
	}
};

int main()
{
	float tranzactii[2] = { 1,2 };
	contBancarDeCredit c1("Remus", 22, tranzactii, 2, 10, "ASD123");

	c1.writeToBinaryFile("c1.bin");

	contBancarDeCredit c2;

	c2.readFromBinaryFile("c1.bin");

	cout << c2;

	float debittranzactii[3] = { 10, 15,5 };
	contBancarDebit d1("Gigel", 30, debittranzactii, 3);
	contBancarDebit d2("Mihai", 30, debittranzactii, 3);

	c1.printTranzactii();
	d1.printTranzactii();

	/*contBancar conturi[4] = { c1, c2, d1, d2 };*/

	//contBancar* conturi = new contBancar[4]{ c1,c2,d1,d2 };

	contBancar* conturi[4] = { &c1, &c2, &d1, &d2 };

	for (int i = 0; i < 4; i++)
	{
		conturi[i]->printTranzactii();
		conturi[i]->GetDescription();
	}

}