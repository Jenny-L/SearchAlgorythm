//
// Created by Jenny Ly on 2018-10-05.
//

#include "matrix.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>

const double TOLERENCE = 0.001;

using namespace std;

matrix::matrix() : sideRow(DEFAULTSIZE), sideColumn(DEFAULTSIZE), matrixSize(DEFAULTSIZE * DEFAULTSIZE), matrixArray(new double[matrixSize]) {
    this->matrixArray[0] = 0.0;
}

matrix::matrix(int input) : sideRow(input), sideColumn(input), matrixSize(input * input)  {
    if (input <= 0) {
        throw invalid_argument("input side length is a negative integer");
    } else {
        matrixArray = new double[matrixSize];
    }
    for(int i = 0; i < matrixSize; i++) {
        this->matrixArray[i] = 0.0;
    }
}

matrix::matrix(int r, int c) : sideRow(r), sideColumn(c), matrixSize(r * c)  {
    if (r <= 0 || c <= 0) {
        throw invalid_argument("input r or c  is a negative integer");
    } else {
        matrixArray = new double[matrixSize];
    }
    for(int i = 0; i < matrixSize; i++) {
        this->matrixArray[i] = 0.0;
    }
}

matrix::matrix(vector<double> arrayValues) {
    int arraySize = arrayValues.size();
    int sqrtArraySize = sqrt(arraySize);
    sideRow = sqrtArraySize;
    sideColumn = sqrtArraySize;
    matrixSize = sideRow * sideColumn;
    if (sqrtArraySize * sqrtArraySize != arraySize) {
    throw invalid_argument("input array is not a perfect square");
    } else {
    matrixArray = new double[matrixSize];
    }
    for(int i = 0; i < arraySize; i++) {
    this->matrixArray[i] = arrayValues[i];
    }
}

matrix::matrix(const matrix& m): sideColumn(m.sideColumn), sideRow(m.sideRow), matrixSize(m.sideColumn * m.sideRow), matrixArray(new double[matrixSize]){
    for (int i = 0; i < m.matrixSize; i++) {
        this->matrixArray[i] = m.matrixArray[i];
    }
}

matrix::~matrix() {delete[] matrixArray;}

void matrix::set_value(int x, int y, double value) {
    if (x >= sideRow || x < 0) {
        throw invalid_argument("input x contains an invalid value");
    }
    if (y >= sideColumn || y < 0) {
        throw invalid_argument("input y contains an invalid value");
    }
    matrixArray[x * sideRow + y] = value;
}

const double matrix::get_value(int x, int y) {
    if (x >= sideRow || x < 0) {
        throw invalid_argument("input x contains an invalid value");
    }
    if (y >= sideColumn || y < 0) {
        throw invalid_argument("input y contains an invalid value");
    }
    return matrixArray[x * sideRow + y];
}


void matrix::clear() {
    for(int i = 0; i < matrixSize; i++) {
        matrixArray[i] = 0.0;
    }
}

std::ostream& operator<<(std::ostream& os, matrix& obj){
    double objValue;
    int rowSize = obj.get_row_size();
    int columnSize = obj.get_column_size();
    for(int i = 0; i < rowSize; i++) {
        for(int j = 0; j < columnSize; j++) {



            objValue = obj.get_value(i, j);
            os << fixed << setprecision(4) << objValue << " ";
            if ((j + 1) % rowSize == 0) {
                os << endl;
            }
        }
    }
    return os;
}

bool operator==(const matrix& m1, const matrix& m2) {
    if(m1.matrixSize != m2.matrixSize) {
        return false;
    }
    for (int i = 0; i < m1.matrixSize; i++) {
        if (!(m1.matrixArray[i] < m2.matrixArray[i] + TOLERENCE && m1.matrixArray[i] > m2.matrixArray[i] - TOLERENCE)){
            return false;
        }
    }
    return true;
}

bool operator!=(const matrix& m1, const matrix& m2) {
    return !operator==(m1,m2);
}

bool operator<(const matrix& m1, const matrix& m2) {
   return (m1.matrixSize < m2.matrixSize);
}

bool operator>(const matrix& m1, const matrix& m2) {
    return  (m2.matrixSize < m1.matrixSize);
}

bool operator<=(const matrix& m1, const matrix& m2) {
    return !operator>(m1.matrixSize, m2.matrixSize);
}

bool operator>=(const matrix&m1, const matrix& m2) {
    return !operator<(m1.matrixSize, m2.matrixSize);
}

//Prefix
matrix& matrix::operator++(){
    for (int i = 0; i < this->matrixSize; i++) {
        this->matrixArray[i] = this->matrixArray[i] + 1.0;
    }
    return *this;
}

//Postfix
matrix matrix::operator++(int) {
    matrix temp(*this);
    operator++();
    return temp;
}

//Prefix
matrix& matrix::operator--(){
    for (int i = 0; i < this->matrixSize; i++) {
        this->matrixArray[i] = this->matrixArray[i] - 1.0;
    }
    return *this;
}

//Postfix
matrix matrix::operator--(int) {
    matrix temp(*this);
    operator--();
    return temp;
}



matrix& matrix::operator+=(const matrix& m1) {
    if (this->matrixSize != m1.matrixSize) {
        throw invalid_argument("Cannot add matrices because their size are different");
    }
    for (int i = 0; i < m1.matrixSize; i++) {
        this->matrixArray[i] = this->matrixArray[i] + m1.matrixArray[i];
    }
    return *this;
}

matrix operator+(matrix m1, const matrix& m2) {
    m1 += m2;
    return m1;
}

matrix& matrix::operator-=(const matrix& m1) {
    if (this->matrixSize != m1.matrixSize) {
        throw invalid_argument("Cannot subtract matrices because their size are different");
    }
    for (int i = 0; i < m1.matrixSize; i++) {
        this->matrixArray[i] = this->matrixArray[i] - m1.matrixArray[i];
    }
    return *this;
}

matrix operator-(matrix m1, const matrix& m2) {
    m1 += m2;
    return m1;
}

//swap and assign
matrix& matrix::operator=(matrix &m) {
    swap(*this, m);
    return *this;
}

void swap(matrix &m1, matrix &m2) {
    matrix temp;
    temp = m1;
    m1 = m2;
    m2 = temp;
}

matrix& matrix::operator*=(matrix &m1) {
    int nRows = this->sideRow;
    int nColumn = m1.sideColumn;
    int commonSize = this->sideRow;
    if (this->sideColumn != m1.sideRow ) {
        throw invalid_argument("column length of matrix 1 does != row length of matrix 2");
    }
    for(int i = 0; i < nRows; i++) {
        for(int j = 0; j < nColumn; j++) {
            int product = 0;
            for(int k = 0; k < commonSize; k++) {
                product += this->get_value(i, k) * m1.get_value(k, j);
            }
            this->set_value(i, j, product);
        }
    }
    return *this;
}

matrix operator*(matrix result, matrix &m) {
    result *= m;
    return result;
}

double* matrix::get_matrix() {
    return matrixArray;
}

int matrix::get_row_size() const {
    return sideRow;
}

int matrix::get_column_size() const {
    return sideColumn;
}

vector<double> matrix::row_sum_vector() {
    vector<double> sum_container;
    for (int x = 0; x < get_row_size(); x++) {

        int sum = 0;
        for(int y = 0; y < get_column_size(); y++) {
            sum += get_value(x, y);
            //cout << "x = " << x << "y = " << y << endl;
        }
        sum_container.push_back(sum);
        //cout << "column sum " << sum << endl;
    }
    return sum_container;
}







