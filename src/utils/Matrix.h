#ifndef RAYTRACER_MATRIX_H
#define RAYTRACER_MATRIX_H

#include <array>
#include <cstdlib>
#include <iostream>

template <unsigned rows, unsigned columns>
class Matrix {
private:
    std::array<float, rows * columns> data_;

public:
    Matrix()
    {
        data_.fill(0);
    }

    void fill(float value)
    {
        data_.fill(value);
    }

    void set(unsigned i, unsigned j, float value);
    float get(unsigned i, unsigned j);

    std::array<float, rows> operator*(std::array<float, columns> vector) const;

    friend std::ostream& operator<<(std::ostream& out, Matrix<rows, columns> mat);
};

template<unsigned int rows, unsigned int columns>
void Matrix<rows, columns>::set(unsigned i, unsigned j, float value) {
    if (i < 0 or j < 0 or j >= columns or i >= rows)
        throw std::invalid_argument("Matrix indexes out of bounds");
    data_[j + i * columns] = value;
}

template<unsigned int rows, unsigned int columns>
float Matrix<rows, columns>::get(unsigned i, unsigned j) {
    if (i < 0 or j < 0 or j >= columns or i >= rows)
        throw std::invalid_argument("Matrix indexes out of bounds");
    return data_[j + i * columns];
}

template<unsigned int rows, unsigned int columns>
std::array<float, rows> Matrix<rows, columns>::operator*(std::array<float, columns> vector) const {
    auto res = std::array<float, rows>();

    for (unsigned i = 0; i < rows; i++)
    {
        float acc = 0;
        for (unsigned j = 0; j < columns; j++)
        {
            acc += get(i, j) * vector[j];
        }
        res[i] = acc;
    }

    return res;
}

template <unsigned rows, unsigned columns>
std::ostream& operator<<(std::ostream& out, Matrix<rows, columns> mat)
{
    std::cout << "(";
    for (unsigned i = 0; i < rows; i++)
    {
        for (unsigned j = 0; j < columns; j++)
        {
            printf(" %5.2f", mat.get(i, j));
        }
        std::cout << "\n";
    }
    std::cout << ")";
}

using Matrix3x3 = Matrix<3, 3>;

#endif //RAYTRACER_MATRIX_H
