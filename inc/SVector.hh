#pragma once
#include <iostream>
#define DIFF 0.01

template <typename Type, int Size>
class SVector {
  private:
    Type  size[Size];
    static int quantity;
  public:
    typedef SVector<double, 3> Vector3D; 

    SVector() { for (Type &Wsp: size) Wsp = 0; }
    SVector(Type [Size]);
    
    Type  operator [] (unsigned int Ind) const { return size[Ind]; }
    Type &operator [] (unsigned int Ind)       { return size[Ind]; }

    SVector<Type,Size> operator - (const SVector<Type,Size> &subtrahend) const;
    SVector<Type,Size> operator * (double multiplier) const;
    SVector<Type,Size> operator + (const SVector<Type,Size> &v);
    SVector<Type,Size> operator / (const double &tmp);
    bool operator == (const  SVector<Type,Size> tmp) const;
    SVector<Type,Size> operator * (SVector<Type,Size> Vector2) const; // Cross product
    Type return_x() { return size[0]; }
    Type return_y() { return size[1]; }
};

typedef SVector<double, 3> Vector3D; 
typedef SVector<double, 2> Vector2D; 

/******************************************************************************
 |  Subtractor of two vectors.                                                |
 |  Arguments:                                                                |
 |      this - first subtraction operand,                                     |
 |      subtrahend - second subtraction operand.                              |
 |  Returns:                                                                  |
 |      The difference of the two vectors.                                    |
 */
template <typename Type, int Size>
SVector<Type,Size> SVector<Type,Size>::operator - (const SVector<Type,Size> &subtrahend) const
{
  SVector<Type,Size>  Result;
  for (unsigned int Ind = 0; Ind < Size; ++Ind) Result[Ind] = (*this)[Ind] - subtrahend[Ind];
  return Result;
}

/******************************************************************************
 |  Multiplies vector by scalar.                                              |
 |  Arguments:                                                                |
 |      this - first multiplication operand (vector),                         |
 |      multiplier - second multiplication operand (double).                  |
 |  Returns:                                                                  |
 |      Product of the vector and scalar.                                     |
 */
template <typename Type, int Size>
SVector<Type,Size> SVector<Type,Size>::operator * (double multiplier) const
{
  SVector<Type,Size>  Result;
  for (unsigned int Ind = 0; Ind < Size; ++Ind) Result[Ind] = (*this)[Ind] * multiplier;
  return Result;  
}

/******************************************************************************
 |  Constructor of SVector class.                                             |
 |  Arguments:                                                                |
 |      tmp - One-dimensional array of Type elements.                         |
 |  Returns:                                                                  |
 |      An SVector initialized with elements from the array.                  |
 */
template <typename Type, int Size>
SVector<Type, Size>::SVector(Type tmp[Size]) {
  for (int i = 0; i < Size; ++i) {
    size[i] = tmp[i];
  }
}

/******************************************************************************
 |  Overload of operator <<                                                   |
 |  Arguments:                                                                |
 |      out - output stream,                                                  |
 |      tmp - vector.                                                         |
 */
template <typename Type, int Size>
std::ostream &operator<<(std::ostream &out, const SVector<Type,Size> &tmp) {
  for (int i = 0; i < Size; ++i) {
    out << "[ " << tmp[i] << " ]\n";
  }
  return out;
}

/******************************************************************************
 |  Overload of operator >>                                                   |
 |  Arguments:                                                                |
 |      in - input stream,                                                    |
 |      tmp - vector.                                                         |
 */
template <typename Type, int Size>
std::istream &operator>>(std::istream &in, SVector<Type,Size> &tmp) {
  for (int i = 0; i < Size; ++i) {
    in >> tmp[i];
  }
  std::cout << std::endl;
  return in;
}

/******************************************************************************
 |  Overload of equality comparison operator.                                 |
 */
template <typename Type, int Size>
bool SVector<Type,Size>::operator == (const  SVector<Type,Size> tmp) const {
  for(int i = 0; i < Size; ++i){
    if(abs(size[i] - tmp[i]) >= DIFF)
      return 0;
  }
  return 1;
}

/******************************************************************************
 |  Adds two vectors.                                                         |
 |  Arguments:                                                                |
 |      this - first addition operand,                                        |
 |      v - second addition operand.                                          |
 |  Returns:                                                                  |
 |      Sum of the two vectors.                                               |
 */
template <typename Type, int Size>
SVector<Type,Size> SVector<Type,Size>::operator + (const SVector<Type,Size> &v) {
  SVector<Type,Size> result;
  for (int i = 0; i < Size; ++i) {
    result[i] = size[i] + v[i];
  }
  return result;
}

/******************************************************************************
 |  Divides vector by a scalar.                                               |
 |  Arguments:                                                                |
 |      this - numerator,                                                     |
 |      tmp - denominator (scalar).                                           |
 |  Returns:                                                                  |
 |      The quotient of vector divided by scalar.                             |
 */
template <typename Type, int Size>
SVector<Type,Size> SVector<Type,Size>::operator / (const double &tmp) {
  SVector<Type,Size> result;
  for (int i = 0; i < Size; ++i) {
    result[i] = size[i] / tmp;
  }
  return result;
}

/******************************************************************************
 |  Calculates vector cross product.                                          |
 |  Arguments:                                                                |
 |      this - first operand,                                                 |
 |      Vector2 - second operand.                                             |
 |  Returns:                                                                  |
 |      The cross product vector.                                             |
 */
template <typename Type, int Size>
SVector<Type,Size> SVector<Type,Size>::operator * (SVector<Type,Size> Vector2) const
{
  SVector<Type,Size>  Result;
  for (unsigned int Ind = 0; Ind < Size; ++Ind) Result[Ind] = (*this)[Ind] * Vector2[Ind];
  return Result;  
}
