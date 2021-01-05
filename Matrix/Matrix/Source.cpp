#include <iostream>
#include <vector>

using namespace std;

class Matrix
{
private:
	int rows, columns;
	vector<vector<int>> elements;
	
public:

	enum Dimension{ Dissimilar, Similar };

	Matrix();
	Matrix(vector<vector<int>> mat, int rows, int columns);
	
	void setElements(vector<vector<int>> mat, int rows, int columns);
	void setElementAt(int number, int row, int column);
	
	vector<vector<int>> getElements();
	int getRowSize();
	int getColumnSize();
	
	bool isSquareMatrix();

	void display();
	
	void add(Matrix b);
	void subtract(Matrix b);
	void multiply(Matrix b);
	void multiply(int num);
	Matrix operator-(Matrix b);
	Matrix operator+(Matrix b);
	Matrix operator*(Matrix b);
	Matrix transpose();
	
	friend int checkDimension(Matrix a, Matrix b);
	friend ostream& operator<< (ostream &out, Matrix a);
	friend Matrix operator*(Matrix a, int num);
	friend Matrix operator*(int num, Matrix a);

	~Matrix();
};


Matrix::Matrix()
{
	this->rows = 2;
	this->columns = 2;
	this->elements = { {1,0},{0,1} };
}

Matrix::Matrix(vector<vector<int>> mat, int rows, int columns)
{
	this->setElements(mat, rows, columns);
}

void Matrix::setElements(vector<vector<int>> mat, int rows, int columns)
{
	this->rows = rows;
	this->columns = columns;

	for (int i = 0; i < mat.size(); i++) {
		if (mat[i].size() != this->columns) {
			cout << "\n!!!Enter a proper matrix of m*n dimensions!!!\n";
			exit(0);
		}
	}

	this->elements = mat;
}

void Matrix::setElementAt(int number, int row, int column)
{
	if (row < this->rows && column < this->columns)
		this->elements[row][column] = number;
	else
		cout << "\nIndex Out Of Bound\n";
}

vector<vector<int>> Matrix::getElements()
{
	return this->elements;
}

int Matrix::getRowSize()
{
	return this->rows;
}

int Matrix::getColumnSize()
{
	return this->columns;
}

bool Matrix::isSquareMatrix()
{
	if (this->rows == this->columns)
		return true;
	else
		return false;
}

void Matrix::add(Matrix b)
{
	Matrix result = *this + b;
	this->elements = result.elements;
	this->rows = result.rows;
	this->columns = result.columns;
}

void Matrix::subtract(Matrix b)
{
	Matrix result = *this - b;
	this->elements = result.elements;
	this->rows = result.rows;
	this->columns = result.columns;
}


void Matrix::multiply(int num)
{
	Matrix result = *this * num;
	this->elements = result.elements;
	this->rows = result.rows;
	this->columns = result.columns;
}

void Matrix::multiply(Matrix b)
{
	Matrix result = *this * b;
	this->elements = result.elements;
	this->columns = result.columns;
	this->rows = result.rows;
}

Matrix Matrix::operator+(Matrix b)
{
	if (checkDimension(*this, b) == Matrix::Dissimilar)
	{
		cout << "\n Matrix Addition cannot be done between these matrices";
		Matrix c({ {0} }, 1, 1);
		return c;
	}
	vector<vector<int>> temp(this->rows, vector<int>(this->columns));

	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++) {
			temp[i][j] = this->elements[i][j] + b.getElements()[i][j];
		}
	}

	Matrix t(temp, this->rows, this->columns);
	return t;
}

Matrix Matrix::operator-(Matrix b)
{
	if (checkDimension(*this, b) == Matrix::Dissimilar)
	{
		cout << "\n Matrix Subtraction cannot be done between these matrices";
		Matrix c({ {0} }, 1, 1);
		return c;
	}
	vector<vector<int>> temp(this->rows, vector<int>(this->columns));

	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++) {
			temp[i][j] = this->elements[i][j] - b.getElements()[i][j];
		}
	}

	Matrix t(temp, this->rows, this->columns);
	return t;
}

Matrix Matrix::operator*(Matrix b)
{
	Matrix temp({ {0} }, 1, 1);
	if (this->columns != b.rows)
	{
		cout << "\nMatrix Multiplication is not possible\n";
		return temp;
	}

	vector<vector<int>> mat(this->rows, vector<int>(b.columns, 0));

	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < b.columns; j++)
		{
			for (int k = 0; k < this->columns; k++) {
				mat[i][j] = mat[i][j] + (this->elements[i][k] * b.elements[k][j]);
			}
		}
	}
	
	temp.setElements(mat, this->rows, b.columns);
	return temp;
}

Matrix Matrix::transpose()
{
	vector<vector<int>> mat(this->columns, vector<int>(this->rows));

	for (int i = 0; i < this->columns; i++) {
		for (int j = 0; j < this->rows; j++) {
			mat[i][j] = this->elements[j][i];
 		}
	}
	
	Matrix result(mat, this->columns, this->rows);
	return result;
}

void Matrix::display()
{
	printf("Rows: %d \t Columns: %d\n", this->rows, this->columns);
	cout << "The matrix is of " << this->rows << " x " << this->columns << " dimension" <<endl;
	cout << "The elements are :" << endl;
	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->columns; j++) {
			cout << elements[i][j] << " ";
		}

		cout << endl;
	}
	cout << "--------------------------------------" << endl;
}

int checkDimension(Matrix a, Matrix b)
{
	if ((a.rows == b.rows) && (a.columns == b.columns))
		return Matrix::Similar;
	else
		return Matrix::Dissimilar;
}

Matrix operator*(Matrix a, int num)
{
	Matrix temp = a;

	for (int i = 0; i < a.rows; i++) {
		for (int j = 0; j < a.columns; j++) {
			temp.elements[i][j] = num * a.elements[i][j];
		}
	}

	return temp;
}

Matrix operator*(int num, Matrix a)
{
	return operator*(a, num);
}

ostream& operator<<(ostream &out, Matrix a)
{
	a.display();

	return out;

}

Matrix::~Matrix()
{
	this->elements.clear();
}


int main()
{
	vector<vector<int>> matA{ {1,2,4}, {3,6,8} };
	vector<vector<int>> matB{ {2,5,8}, {1,7,9} };
	
	Matrix matrixA(matA, 2, 3);
	Matrix matrixB(matB, 2, 3);
	Matrix matrixC, matrixD, matrixE, matrixF;
	cout << "Matrix A: " << endl;
	cout << matrixA;
	cout << "Matrix B: " << endl;
	cout << matrixB;

	matrixC = matrixA + matrixB;
	cout << "Matrix Addition" << endl;
	cout << matrixC;

	matrixC = matrixA - matrixB;
	cout << "Matrix Subtraction" << endl;
	cout << matrixC;

	matrixD = 2 * matrixC;
	cout << "Scalar Matrix Multiplication" << endl;
	cout << matrixD;

	matrixE = matrixD.transpose();
	cout << " Transpose of matrix D" << endl;
	cout << matrixE;

	matrixF = matrixD * matrixE;
	cout << "Matrix Multiplication" << endl;
	cout << matrixF;
	
	matrixA.add(matrixB);
	cout << "Matrix Addition and update" << endl;
	cout << matrixA;

	matrixA.subtract(matrixB);
	cout << "Matrix Subtraction and update"<< endl;
	cout << matrixB;

	matrixA.multiply(4);
	cout << "Scalar Matrix Multiplication and update" << endl;
	cout << matrixA;

	if (matrixA.isSquareMatrix()) 
		cout << "matrixA is a square matrix\n";
	else
		cout << "matrix A is not a square matrix\n";


	return 0;
}
