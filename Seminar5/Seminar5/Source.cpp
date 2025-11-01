#include<iostream>
#include<string>

using namespace std;

enum culoare {
	Unknown = 0, White = 1, Black = 2
};

class masina {
	string _marca;
	culoare _color;
	int _nbOfKmTravelled;
public:
	masina() {
		cout << "Constructor implicit apelat! :)" << endl;
		_color = Unknown;
		_nbOfKmTravelled = 0;
	};


	masina(string marca, culoare color) {
		cout << "Constructor cu parametrii apelat! :)" << endl;

		this->_marca = marca;
		this->_color = color;
		this->_nbOfKmTravelled = 0;
	}

	masina(const masina& masina)
	{
		cout << "Constructorul de copiere a fost apelat!" << endl;
		this->_marca = masina._marca;
		this->_color = masina._color;
		this->_nbOfKmTravelled = masina._nbOfKmTravelled;
	}

	int getNbOfKmTravelled()
	{
		return this->_nbOfKmTravelled;
	}

	void setNbOfKmTravelled(int nbOfKmTravelled)
	{
		if (nbOfKmTravelled < this->_nbOfKmTravelled)
		{
			return;
		}

		this->_nbOfKmTravelled = nbOfKmTravelled;
	}

	~masina()
	{
		cout << "destructorul clasei a fost apelat" << endl;
	}
};

masina travelFromBucharestToSinaia(masina car)
{
	car.setNbOfKmTravelled(car.getNbOfKmTravelled() + 200);

	return car;
}

void travelFromBucharestToSinaiaUsingReference(masina& car)
{
	car.setNbOfKmTravelled(car.getNbOfKmTravelled() + 200);
}



class student
{
	string _nume;
	int _varsta;
	int numarNote;
public:
	int* note;

	student(string nume, int varsta)
	{
		this->_nume = nume;
		this->_varsta = varsta;
		this->note = nullptr;
		this->numarNote = 2;
		this->note = new int[2];
		for (int i = 0; i < i < 2; i++)
		{
			this->note[i] = 9;
		}
	}

	student(student& s)
	{
		this->_nume = s._nume;
		this->_varsta = s._varsta;
		this->note = s.note; // Nu este ok, intrucat ne creaza o copie superficiala
	}
};

int main()
{
	char charArr[] = "test";
	char* charArrSecond = charArr;
	charArrSecond[0] = 'A';

	std::cout << charArr << std::endl;
	std::cout << charArrSecond << std::endl;

	string str = "Test";
	string str2 = str;
	str2[0] = 'A';

	std::cout << str << std::endl;
	std::cout << str2 << std::endl;

	cout << str.length() << std::endl;

	const char* charArr2 = str.c_str();

	masina unknownCar;
	masina hyundai("Hyundai", Black);

	masina hyundaiTucson = hyundai;

	hyundai = travelFromBucharestToSinaia(hyundai);

	cout << "Numarul de km parcursi este: " << hyundai.getNbOfKmTravelled() << endl;

	travelFromBucharestToSinaiaUsingReference(hyundai);

	cout << "Numarul de km parcursi este: " << hyundai.getNbOfKmTravelled() << endl;


	masina* pointerToHyundai = new masina("Dacia", culoare::White);

	cout << "Numarul de km parcursi este: " << (*pointerToHyundai).getNbOfKmTravelled() << endl;
	cout << "Numarul de km parcursi este: " << pointerToHyundai->getNbOfKmTravelled() << endl;

	delete pointerToHyundai;
	pointerToHyundai = nullptr;

	int size = 2;
	int* note = new int[size];
	note[0] = 9;
	note[1] = 9;

	student s("Nume", 20);
	student s2 = s;

	s2.note[0] = 10;

	return 0;
}