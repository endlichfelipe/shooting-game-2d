#include "matrix.hpp"
#include <stdexcept>
#include <sstream>

using ::math::Matrix;
using ::math::Vector;

#pragma region Constructor and Destructor
Matrix::Matrix()
{
    Allocate(0, 0);
}

Matrix::Matrix(int rows, int columns)
{
    Allocate(rows, columns);
}

Matrix::Matrix(const Matrix &other)
{
    Copy(other);
}

Matrix::~Matrix()
{
    Deallocate();
}
#pragma endregion // Constructor and Destructor

#pragma region Getters and Setters
int Matrix::get_rows() const
{
    return rows_;
}

int Matrix::get_columns() const
{
    return columns_;
}

void Matrix::set_rows(int rows)
{
    if (rows < 0)
    {
        throw std::invalid_argument("rows must be greater than or equal to 0");
    }
    if (rows != this->rows_)
    {
        Deallocate();
        Allocate(rows, columns_);
    }
}

void Matrix::set_columns(int columns)
{
    if (columns < 0)
    {
        throw std::invalid_argument("columns must be greater than or equal to 0");
    }
    if (columns != this->columns_)
    {
        Deallocate();
        Allocate(rows_, columns);
    }
}
#pragma endregion // Getters and Setters

#pragma region Operator Overloading
Matrix &Matrix::operator=(const Matrix &other)
{
    if (this != &other)
    {
        Deallocate();
        Copy(other);
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix &other)
{

    if (this->rows_ != other.rows_ || this->columns_ != other.columns_)
        throw std::invalid_argument("Dimension mismatch");

    Matrix result(this->rows_, this->columns_);

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            result[i][j] = this->values_[i][j] + other.values_[i][j];

    return result;
}

Matrix Matrix::operator-(const Matrix &other)
{
    if (this->rows_ != other.rows_ || this->columns_ != other.columns_)
        throw std::invalid_argument("Dimension mismatch");

    Matrix result(this->rows_, this->columns_);

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            result[i][j] = this->values_[i][j] - other.values_[i][j];

    return result;
}

Matrix Matrix::operator*(const Matrix &other)
{
    if (this->columns_ != other.rows_)
        throw std::invalid_argument("Dimension mismatch");

    Matrix result(this->rows_, other.columns_);

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < other.columns_; j++)
            for (int k = 0; k < this->columns_; k++)
                result[i][j] += this->values_[i][k] * other.values_[k][j];

    return result;
}

Vector Matrix::operator*(const Vector &other) const
{
    if (this->columns_ != other.get_dimension())
        throw std::invalid_argument("Dimension mismatch");

    Vector result(this->rows_);

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            result[i] += this->values_[i][j] * other[j];

    return result;
}

Matrix Matrix::operator*(const double &other)
{
    Matrix result(this->rows_, this->columns_);

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            result[i][j] = this->values_[i][j] * other;

    return result;
}

Matrix Matrix::operator/(const double &other)
{
    Matrix result(this->rows_, this->columns_);

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            result[i][j] = this->values_[i][j] / other;

    return result;
}

Matrix Matrix::operator^(const int &other)
{
    if (other < 1)
        throw std::invalid_argument("Invalid exponent");

    Matrix result(*this);

    for (int i = 1; i < other; i++)
        result = result * (*this);

    return result;
}

Matrix &Matrix::operator+=(const Matrix &other)
{
    if (this->rows_ != other.rows_ || this->columns_ != other.columns_)
        throw std::invalid_argument("Dimension mismatch");

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            this->values_[i][j] += other.values_[i][j];

    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other)
{
    if (this->rows_ != other.rows_ || this->columns_ != other.columns_)
        throw std::invalid_argument("Dimension mismatch");

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            this->values_[i][j] -= other.values_[i][j];

    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other)
{
    if (this->columns_ != other.rows_)
        throw std::invalid_argument("Dimension mismatch");

    Matrix result(this->rows_, other.columns_);

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < other.columns_; j++)
            for (int k = 0; k < this->columns_; k++)
                result[i][j] += this->values_[i][k] * other.values_[k][j];

    *this = result;

    return *this;
}

Matrix &Matrix::operator*=(const double &other)
{
    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            this->values_[i][j] *= other;

    return *this;
}

Matrix &Matrix::operator/=(const double &other)
{
    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            this->values_[i][j] /= other;

    return *this;
}

Matrix &Matrix::operator^=(const int &other)
{
    if (other < 1)
        throw std::invalid_argument("Invalid exponent");

    for (int i = 1; i < other; i++)
        *this = *this * (*this);

    return *this;
}

Vector Matrix::operator[](int i) const
{
    if (i < 0 || i >= this->rows_)
        throw std::invalid_argument("Index out of bounds");

    return this->values_[i];
}

Vector &Matrix::operator[](int i)
{
    if (i < 0 || i >= this->rows_)
        throw std::invalid_argument("Index out of bounds");

    return this->values_[i];
}
#pragma endregion // Operator Overloading

#pragma region Other Methods
Matrix Matrix::Transpose()
{
    Matrix result(this->columns_, this->rows_);

    for (int i = 0; i < this->rows_; i++)
        for (int j = 0; j < this->columns_; j++)
            result[j][i] = this->values_[i][j];

    return result;
}

std::string Matrix::to_string() const
{
    std::stringstream ss;

    for (int i = 0; i < this->rows_; i++)
    {
        for (int j = 0; j < this->columns_; j++)
            ss << this->values_[i][j] << " ";

        ss << std::endl;
    }

    return ss.str();
}
#pragma endregion // Other Methods

#pragma region Static Methods
Matrix Matrix::Zero(int rows, int columns)
{
    Matrix result(rows, columns);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            result[i][j] = 0;

    return result;
}

Matrix Matrix::Identity(int rows, int columns)
{
    Matrix result(rows, columns);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            result[i][j] = (i == j) ? 1 : 0;

    return result;
}
#pragma endregion // Static Methods

#pragma region Protected Methods
void Matrix::Allocate(int rows, int columns)
{
    this->rows_ = rows;
    this->columns_ = columns;
    this->values_.resize(rows);
    for (int i = 0; i < rows; i++)
        this->values_[i].Resize(columns);
}

void Matrix::Deallocate()
{
    this->rows_ = 0;
    this->columns_ = 0;
    this->values_.clear();
}

void Matrix::Copy(const Matrix &other)
{
    Allocate(other.rows_, other.columns_);
    for (int i = 0; i < other.rows_; i++)
        for (int j = 0; j < other.columns_; j++)
            this->values_[i][j] = other.values_[i][j];
}
#pragma endregion // Protected Methods