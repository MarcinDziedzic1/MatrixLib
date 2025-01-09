#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <cmath>

// Matrix Class - base for all matrices
class Matrix
{
public:
    // General constructor
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols)
    {
        data.resize(rows, std::vector<double>(cols, 0));
    }

    // Constructor with data vector
    Matrix(const std::vector<std::vector<double>> &values)
        : data(values), rows(values.size()), cols(values[0].size()) {}

    // Access to matrix elements
    double &operator()(size_t i, size_t j)
    {
        return data[i][j];
    }

    const double operator()(size_t i, size_t j) const
    {
        return data[i][j];
    }

    // Addition operation
    Matrix operator+(const Matrix &other) const
    {
        if (rows != other.rows || cols != other.cols)
            throw std::invalid_argument("Matrix dimensions must be the same!");
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result(i, j) = data[i][j] + other(i, j);
            }
        }
        return result;
    }

    // Subtraction operation
    Matrix operator-(const Matrix &other) const
    {
        if (rows != other.rows || cols != other.cols)
            throw std::invalid_argument("Matrix dimensions must be the same!");
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result(i, j) = data[i][j] - other(i, j);
            }
        }
        return result;
    }

    // Multiplication operation
    Matrix operator*(const Matrix &other) const
    {
        if (cols != other.rows)
            throw std::invalid_argument("Invalid matrix dimensions for multiplication!");
        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < other.cols; ++j)
            {
                for (size_t k = 0; k < cols; ++k)
                {
                    result(i, j) += data[i][k] * other(k, j);
                }
            }
        }
        return result;
    }

    // Scalar multiplication operation
    Matrix operator*(double scalar) const
    {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result(i, j) = data[i][j] * scalar;
            }
        }
        return result;
    }

    // Friend function for scalar * Matrix multiplication
    friend Matrix operator*(double scalar, const Matrix &matrix)
    {
        return matrix * scalar;
    }

    // Division by matrix (through multiplication by inverse)
    Matrix operator/(const Matrix &other) const
    {
        Matrix inverse = other.inverse();
        return (*this) * inverse;
    }

    // Matrix transpose
    Matrix transpose() const
    {
        Matrix result(cols, rows);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result(j, i) = data[i][j];
            }
        }
        return result;
    }

    // Function to calculate determinant (recursively)
    double determinant() const
    {
        if (rows != cols)
            throw std::invalid_argument("Determinant can only be calculated for square matrices!");
        if (rows == 1)
            return data[0][0];
        if (rows == 2)
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];

        double det = 0;
        for (size_t p = 0; p < cols; ++p)
        {
            Matrix subMatrix(rows - 1, cols - 1);
            for (size_t i = 1; i < rows; ++i)
            {
                size_t colIndex = 0;
                for (size_t j = 0; j < cols; ++j)
                {
                    if (j == p)
                        continue;
                    subMatrix(i - 1, colIndex++) = data[i][j];
                }
            }
            det += data[0][p] * subMatrix.determinant() * (p % 2 == 0 ? 1 : -1);
        }
        return det;
    }

    // Matrix inversion
    Matrix inverse() const
    {
        double det = determinant();
        if (det == 0)
            throw std::runtime_error("Matrix is non-invertible (determinant is zero)!");
        if (rows != cols)
            throw std::invalid_argument("Inversion is only possible for square matrices!");

        Matrix adj(rows, cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                Matrix subMatrix(rows - 1, cols - 1);
                for (size_t sub_i = 0, mat_i = 0; mat_i < rows; ++mat_i)
                {
                    if (mat_i == i)
                        continue;
                    for (size_t sub_j = 0, mat_j = 0; mat_j < cols; ++mat_j)
                    {
                        if (mat_j == j)
                            continue;
                        subMatrix(sub_i, sub_j++) = data[mat_i][mat_j];
                    }
                    ++sub_i;
                }
                adj(j, i) = subMatrix.determinant() * ((i + j) % 2 == 0 ? 1 : -1);
            }
        }
        return adj * (1 / det);
    }

    // Adding rows/columns
    void addRow(const std::vector<double> &newRow, bool atBottom = true)
    {
        if (newRow.size() != cols)
            throw std::invalid_argument("New row must have the same number of columns as the matrix!");
        if (atBottom)
            data.push_back(newRow);
        else
            data.insert(data.begin(), newRow);
        ++rows;
    }

    void addColumn(const std::vector<double> &newColumn, bool atRight = true)
    {
        if (newColumn.size() != rows)
            throw std::invalid_argument("New column must have the same number of rows as the matrix!");
        for (size_t i = 0; i < rows; ++i)
        {
            if (atRight)
                data[i].push_back(newColumn[i]);
            else
                data[i].insert(data[i].begin(), newColumn[i]);
        }
        ++cols;
    }

    // Removing rows/columns
    void removeRow(bool fromBottom = true)
    {
        if (rows == 0)
            throw std::invalid_argument("Cannot remove a row from an empty matrix!");
        if (fromBottom)
            data.pop_back();
        else
            data.erase(data.begin());
        --rows;
    }

    void removeColumn(bool fromRight = true)
    {
        if (cols == 0)
            throw std::invalid_argument("Cannot remove a column from an empty matrix!");
        for (size_t i = 0; i < rows; ++i)
        {
            if (fromRight)
                data[i].pop_back();
            else
                data[i].erase(data[i].begin());
        }
        --cols;
    }

    // Displaying the matrix
    void print() const
    {
        for (const auto &row : data)
        {
            for (const auto &val : row)
            {
                std::cout << std::setw(10) << val << " ";
            }
            std::cout << "\n";
        }
    }

protected:
    std::vector<std::vector<double>> data;
    size_t rows, cols;
};

// SquareMatrix Class (square matrix)
class SquareMatrix : public Matrix
{
public:
    // Constructor accepting the size of the matrix
    SquareMatrix(size_t size) : Matrix(size, size) {}

    // Overloading the assignment operator to assign a value to all elements of the matrix
    SquareMatrix &operator=(double value)
    {
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                data[i][j] = value;
            }
        }
        return *this;
    }
};

// SquareMatrixIdentity Class (identity matrix)
class SquareMatrixIdentity : public SquareMatrix
{
public:
    SquareMatrixIdentity(size_t size) : SquareMatrix(size)
    {
        for (size_t i = 0; i < size; ++i)
            data[i][i] = 1.0;
    }
};
