#include<iostream>

enum matrixState
{
	unintialized = 0,
	partiallyInitialized = 2,
	initialized = 9,
};

struct myMatrix {
	int rows;
	int columns;
	int** matrix;
};

class myMatrixClass {
public:
	int rows = 0;
	int columns = 0;
	int** matrix = nullptr;
	matrixState state = matrixState::unintialized;


	void showMatrix()
	{
		// (*this). = this->

		if (this->state == matrixState::unintialized)
		{
			std::cout << "Matricea nu este initializata " << std::endl;
		}
		else {
			int column, row;
			for (row = 0; row < this->rows; row++)
			{
				for (column = 0; column < this->columns; column++)
				{
					std::cout << this->matrix[row][column];
				}
				std::cout << std::endl;
			}
		}
	}
};

myMatrixClass createMatrix()
{
	myMatrixClass m;

	std::cout << "Introduceti numarul de randuri: ";
	std::cin >> m.rows;


	std::cout << "Introduceti numarul de coloane: ";
	std::cin >> m.columns;

	m.matrix = new  int* [m.rows];

	for (int i = 0; i < m.rows; i++)
	{
		m.matrix[i] = new int[m.columns];
	}

	m.state = matrixState::initialized;
	for (int row = 0; row < m.rows; row++)
	{
		for (int column = 0; column < m.columns; column++)
		{
			std::cout << "matrix[" << row << "][" << column << "]=";
			std::cin >> m.matrix[row][column];
		}
	}

	return m;
}


int main()
{
	myMatrixClass matrix = createMatrix();
	matrix.showMatrix();

	myMatrixClass matrix2;

	matrix2.showMatrix();

	std::cout << sizeof(matrix2.state) << std::endl;

	std::cout << sizeof(matrix2.matrix) << std::endl;

	std::cout << sizeof(matrix2) << std::endl;

	return 0;
}