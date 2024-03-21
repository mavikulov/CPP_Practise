#pragma once

#include <vector>
#include <stddef.h>

class Matrix {
private:
    std::vector<std::vector<double>> data_;
    size_t rows_, cols_;

public:
    Matrix(size_t rows, size_t columns) : rows_(rows), cols_(columns) {
        for (size_t i = 0; i < rows_; ++i) {
            data_.push_back(std::vector<double>(cols_, 0.0));
        }
    }
    explicit Matrix(size_t rows) : rows_(rows), cols_(rows) {
        for (size_t i = 0; i < rows_; ++i) {
            data_.push_back(std::vector<double>(rows_, 0));
        }
    }
    Matrix(const std::vector<std::vector<double>>& other)
        : rows_(other.size()), cols_(other[0].size()) {
        for (size_t i = 0; i < rows_; i++) {
            data_.push_back(other[i]);
        }
    }
    size_t Rows() const {
        return rows_;
    }
    size_t Columns() const {
        return cols_;
    }
    double& operator()(size_t row, size_t column) {
        return data_[row][column];
    }
    const double& operator()(size_t row, size_t column) const {
        return data_[row][column];
    }
    Matrix operator+(const Matrix& second) const {
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_; i++) {
            for (size_t j = 0; j < cols_; j++) {
                result(i, j) = data_[i][j] + second(i, j);
            }
        }
        return result;
    }
    Matrix operator-(const Matrix& second) const {
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_; i++) {
            for (size_t j = 0; j < cols_; j++) {
                result(i, j) = data_[i][j] - second(i, j);
            }
        }
        return result;
    }
    Matrix operator*(const Matrix& second) const {
        Matrix result(rows_, second.cols_);
        for (size_t i = 0; i < second.cols_; i++) {
            for (size_t j = 0; j < rows_; j++) {
                for (size_t k = 0; k < cols_; k++) {
                    result(i, j) += data_[i][k] * second(k, j);
                }
            }
        }
        return result;
    }
    Matrix& operator+=(const Matrix& second) {
        *this = *this + second;
        return *this;
    }
    Matrix& operator-=(const Matrix& second) {
        *this = *this - second;
        return *this;
    }
    Matrix& operator*=(const Matrix& second) {
        *this = *this * second;
        return *this;
    }

    friend Matrix Transpose(const Matrix& second) {
        Matrix result(second.Columns(), second.Rows());
        for (size_t i = 0; i < second.Rows(); i++) {
            for (size_t j = 0; j < second.Columns(); j++) {
                result(j, i) = second(i, j);
            }
        }
        return result;
    }
};

Matrix Identity(size_t rows) {
    Matrix identity(rows);
    for (size_t i = 0; i < rows; i++) {
        identity(i, i) = 1;
    }
    return identity;
}
