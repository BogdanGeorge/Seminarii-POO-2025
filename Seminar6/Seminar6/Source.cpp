#include <iostream>
#include <string>

using namespace std;


class bankAccount {

private:
	const int creditLimit;
	string accountHolder;
	int numberOfTransactions;


public:
	float* transactions;
	static int counter;

	bankAccount(string accountHolder) : accountHolder(accountHolder), numberOfTransactions(0), transactions(nullptr), creditLimit(15000)
	{
		counter++;
	}

	bankAccount(string accountHolder, float* transactions, int numberOfTransactions) : creditLimit(15000)
	{
		cout << "Constructorul cu parametrii a fost apelat" << endl;

		this->accountHolder = accountHolder;
		if (numberOfTransactions <= 0) {
			this->transactions = nullptr;
			this->numberOfTransactions = 0;
		}
		else {
			this->numberOfTransactions = numberOfTransactions;
			this->transactions = new float[numberOfTransactions];

			for (int i = 0; i < numberOfTransactions; i++)
				this->transactions[i] = transactions[i];
		}

		counter++;
	}

	bankAccount(const bankAccount& bankAccount) : creditLimit(15000)
	{
		cout << "Constructorul de copiere a fost apelat" << endl;

		this->accountHolder = bankAccount.accountHolder;

		this->numberOfTransactions = bankAccount.numberOfTransactions;
		this->transactions = new float[bankAccount.numberOfTransactions];
		for (int i = 0; i < bankAccount.numberOfTransactions; i++)
			this->transactions[i] = bankAccount.transactions[i];

		counter++;
	}

	bankAccount& operator=(const bankAccount& bankAccount)
	{
		cout << "operator= a fost apelat" << endl;

		if (&bankAccount == this)
		{
			cout << "sunt egale" << endl;
			return *this;
		}

		if (this->transactions != nullptr)
		{
			delete[] this->transactions;
			this->transactions = nullptr;
			this->numberOfTransactions = 0;
		}

		this->accountHolder = bankAccount.accountHolder;

		this->numberOfTransactions = bankAccount.numberOfTransactions;
		this->transactions = new float[bankAccount.numberOfTransactions];
		for (int i = 0; i < bankAccount.numberOfTransactions; i++)
			this->transactions[i] = bankAccount.transactions[i];

		return *this;
	}

	static void printCounter()
	{
		cout << counter << endl;
	}

	void printDetails()
	{
		cout << this->accountHolder << endl;
		for (int i = 0; i < this->numberOfTransactions; i++)
			cout << this->transactions[i] << " ";

		cout << endl;

		cout << "avand limita de credit " << this->creditLimit << endl;

	}

	~bankAccount()
	{
		counter--;
		if (this->transactions != nullptr)
		{
			delete[] this->transactions;
			this->transactions = nullptr;
			this->numberOfTransactions = 0;
		}
	}

};

int bankAccount::counter = 0;

int main()
{
	float transactions[2] = { 12 , 60 };
	bankAccount a1("Ion", transactions, 2);
	a1.printDetails();


	transactions[0] = 15;
	a1.printDetails();


	bankAccount a2 = a1;

	a2.printDetails();
	a1.transactions[0] = 30;

	cout << "=================" << endl;

	a1.printDetails();
	a2.printDetails();

	bankAccount a3("Gigel", transactions, 2);

	a1 = a3; // a1.operator=(a3);

	a1.printDetails();

	a3 = a1 = a2;

	a3.printDetails();

	a3 = a3;

	a3.printDetails();

	cout << a3.counter << endl;

	bankAccount::printCounter();

	return 0;
}