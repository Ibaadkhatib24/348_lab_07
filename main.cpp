#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

const int MATRIX_SIZE = 4; // matrix dimension

class Matrix
{
private:
    int elements[MATRIX_SIZE][MATRIX_SIZE]; // matrix data

public:
    // load matrix data from a file stream
    void loadFromFile(ifstream &fileStream)
    {
        for (int row = 0; row < MATRIX_SIZE; row++)
        {
            for (int col = 0; col < MATRIX_SIZE; col++)
            {
                if (!(fileStream >> elements[row][col]))
                {
                    cerr << "error: not enough or invalid data in file" << endl;
                    return;
                }
            }
        }
    }

    // display the matrix
    void display() const
    {
        for (int row = 0; row < MATRIX_SIZE; row++)
        {
            for (int col = 0; col < MATRIX_SIZE; col++)
            {
                cout << setw(4) << elements[row][col];
            }
            cout << endl;
        }
        cout << endl;
    }

    // add two matrices with operator overloading
    Matrix operator+(const Matrix &other) const
    {
        Matrix result;
        for (int row = 0; row < MATRIX_SIZE; row++)
        {
            for (int col = 0; col < MATRIX_SIZE; col++)
            {
                result.elements[row][col] = elements[row][col] + other.elements[row][col];
            }
        }
        return result;
    }

    // multiply two matrices with operator overloading
    Matrix operator*(const Matrix &other) const
    {
        Matrix result;
        for (int row = 0; row < MATRIX_SIZE; row++)
        {
            for (int col = 0; col < MATRIX_SIZE; col++)
            {
                result.elements[row][col] = 0;
                for (int k = 0; k < MATRIX_SIZE; k++)
                {
                    result.elements[row][col] += elements[row][k] * other.elements[k][col];
                }
            }
        }
        return result;
    }

    // calculate sum of main and secondary diagonals
    int calculateDiagonalSum() const
    {
        int diagonalSum = 0;
        for (int i = 0; i < MATRIX_SIZE; i++)
        {
            diagonalSum += elements[i][i]; // main diagonal
            if (i != MATRIX_SIZE - 1 - i)
            {
                diagonalSum += elements[i][MATRIX_SIZE - 1 - i]; // secondary diagonal
            }
        }
        return diagonalSum;
    }

    // swap two rows if indices are valid
    void swapRows(int firstRow, int secondRow)
    {
        if (firstRow >= 0 && firstRow < MATRIX_SIZE && secondRow >= 0 && secondRow < MATRIX_SIZE)
        {
            for (int col = 0; col < MATRIX_SIZE; col++)
            {
                int temp = elements[firstRow][col];
                elements[firstRow][col] = elements[secondRow][col];
                elements[secondRow][col] = temp;
            }
        }
        else
        {
            cout << "error: invalid row indices for swapping" << endl;
        }
    }
};

int main()
{
    ifstream inputFile("matrix-data.txt");
    if (!inputFile)
    {
        cerr << "error: unable to open matrix-data.txt" << endl;
        return 1;
    }

    Matrix matrix1, matrix2;

    // load and display the first matrix
    matrix1.loadFromFile(inputFile);
    cout << "matrix 1:" << endl;
    matrix1.display();

    // load and display the second matrix
    matrix2.loadFromFile(inputFile);
    cout << "matrix 2:" << endl;
    matrix2.display();

    // add matrices and display the result
    Matrix sumMatrix = matrix1 + matrix2;
    cout << "sum of matrix 1 and matrix 2:" << endl;
    sumMatrix.display();

    // multiply matrices and display the result
    Matrix productMatrix = matrix1 * matrix2;
    cout << "product of matrix 1 and matrix 2:" << endl;
    productMatrix.display();

    // display the sum of diagonals of the first matrix
    cout << "diagonal sum of matrix 1: " << matrix1.calculateDiagonalSum() << endl;

    // swap rows and display the modified matrix
    matrix1.swapRows(0, 2);
    cout << "matrix 1 after swapping row 0 with row 2:" << endl;
    matrix1.display();

    return 0;
}
