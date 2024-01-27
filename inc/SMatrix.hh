#include <cmath>
#include <iostream>


template <typename Type, int Size> class SMatrix {
private:
  Type value[Size][Size];

public:
  SMatrix();
  SMatrix(Type[Size][Size]); // Konstruktor klasy

  SVector<Type, Size> operator*(SVector<Type, Size> tmp); // Operator mnożenia przez wektor

    SMatrix<Type,Size> operator * (SMatrix<Type,Size> tmp);           // Operator mnożenia przez macierz

  SMatrix<Type, Size> operator+(SMatrix<Type, Size> tmp);

  SMatrix<Type, Size> Transpose(); //  transposes matix

  Type Gauss(); //  calculte det

  SMatrix<Type, Size> ColumnChange(int column,
                                   SVector<Type, Size> vec); //  changes column

  SMatrix<Type, Size> RowChange(int row1, int row2); // changes 2 rows

  SMatrix<Type, Size>
  Changing(int row); // changes appropriate rows using RowChange()

  SVector<Type, Size>  Equation(SMatrix<Type, Size>  A, SVector<Type, Size> B); // solves equation

  SMatrix<Type, Size> Zamiana(unsigned int column);

  SMatrix<Type, Size> Wyzeruj(unsigned int column);

  Type CheckIf0() const; // function checks if it's triangular matrix

  Type &operator()(unsigned int row, unsigned int column);

  SVector<Type,Size> WBledu(SMatrix<Type,Size> A, SVector<Type,Size> X, SVector<Type,Size> B); //liczy wektor bledu

  const Type &operator()(unsigned int row, unsigned int column) const;




  Vector3D wypelnijRotX(Vector3D v , double theta);
};

typedef SMatrix<double, 3> Matrix3D; 


/******************************************************************************
 |  Przeciazenie operatora <<                                                 |
 |  Argumenty:                                                                |
 |      out - strumien wejsciowy,                                             |
 |      mat - macierz.                                                        |
 */
template <typename Type, int Size>
std::ostream &operator<<(std::ostream &out, const SMatrix<Type, Size> &mat) {
  for (int i = 0; i < Size; ++i) {
    for (int j = 0; j < Size; ++j) {
      out << "| " << mat(i, j)
          << " | "; // warto ustalic szerokosc wyswietlania dokladnosci liczb
    }
    std::cout << std::endl;
  }
  return out;
}

/******************************************************************************
 |  Przeciazenie operatora >>                                                 |
 |  Argumenty:                                                                |
 |      in - strumien wyjsciowy,                                              |
 |      mat - macierz.                                                         |
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
    std::cout << "Error: Macierz jest poza zasiegiem";
    exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
  }

  if (column >= Size) {
    std::cout << "Error: Macierz jest poza zasiegiem";
    exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
  }

  return value[row][column];
}

/******************************************************************************
 |  Funktor macierzy                                                          |
 |  Argumenty:                                                                |
 |      row - numer wiersza.                                                  |
 |      column - numer kolumny.                                               |
 |  Zwraca:                                                                   |
 |      Wartosc macierzy w danym miejscu tablicy jako stala.                  |
 */
template <typename Type, int Size>
const Type &SMatrix<Type, Size>::operator()(unsigned int row,
                                            unsigned int column) const {

  if (row >= Size) {
    std::cout << "Error: Macierz jest poza zasiegiem";
    exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
  }

  if (column >= Size) {
    std::cout << "Error: Macierz jest poza zasiegiem";
    exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
  }

  return value[row][column];
}

/******************************************************************************
 |  Konstruktor klasy Matrix.                                                 |
 |  Argumenty:                                                                |
 |      Brak argumentow.                                                      |
 |  Zwraca:                                                                   |
 |      Macierz wypelnione wartoscia 0.                                       |
 */
template <typename Type, int Size> SMatrix<Type, Size>::SMatrix() {
  for (int i = 0; i < Size; ++i) {
    for (int j = 0; j < Size; ++j) {
      value[i][j] = 0;
    }
  }
}

/******************************************************************************
 |  Konstruktor parametryczny klasy Matrix.                                   |
 |  Argumenty:                                                                |
 |      tmp - dwuwymiarowa tablica z elementami typu double.                  |
 |  Zwraca:                                                                   |
 |      Macierz wypelniona wartosciami podanymi w argumencie.                 |
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
 |  Funkcja zwracajaca macierz transponiowana                                  |
 |  Argumenty:                                                                |
 |      tmp - dwuwymiarowa tablica z elementami typu double.                  |
 |  Zwraca:                                                                   |
 |      Macierz wypelniona wartosciami podanymi w argumencie.                 |
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
 |  Realizuje mnozenie macierzy przez wektor.                                 |
 |  Argumenty:                                                                |
 |       - macierz, czyli pierwszy skladnik mnozenia,                         |
 |      v - wektor, czyli drugi skladnik mnozenia.                            |
 |  Zwraca:                                                                   |
 |      Iloczyn dwoch skladnikow przekazanych jako wektor.                    |
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
 |  Realizuje mnozenie macierzy przez macierz.                                |
 |  Argumenty:                                                                |
 |       - macierz, czyli pierwszy skladnik mnozenia,                         |
 |      v - wektor, czyli drugi skladnik mnozenia.                            |
 |  Zwraca:                                                                   |
 |      Iloczyn dwoch macierzy.                                               |
*/
template <typename Type, int Size>
SMatrix<Type,Size> SMatrix<Type,Size>::operator*(SMatrix<Type,Size> tmp) {
  SMatrix<Type,Size> result;

     for(int i = 0; i < Size; ++i)
        for(int j = 0; j < Size; ++j)
            for(int k = 0; k < Size; ++k)
            {
                result(i,j) += value[i][k] * tmp(k,j);
            }

  return result;
}


/******************************************************************************
 Przeciążenie dodawania macierzy |
  |  Argumenty:

 |       - macierz, czyli
 pierwszy skladnik dodawania,                     |
 |      v - wektor, czyli
 drugi skladnik dodawania.                                               |
 |
 Zwraca:                                                                   |
 |
 Macierz - iloczyn dwóch podanych macierzy.                  |
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
   Calculates determinant using gaussian elimination
   Returns:
     Value of determinant.

 */
template <typename Type, int Size> Type SMatrix<Type, Size>::Gauss() {
  Type det;
  int parzystosc=1;
 

  for (int i = 0; i < Size; ++i) {
    CheckIf0();
     
    if (value[i][i] == 0) {
      parzystosc=-parzystosc;
      Zamiana(i);
      Wyzeruj(i);

    }
    Wyzeruj(i);


  
  }


  det = value[0][0];
  for (int i = 1; i < Size; ++i){
      det = det * value[i][i];
    
  }
  det=det*parzystosc;
  return det;
}

/******************************************************************************
   Changing columns
   Arguments:
    cloumn  -  column to change
    vec - vector replacing that column
 */
template <typename Type, int Size>
SMatrix<Type, Size> SMatrix<Type, Size>::ColumnChange(int column,
                                                      SVector<Type, Size> vec) {
  SMatrix<Type, Size> result;

  for (int i = 0; i < Size; ++i) {
    for (int j = 0; j < Size; ++j) {
      result(i, j) = value[j][i];
    }
  }

  for (int i = 0; i < Size; ++i) {

    value[i][column-1] = vec[i];
  }

  return value;
}

/******************************************************************************
   Changing 2 rows
   Arguments:
    row1 -  row changed by row2
    row2 -  row changed by row1
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
  Function solves and prints matrixes A, X, B of AX=B equation
  and wektor bledu




 */
template <typename Type, int Size>
SVector<Type, Size> SMatrix<Type, Size>::Equation(SMatrix<Type, Size>A, SVector<Type, Size> B) {
  SVector<Type, Size> solutions;

  std::cout << "A and B of equation (AX=B) are represented by:  " << std::endl;
  std::cout << "A: " << std::endl;
  std::cout << A << std::endl;
  std::cout << "B: " << std::endl;
  std::cout << B << std::endl;



  SMatrix<Type, Size>  tmpA=A;
  Type W = A.Gauss();
  Type determinants[Size];


  for (int i = 1; i <= Size; ++i) {
    A=tmpA;
    A.ColumnChange(i,B);
    determinants[i - 1] = A.Gauss();
    
    solutions[i - 1] = determinants[i - 1] / W;
  }

  std::cout << "Solutions: " << std::endl;
  std::cout << solutions << std::endl;
  WBledu(tmpA,solutions,B);


  return solutions;
}



/******************************************************************************
  Funkcja zamienia kolumne po prawej strone, ktorej i-ty element jest niezerowy 
  i zamienia  z i-ta kolumna, jesli i-ty element tej kolumny byl zerowy 
  



 */
template <typename Type, int Size>
SMatrix<Type, Size> SMatrix<Type, Size>::Zamiana(unsigned int column) {
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
  Funkcja zeruje i-ty element w prawo



 */
template <typename Type, int Size>
SMatrix<Type, Size> SMatrix<Type, Size>::Wyzeruj(unsigned int column) {
  Type wariat;

  for (int k = column + 1; k < Size; ++k) {
    wariat = (value[column][k] / value[column][column]);
  
    for (int j = 0; j < Size; ++j) {
      value[j][k] = value[j][k] - value[j][column] * wariat;
    }
  }

  return value;
}

/******************************************************************************
 Function checks if it's triangular matrix
   Returns:
    det  -  determinant if it's trangular matrix

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

det=value[Size][Size];
  if (result == 1) {
    for (i = Size-1; i > 0; --i) {
      det *= value[i][i];
    }
  }

  return det;
}





/******************************************************************************
Liczy wektor bledu
   Argumenty:                                                            
       A -  macierz wspolczynnikow rownania            
       X -  wektor nieznanych wartosci
       B -  wektor wyrazow wolnych                      
  Zwraca:                                                                
      Wektor bledu

 */
template <typename Type, int Size>
SVector<Type,Size> SMatrix<Type,Size>::WBledu(SMatrix<Type,Size> A, SVector<Type,Size> X, SVector<Type,Size> B) {
 SVector<Type,Size> result;

result=(A*X)-B;

std::cout<<"Wektor bledu: "<<std::endl;
std::cout<<result<<std::endl;
  return result;


}




