#pragma once
#include <cmath>
#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include "SVector.hh"

template <typename Type, int Size> class SMatrix {
private:
  Type value[Size][Size];

public:
  SMatrix();
  SMatrix(Type[Size][Size]); // Class constructor
  
  SMatrix(std::initializer_list<std::initializer_list<Type>> list) {
      if (list.size() > Size) {
          throw std::out_of_range("Initializer list size exceeds SMatrix row bounds");
      }
      size_t i = 0;
      for (const auto& row : list) {
          if (row.size() > Size) {
              throw std::out_of_range("Initializer list size exceeds SMatrix column bounds");
          }
          size_t j = 0;
          for (const auto& elem : row) {
              value[i][j++] = elem;
          }
          for (; j < Size; ++j) {
              value[i][j] = Type{};
          }
          ++i;
      }
      for (; i < Size; ++i) {
          for (size_t j = 0; j < Size; ++j) {
              value[i][j] = Type{};
          }
      }
  }

  SVector<Type, Size> operator*(SVector<Type, Size> tmp); // Operator for multiplication by vector
  SMatrix<Type, Size> operator*(SMatrix<Type, Size> tmp); // Operator for multiplication by matrix
  SMatrix<Type, Size> operator+(SMatrix<Type, Size> tmp); // Operator for addition of matrices

  SMatrix<Type, Size> Transpose(); // Transposes matrix
  Type Gauss(); // Calculates determinant using Gaussian elimination

  SMatrix<Type, Size> ColumnChange(int column, SVector<Type, Size> vec); // Replaces a column
  SMatrix<Type, Size> RowChange(int row1, int row2); // Swaps two rows
  SMatrix<Type, Size> Changing(int row); // Swaps appropriate rows using RowChange()

  SVector<Type, Size> Equation(SMatrix<Type, Size> A, SVector<Type, Size> B); // Solves system of linear equations
  SMatrix<Type, Size> SwapColumns(unsigned int column);
  SMatrix<Type, Size> ZeroColumn(unsigned int column);

  Type CheckIf0() const; // Checks if it is a triangular matrix
  Type &operator()(unsigned int row, unsigned int column);
  const Type &operator()(unsigned int row, unsigned int column) const;

  SVector<Type, Size> ErrorVector(SMatrix<Type, Size> A, SVector<Type, Size> X, SVector<Type, Size> B); // Calculates error vector

  Vector3D rotateX(Vector3D v, double theta);
};

typedef SMatrix<double, 3> Matrix3D; 

/******************************************************************************
 |  Overload of operator <<                                                   |
 |  Arguments:                                                                |
 |      out - output stream,                                                  |
 |      mat - matrix.                                                         |
 */
template <typename Type, int Size>
std::ostream &operator<<(std::ostream &out, const SMatrix<Type, Size> &mat) {
  for (int i = 0; i < Size; ++i) {
    for (int j = 0; j < Size; ++j) {
      out << "| " << mat(i, j) << " | ";
    }
    std::cout << std::endl;
  }
  return out;
}

/******************************************************************************
 |  Overload of operator >>                                                   |
 |  Arguments:                                                                |
 |      in - input stream,                                                    |
 |      mat - matrix.                                                         |
 */
template <typename Type, int Size>
std::istream &operator>>(std::istream &in, SMatrix<Type, Size> &mat) {
  for (int i = 0; i < Size; ++i) {
    for (int j = 0; j < Size; ++j) {
      in >> mat(i, j);
    }
  }
  return in;
}

template <typename Type, int Size>
Type &SMatrix<Type, Size>::operator()(unsigned int row, unsigned int column) {
  if (row >= Size) {
    std::cout << "Error: Matrix index out of range";
    exit(0);
  }
  if (column >= Size) {
    std::cout << "Error: Matrix index out of range";
    exit(0);
  }
  return value[row][column];
}

/******************************************************************************
 |  Matrix functor (const)                                                    |
 |  Arguments:                                                                |
 |      row - row index,                                                      |
 |      column - column index.                                                |
 |  Returns:                                                                  |
 |      Value of matrix at the specified position as a constant.              |
 */
template <typename Type, int Size>
const Type &SMatrix<Type, Size>::operator()(unsigned int row,
                                            unsigned int column) const {
  if (row >= Size) {
    std::cout << "Error: Matrix index out of range";
    exit(0);
  }
  if (column >= Size) {
    std::cout << "Error: Matrix index out of range";
    exit(0);
  }
  return value[row][column];
}

/******************************************************************************
 |  Constructor of Matrix class.                                              |
 |  Returns:                                                                  |
 |      Matrix initialized to 0.                                              |
 */
template <typename Type, int Size> SMatrix<Type, Size>::SMatrix() {
  for (int i = 0; i < Size; ++i) {
    for (int j = 0; j < Size; ++j) {
      value[i][j] = 0;
    }
  }
}

/******************************************************************************
 |  Parameterized constructor of Matrix class.                                |
 |  Arguments:                                                                |
 |      tmp - two-dimensional array of elements.                              |
 |  Returns:                                                                  |
 |      Matrix initialized with values from the array.                        |
 */
template <typename Type, int Size>
SMatrix<Type, Size>::SMatrix(Type tmp[Size][Size]) {
  for (int i = 0; i < Size; ++i) {
    for (int j = 0; j < Size; ++j) {
      value[i][j] = tmp[i][j];
    }
  }
}

/******************************************************************************
 |  Transposes the matrix.                                                    |
 |  Returns:                                                                  |
 |      The transposed matrix.                                                |
 */
template <typename Type, int Size>
SMatrix<Type, Size> SMatrix<Type, Size>::Transpose() {
  SMatrix<Type, Size> result;
  for (int i = 0; i < Size; ++i) {
    for (int j = 0; j < Size; ++j) {
      result(i, j) = value[j][i];
    }
  }
  return result;
}

/******************************************************************************
 |  Multiplies matrix by vector.                                              |
 |  Arguments:                                                                |
 |      tmp - vector.                                                         |
 |  Returns:                                                                  |
 |      Product of matrix and vector.                                         |
 */
template <typename Type, int Size>
SVector<Type, Size> SMatrix<Type, Size>::operator*(SVector<Type, Size> tmp) {
  SVector<Type, Size> result;
  for (int i = 0; i < Size; ++i) {
    for (int j = 0; j < Size; ++j) {
      result[i] += value[i][j] * tmp[j];
    }
  }
  return result;
}

/******************************************************************************
 |  Multiplies matrix by matrix.                                              |
 |  Arguments:                                                                |
 |      tmp - second matrix.                                                  |
 |  Returns:                                                                  |
 |      Product of the two matrices.                                          |
 */
template <typename Type, int Size>
SMatrix<Type, Size> SMatrix<Type, Size>::operator*(SMatrix<Type, Size> tmp) {
  SMatrix<Type, Size> result;
  for (int i = 0; i < Size; ++i)
    for (int j = 0; j < Size; ++j)
      for (int k = 0; k < Size; ++k) {
        result(i, j) += value[i][k] * tmp(k, j);
      }
  return result;
}

/******************************************************************************
 |  Adds two matrices.                                                        |
 |  Arguments:                                                                |
 |      tmp - second matrix.                                                  |
 |  Returns:                                                                  |
 |      Sum of the two matrices.                                              |
 */
template <typename Type, int Size>
SMatrix<Type, Size> SMatrix<Type, Size>::operator+(SMatrix<Type, Size> tmp) {
  SMatrix<Type, Size> result;
  for (int i = 0; i < Size; ++i) {
    for (int j = 0; j < Size; ++j) {
      result(i, j) = value[i][j] + tmp(i, j);
    }
  }
  return result;
}

/******************************************************************************
 |  Calculates determinant using Gaussian elimination.                        |
 |  Returns:                                                                  |
 |      Value of the determinant.                                             |
 */
template <typename Type, int Size> Type SMatrix<Type, Size>::Gauss() {
  Type det;
  int parity = 1;

  for (int i = 0; i < Size; ++i) {
    CheckIf0();
    if (value[i][i] == 0) {
      parity = -parity;
      SwapColumns(i);
      ZeroColumn(i);
    }
    ZeroColumn(i);
  }

  det = value[0][0];
  for (int i = 1; i < Size; ++i) {
    det = det * value[i][i];
  }
  det = det * parity;
  return det;
}

/******************************************************************************
 |  Replaces a column with a vector.                                          |
 |  Arguments:                                                                |
 |      column - index of the column to replace                               |
 |      vec - the vector to replace it with                                   |
 */
template <typename Type, int Size>
SMatrix<Type, Size> SMatrix<Type, Size>::ColumnChange(int column,
                                                      SVector<Type, Size> vec) {
  for (int i = 0; i < Size; ++i) {
    value[i][column - 1] = vec[i];
  }
  return value;
}

/******************************************************************************
 |  Swaps two rows.                                                           |
 |  Arguments:                                                                |
 |      row1 - first row,                                                     |
 |      row2 - second row.                                                    |
 */
template <typename Type, int Size>
SMatrix<Type, Size> SMatrix<Type, Size>::RowChange(int row1, int row2) {
  SMatrix<Type, Size> result;
  int changes = 0, minus = -1;

  for (int i = 0; i < Size; ++i) {
    for (int j = 0; j < Size; ++j) {
      result(i, j) = value[i][j];
    }
  }

  if (result(row2, 0) == 0 || result(row2, 1) == 0 || result(row2, 2) == 0) {
    for (int j = 0; j < Size; ++j) {
      minus = -1;
      ++changes;
      if (changes % 2 == 0)
        minus = 1;

      result(row2, j) = value[row1][j];
      result(row1, j) = value[row2][j];
    }

    for (int j = 0; j < Size; ++j) {
      result(row2, j) = minus * result(row2, j);
    }
  }

  return result;
}

/******************************************************************************
 |  Solves system of linear equations AX=B.                                   |
 |  Arguments:                                                                |
 |      A - coefficient matrix,                                               |
 |      B - constant terms vector.                                            |
 |  Returns:                                                                  |
 |      The solutions vector X.                                               |
 */
template <typename Type, int Size>
SVector<Type, Size> SMatrix<Type, Size>::Equation(SMatrix<Type, Size> A, SVector<Type, Size> B) {
  SVector<Type, Size> solutions;

  std::cout << "A and B of equation (AX=B) are represented by: " << std::endl;
  std::cout << "A: " << std::endl;
  std::cout << A << std::endl;
  std::cout << "B: " << std::endl;
  std::cout << B << std::endl;

  SMatrix<Type, Size> tmpA = A;
  Type W = A.Gauss();
  Type determinants[Size];

  for (int i = 1; i <= Size; ++i) {
    A = tmpA;
    A.ColumnChange(i, B);
    determinants[i - 1] = A.Gauss();
    solutions[i - 1] = determinants[i - 1] / W;
  }

  std::cout << "Solutions: " << std::endl;
  std::cout << solutions << std::endl;
  ErrorVector(tmpA, solutions, B);

  return solutions;
}

/******************************************************************************
 |  Swaps a column with a non-zero element on the right if the current        |
 |  element at position (column, column) is zero.                            |
 */
template <typename Type, int Size>
SMatrix<Type, Size> SMatrix<Type, Size>::SwapColumns(unsigned int column) {
  Type tmp[Size];

  for (int k = column + 1; k < Size; ++k) {
    if (value[column][k] == 0) {
      for (int j = 0; j < Size; ++j) {
        tmp[j] = value[j][k];
        value[j][k] = value[j][column];
        value[j][column] = tmp[j];
      }
    }
  }

  return value;
}

/******************************************************************************
 |  Zeroes out elements to the right of column position during elimination.    |
 */
template <typename Type, int Size>
SMatrix<Type, Size> SMatrix<Type, Size>::ZeroColumn(unsigned int column) {
  Type factor;

  for (int k = column + 1; k < Size; ++k) {
    factor = (value[column][k] / value[column][column]);
    for (int j = 0; j < Size; ++j) {
      value[j][k] = value[j][k] - value[j][column] * factor;
    }
  }

  return value;
}

/******************************************************************************
 |  Checks if the matrix is a triangular matrix.                              |
 */
template <typename Type, int Size> Type SMatrix<Type, Size>::CheckIf0() const {
  int i = 0, j = 0, k = 0, result = 1;
  Type det;

  for (i = 0; i < Size - 1; ++i) {
    for (j = Size - 1 - k; j >= 0; --j) {
      if (value[i][j] == 0) {
        result = 1;
      } else
        result = 0;
    }
    ++k;
  }

  det = value[Size - 1][Size - 1];
  if (result == 1) {
    for (i = Size - 2; i >= 0; --i) {
      det *= value[i][i];
    }
  }

  return det;
}

/******************************************************************************
 |  Calculates the error vector.                                              |
 |  Arguments:                                                                |
 |      A - coefficient matrix,                                               |
 |      X - solutions vector,                                                 |
 |      B - constant terms vector.                                            |
 */
template <typename Type, int Size>
SVector<Type, Size> SMatrix<Type, Size>::ErrorVector(SMatrix<Type, Size> A, SVector<Type, Size> X, SVector<Type, Size> B) {
  SVector<Type, Size> result;
  result = (A * X) - B;

  std::cout << "Error vector: " << std::endl;
  std::cout << result << std::endl;
  return result;
}
