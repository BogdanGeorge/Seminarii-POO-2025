#include <iostream>
#include<string>
using namespace std;

enum TipContBancar { debit = 100, credit = 200 };

class contBancar {
	string denumireClient;
	TipContBancar tipCont;
	float* tranzactii;
	int nrTranzactii;
	static float rataDobanda;
public:
	contBancar(string denumireClient, int tipContBancar, float* tranzactii, int nrTranzactii)
	{
		this->denumireClient = denumireClient;
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

	contBancar(const contBancar& cont)
	{
		this->denumireClient = cont.denumireClient;
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
		this->denumireClient = cont.denumireClient;
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

	friend contBancar operator+(int valoare, contBancar cont);
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


int main()
{
	float tranzactii[2] = { 1,2 };
	contBancar a("Mihai", 100, tranzactii, 2);
	contBancar b = a;

	cout << "Nr tranzactii: " << (int)a << endl;
	cout << "Suma: " << (float)a << endl;

	contBancar c = a + b;

	c.printTranzactii();

	c = c + 1;

	c.printTranzactii();

	c = 1 + c;
	c.printTranzactii();

	cout << "pentru index 1 avem valoarea: " << c[1] << endl;

	c[1] = 10;

	cout << "pentru index 1 avem valoarea: " << c[1] << endl;
}