#include <iostream>
#include <string>

using namespace std;

#include "matrix.h"

TwoDimensionMatrix::TwoDimensionMatrix()
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
            matrix[i][j] = 0;
    }
}
TwoDimensionMatrix::TwoDimensionMatrix(const TwoDimensionMatrix &imput_matrix)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
            matrix[i][j] = imput_matrix.matrix[i][j];
    }
}

TwoDimensionMatrix::TwoDimensionMatrix(const MatrixElement matrix_[size][size])
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
            matrix[i][j] = matrix_[i][j];
    }
}

// ------------------------

MatrixElement TwoDimensionMatrix::get(const size_t row, const size_t column) const
{
    return matrix[row][column];
}

// ------------------------

TwoDimensionMatrix &TwoDimensionMatrix::operator=(const TwoDimensionMatrix &imput_matrix)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
            matrix[i][j] = imput_matrix.matrix[i][j];
    }
    return *this;
}

std::istream &operator>>(std::istream &input, TwoDimensionMatrix &input_matrix)
{
    for (size_t i = 0; i < TwoDimensionMatrix::size; i++)
    {
        for (size_t j = 0; j < TwoDimensionMatrix::size; j++)
            input >> input_matrix.matrix[i][j];
    }
    return input;
}

std::ostream &operator<<(std::ostream &output, const TwoDimensionMatrix &input_matrix)
{
    for (size_t i = 0; i < TwoDimensionMatrix::size; i++)
    {
        for (size_t j = 0; j < TwoDimensionMatrix::size; j++)
            output << input_matrix.matrix[i][j];
    }
    return output;
}

TwoDimensionMatrix operator+(const TwoDimensionMatrix &matrix1, const TwoDimensionMatrix &matrix2)
{
    TwoDimensionMatrix result;
    for (size_t i = 0; i < TwoDimensionMatrix::size; i++)
    {
        for (size_t j = 0; j < TwoDimensionMatrix::size; j++)
            result.matrix[i][j] = matrix1.matrix[i][j] + matrix2.matrix[i][j];
    }
    return result;
}

TwoDimensionMatrix &TwoDimensionMatrix::operator*=(const MatrixElement number)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
            matrix[i][j] *= number;
    }
    return *this;
}
TwoDimensionMatrix TwoDimensionMatrix::operator&&(const TwoDimensionMatrix &matrix_) const
{
    TwoDimensionMatrix result;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
            result.matrix[i][j] = matrix[i][j] && matrix_.matrix[i][j];
    }
    return result;
}
MatrixElement *TwoDimensionMatrix::operator[](const size_t i)
{
    return matrix[i];
}

const MatrixElement *TwoDimensionMatrix::operator[](const size_t i) const
{
    return matrix[i];
}

TwoDimensionMatrix::operator size_t() const
{
    return size;
}