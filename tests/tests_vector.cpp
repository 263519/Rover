#include "doctest/doctest.h"
#include "matrix.hh"
#include "vector.hh"
#include "SVector.hh"
#include "SMatrix.hh"
#include "WyrazenieZesp.hh"
#include "LZespolona.hh"
#include <cmath>

#define ROZNICA 1e-39

typedef SVector<double,5> Vector5D;
typedef SMatrix<double,5> Matrix5D;

typedef SVector<LZespolona, 5> Vector5Z;
typedef SMatrix<LZespolona, 5> Matrix5Z;


// Tests that don't naturally fit in the headers/.cpp files directly
// can be placed in a tests/*.cpp file. Integration tests are a good example.

TEST_CASE("1. Gauss") {
 double argumentsM[][SIZE] = {{1, 8, 8, 9,1}, {2,2,3, 1.00, 2}, 
 {1,12,1, 1, 17}, {3,7,2, 4, 0},   {3,2,2, 0, 1}};
  Matrix5D tmpM2 = Matrix5D(argumentsM);
  CHECK(abs(tmpM2.Gauss() -(-378))<ROZNICA); 
  std::cout<<tmpM2.Gauss()<<std::endl;
    std::cout<<tmpM2<<std::endl;
  //  wystapily problemy 
  // z porownywaniem liczb wiec w testach obliczania wyznacznika
  // wiec testy licza roznice miedzy liczbami i porownuja
  // z liczba bliska 0

}

TEST_CASE("2. Determinant") {
  double argumentsM[][SIZE] = {{1, 2, 3, 4, 1},
                               {0, 3, 2, 1, 0},
                               {2, 1, 1, 0, 0},
                               {0, 1, 0, 0, 0},
                               {3, 0, 0, 0, 0}};
  Matrix5D A = Matrix5D(argumentsM);

  CHECK(abs(A.Gauss() - (3)) < ROZNICA);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("3. Determinant") {
  double argumentsM[][SIZE] = {{2, 3, 4, 5, 1},
                               {1, 0, 4, 1, 2},
                               {0, 0, 1, 1, 4},
                               {0, 1, 2, 4, 2},
                               {3, 2, 2, 3, 1}};
  Matrix5D A = Matrix5D(argumentsM);
  CHECK(abs(A.Gauss() - (-139)) < ROZNICA);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("4. Determinant") {
  double argumentsM[][SIZE] = {{9, 8, 8, 9, 1},
                               {2, 2, 3, 1.00, 2},
                               {1, 1, 1, 1, 0},
                               {3, 1, 2, 4, 0},
                               {0, 1, 0, 1, 0}};
  Matrix5D A = Matrix5D(argumentsM);
  CHECK(abs(A.Gauss() - (-6)) < ROZNICA);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("5. Determinant") {
  double argumentsM[][SIZE] = {{1, 2, 3, 4, 5},
                               {2, 2, 3, 1.00, 2},
                               {1, 1, 1, 1, 0},
                               {3, 1, 2, 4, 0},
                               {0, 1, 0, 1, 0}};
  Matrix5D A = Matrix5D(argumentsM);

  CHECK(abs(A.Gauss() - (6)) < ROZNICA);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("6. Determinant") {
  double argumentsM[][SIZE] = {{1, 2, 3, 4, 5},
                               {2, 1, 3, 7, 0},
                               {1, 1, 1, 1, 0},
                               {3, 1, 2, 4, 0},
                               {0, 1, 0, 1, 0}};
  Matrix5D A = Matrix5D(argumentsM);

  CHECK(abs(A.Gauss() - (-45)) < ROZNICA);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("7. Determinant") {
  double argumentsM[][SIZE] = {{1, 1, 3, 4, 5},
                               {2, 0, 3, 7, 0},
                               {1, 7, 1, 1, 0},
                               {3, 4, 2, 4, 0},
                               {0, 8, 0, 1, 0}};
  Matrix5D A = Matrix5D(argumentsM);

  CHECK(abs(A.Gauss() - (-395)) < ROZNICA);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("8.Determinant") {
  double argumentsM[][SIZE] = {{1, 1, 3, 4, 5},
                               {2, 0, 3, 7, 0},
                               {1, 7, 1, 0, 0},
                               {3, 4, 0, 0, 0},
                               {77, 0, 0, 0, 0}};
  Matrix5D A = Matrix5D(argumentsM);

  CHECK(abs(A.Gauss() - (10780)) < ROZNICA);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("9. Determinant") {
  double argumentsM[][SIZE] = {{1, 1, 3, 4, 5},
                               {2, 0, 3, 7, 0},
                               {1, 7, 1, 0, 0},
                               {3, 4, 0, 0, 0},
                               {77, 0, 0, 0, 0}};
  Matrix5D A = Matrix5D(argumentsM);

  CHECK(abs(A.Gauss() - (10780)) < ROZNICA);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("10. Determinant") {
  double argumentsM[][SIZE] = {{11, 1, 3, 4, 5},
                               {2, 0, 3, 7, 1},
                               {1, 7, 1, 0, 30},
                               {3, 4, 0, 0, 0},
                               {77, 0, 4, 8, 0}};
  Matrix5D A = Matrix5D(argumentsM);

  CHECK(abs(A.Gauss() - (-66288)) < ROZNICA);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("11. Determinant") {
  double argumentsM[][SIZE] = {{2},
                               {0, 1, 3, 7, 3},
                               {1, 7, 7, 4, 9},
                               {3, 4, 0, 0, 0},
                               {77, 0, 0, 11, 0}};
  Matrix5D A = Matrix5D(argumentsM);

  CHECK(abs(A.Gauss() - (-528)) < ROZNICA);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("12. Complex determinant") {
  LZespolona Zesp[5][5];

  double re[5][5] = {{2, 2, 1, 3, 3},
                     {1, 2, 1.5, 1, 2},
                     {1, 3, 1, 2, 2},
                     {1, 1, 1, 4, 0},
                     {2, 2, 0, 0, 1}};
  double im[5][5] = {{2, 2, 1, 3, 3},
                     {1, 2, 1.5, 1, 2},
                     {1, 3, 1, 2, 2},
                     {1, 1, 1, 4, 0},
                     {2, 2, 0, 0, 1}};

  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      Zesp[i][j].set_re() = re[i][j];
      Zesp[i][j].set_im() = im[i][j];
    }
  }

  LZespolona result;
  result.set_re() = -140;
  result.set_im() = -140;
  Matrix5Z A = Matrix5Z(Zesp);

  CHECK(A.Gauss() == result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("13. Complex determinant") {
  LZespolona Zesp[5][5];

  double re[5][5] = {{0, 0, 1, 3, 3},
                     {1, 2, 0, 1, 7},
                     {1, 3, 1, 2, 8},
                     {1, 4, 1, 13, 11},
                     {2, 1, 0, 9, 5}};
  double im[5][5] = {{69, 3, 4, 13, 3},
                     {1, 1, 15, 1, 2},
                     {15, 3, 13, 2, 21},
                     {0, 1, 0, 3, 11},
                     {2, 1, 7, 8, 9}};

  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      Zesp[i][j].set_re() = re[i][j];
      Zesp[i][j].set_im() = im[i][j];
    }
  }

  LZespolona result;
  result.set_re() = -529856;
  result.set_im() = 426384;
  Matrix5Z A = Matrix5Z(Zesp);

  CHECK(A.Gauss() == result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("14. Complex determinant") {
  LZespolona Zesp[5][5];

  double re[5][5] = {{0, 2, 0, 3, 0},
                     {1, 2, 1.5, 1, 2},
                     {1, 3, 1, 2, 2},
                     {1, 1, 1, 4, 0},
                     {0, 2, 0, 0, 0}};
  double im[5][5] = {{2, 0, 4, 13, 0},
                     {1, 0, 0, 1, 7},
                     {1, 0, 1, 2, 0},
                     {1, 0, 0, 4, 0},
                     {2, 0, 0, 0, 1}};

  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      Zesp[i][j].set_re() = re[i][j];
      Zesp[i][j].set_im() = im[i][j];
    }
  }

  LZespolona result;
  result.set_re() = -714;
  result.set_im() = -174;
  Matrix5Z A = Matrix5Z(Zesp);

  CHECK(A.Gauss() == result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("15. Complex determinant") {
  LZespolona Zesp[5][5];

  double re[5][5] = {{1, 2, 3, 4, 5},
                     {6, 7, 8, 9, 8},
                     {7, 6, 4, 5, 3},
                     {2, 1, 0, 1, 2},
                     {3, 4, 5, 6, 7}};
  double im[5][5] = {{8, 9, 10, 11, 12},
                     {13, 12, 11, 10, 9},
                     {8, 7, 6, 5, 4},
                     {3, 2, 1, 0, 1},
                     {2, 3, 4, 5, 6}};

  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      Zesp[i][j].set_re() = re[i][j];
      Zesp[i][j].set_im() = im[i][j];
    }
  }

  LZespolona result;
  result.set_re() = 32;
  result.set_im() = -16;
  Matrix5Z A = Matrix5Z(Zesp);

  CHECK(A.Gauss() == result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("16. Complex determinant") {
  LZespolona Zesp[5][5];

  double re[5][5] = {{0, 0, 0, 3, 3},
                     {1, 2, 2, 1, 2},
                     {1, 3, 0, 0, 2},
                     {1, 3, 4, 4, 1},
                     {2, 2, 0, 0, 1}};
  double im[5][5] = {{7, 6, 1, 3, 3},
                     {1, 2, 1, 4, 2},
                     {1, 2, 1, 2, 4},
                     {9, 3, 1, 4, 0},
                     {4, 2, 0, 0, 0}};

  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      Zesp[i][j].set_re() = re[i][j];
      Zesp[i][j].set_im() = im[i][j];
    }
  }

  LZespolona result;
  result.set_re() = -181;
  result.set_im() = 1096;
  Matrix5Z A = Matrix5Z(Zesp);

  CHECK(A.Gauss() == result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("17. Complex determinant") {
  LZespolona Zesp[5][5];

  double re[5][5] = {{1, 2, 22, 0, 1},
                     {4, 1, 3, 4, 7},
                     {1, 3, 1, 2, 2},
                     {1, 1, 0, 4, 0},
                     {2, 2, 0, 3, 1}};
  double im[5][5] = {{0, 2, 1, 3.4, 0},
                     {1, 2, 1, 1, 1},
                     {1, 3, 7, 2.1, 2},
                     {1, 1, 1, 4.4, 0},
                     {2, 2, 0, 22}};

  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      Zesp[i][j].set_re() = re[i][j];
      Zesp[i][j].set_im() = im[i][j];
    }
  }
  LZespolona result;
  result.set_re() = -12190.7;
  result.set_im() = -1857.4;
  Matrix5Z A = Matrix5Z(Zesp);

  CHECK(A.Gauss() == result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("18. Complex determinant") {
  LZespolona Zesp[5][5];

  double re[5][5] = {{0.2, 4, 6, 7, 10},
                     {9, 2, 13, 1, 2},
                     {1, 3, -1, 2, 22},
                     {1, 3, -4, -4, 0},
                     {2, 5, 0, 0, 8}};
  double im[5][5] = {{0, 2, -1, 0, 3},
                     {1, 2, 5, 1, 2},
                     {1, 4, 1, 7, 2},
                     {-0, 1, 1, 0, 0},
                     {1, 2, 4, 0, 1}};

  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      Zesp[i][j].set_re() = re[i][j];
      Zesp[i][j].set_im() = im[i][j];
    }
  }

  LZespolona result;
  result.set_re() = 3567.4;
  result.set_im() = -18983.8;
  Matrix5Z A = Matrix5Z(Zesp);

  CHECK(A.Gauss() == result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("19. Complex determinant") {
  LZespolona Zesp[5][5];

  double re[5][5] = {{4, 8, 16, 4, 8},
                     {1.255, 2, 3, 4, 2},
                     {3, 4, 1, 5, 2},
                     {8, 9, 1, 7, 2},
                     {2, 2, 0, 0, 1}};
  double im[5][5] = {{4, 2, 1, 4, 3},
                     {1, 2, 1.5, 1, 2},
                     {1, 3, 0, 3, 2},
                     {1, 0, 0, 4, 0},
                     {5, 3, 1, 1, 0}};

  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      Zesp[i][j].set_re() = re[i][j];
      Zesp[i][j].set_im() = im[i][j];
    }
  }

  LZespolona result;
  result.set_re() = 176.85;
  result.set_im() = -962.595;
  Matrix5Z A = Matrix5Z(Zesp);

  CHECK(A.Gauss() == result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST_CASE("20. Complex determinant") {
  LZespolona Zesp[5][5];

  double re[5][5] = {{12, 42, 0, 3, 3},
                     {1, 2, 2.5, 1, 2},
                     {1, 3, 1, 3, 1},
                     {3, 2, 5, 8, 7},
                     {2, 2, 4, 3, 1}};
  double im[5][5] = {{2, 3, 1, 3, 3},
                     {6, 4, 1.5, 1, 2},
                     {2, 3, 1, 4, 3},
                     {1, 3, 5, 4, 0},
                     {2, 05, 0, 8, 17}};

  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      Zesp[i][j].set_re() = re[i][j];
      Zesp[i][j].set_im() = im[i][j];
    }
  }

  LZespolona result;
  result.set_re() = 19273.5;
  result.set_im() = -76899.5;
  Matrix5Z A = Matrix5Z(Zesp);

  CHECK(A.Gauss() == result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}




TEST_CASE("21. Equation function I") {
 double argumentsM[][SIZE] = {{69, 2, 3, 4,5}, {4,69,3, 7, 0}, 
 {3,1,69, 1, 0}, {1,1,2, 69, 0},   {2,1,0, 1,69}};
  Matrix5D A = Matrix5D(argumentsM);

   double argumentsB[] = {2, 1, 3, 7, 7};
  Vector5D B = Vector5D(argumentsB);

  double argumentsR[] = {0.0141227531425317, 0.0017275517908462, 0.0413896279325196, 0.1000198614377041,0.0995653200070491};
  Vector5D R = Vector5D(argumentsR);

  CHECK(A.Equation(A,B) == R);
 
} 


TEST_CASE("22. Equation function II") {
 double argumentsM[][SIZE] = {{1, 2, 1, 4,5}, {4,3,3, 1, 0}, 
 {3,1,0, 1, 0}, {11,1,2, 0, 9},   {2,1,0, 1,17}};
  Matrix5D A = Matrix5D(argumentsM);

   double argumentsB[] = {4, 2, 1, 0, 2};
  Vector5D B = Vector5D(argumentsB);

  double argumentsR[] = {-0.0912913,0.613213 , -0.045045 ,0.660661,0.0534535};
  Vector5D R = Vector5D(argumentsR);

  CHECK(A.Equation(A,B) == R);
 
} 



TEST_CASE("23. Equation function III") {
 double argumentsM[][SIZE] = {{2,1, 1, 1,2}, {2,2,3, 1,2}, 
 {1,1.5,1, 1, 0}, {3,1,2, 4, 0},   {3,2,2, 0,1}};
  Matrix5D A = Matrix5D(argumentsM);

   double argumentsB[] = {9, 8, 8, 9, 1};
  Vector5D B = Vector5D(argumentsB);

  double argumentsR[] = {-2.74286 , 6.68571 ,-3.84286,4.55714 ,3.54286 };
  Vector5D R = Vector5D(argumentsR);

  CHECK(A.Equation(A,B) == R);
 
} 

TEST_CASE("24. Equation function IV") {
 double argumentsM[][SIZE] = {{2,2, 1, 3,3}, {1,2,1.5, 1,2}, 
 {1,3,1, 2, 2}, {1,1,1, 4, 0},   {2,2,0, 0,1}};
  Matrix5D A = Matrix5D(argumentsM);

   double argumentsB[] = {9, 8, 8, 9, 1};
  Vector5D B = Vector5D(argumentsB);

  double argumentsR[] = {-0.13 , 0.47 ,3.51,1.29 ,0.31 };
  Vector5D R = Vector5D(argumentsR);

  CHECK(A.Equation(A,B) == R);
 
} 


TEST_CASE("25. Rotation X I") {
  double argumentsM[3] = {1, 0, 0};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {1, 0, 0};
  Vector3D R = Vector3D(argumentsR);

  CHECK(wypelnijRotX(B, M_PI / 2) == R);
}

TEST_CASE("26. Rotation X II") {
  double argumentsM[3] = {0, 1, 0};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {0, 0, 1};
  Vector3D R = Vector3D(argumentsR);

  CHECK(wypelnijRotX(B, M_PI / 2) == R);
}

TEST_CASE("27. Rotation X III") {
  double argumentsM[3] = {0, 0, 1};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {0, -1, 0};
  Vector3D R = Vector3D(argumentsR);

  CHECK(wypelnijRotX(B, M_PI / 2) == R);
}

TEST_CASE("28. Rotation Y I") {
  double argumentsM[3] = {1, 0, 0};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {1, 0, 0};
  Vector3D R = Vector3D(argumentsR);

  CHECK(wypelnijRotX(B, M_PI / 2) == R);
}

TEST_CASE("29. Rotation Y II") {
  double argumentsM[3] = {0, 1, 0};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {0, 1, 0};
  Vector3D R = Vector3D(argumentsR);

  CHECK(wypelnijRotY(B, M_PI / 2) == R);
}

TEST_CASE("30. Rotation Y III") {
  double argumentsM[3] = {0, 0, 1};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {1, 0, 0};
  Vector3D R = Vector3D(argumentsR);

  CHECK(wypelnijRotY(B, M_PI / 2) == R);
}

TEST_CASE("31. Rotation Z I") {
  double argumentsM[3] = {1, 0, 0};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {0, 1, 0};
  Vector3D R = Vector3D(argumentsR);

  CHECK(wypelnijRotZ(B, M_PI / 2) == R);
}

TEST_CASE("32. Rotation Z II") {
  double argumentsM[3] = {0, 1, 0};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {-1, 0, 0};
  Vector3D R = Vector3D(argumentsR);

  CHECK(wypelnijRotZ(B, M_PI / 2) == R);
}

TEST_CASE("33. Rotation Z III") {
  double argumentsM[3] = {0, 0, 1};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {0, 0, 1};
  Vector3D R = Vector3D(argumentsR);

  CHECK(wypelnijRotZ(B, M_PI / 2) == R);
}

TEST_CASE("34. Wektor bledu I") {
  double argumentsM[][SIZE] = {{69, 2, 3, 4, 5},
                               {4, 69, 3, 7, 0},
                               {3, 1, 69, 1, 0},
                               {1, 1, 2, 69, 0},
                               {2, 1, 0, 1, 69}};
  Matrix5D A = Matrix5D(argumentsM);

  double argumentsB[] = {2, 1, 3, 7, 7};
  Vector5D B = Vector5D(argumentsB);

  double argumentsR[] = {0, 0, 0, 0, 0};
  Vector5D R = Vector5D(argumentsR);

  Vector5D X = A.Equation(A, B);

  CHECK(A.WBledu(A, X, B) == R);
}

TEST_CASE("35. Wektor bledu II") {
  double argumentsM[][SIZE] = {{1, 2, 1, 4, 5},
                               {4, 3, 3, 1, 0},
                               {3, 1, 0, 1, 0},
                               {11, 1, 2, 0, 9},
                               {2, 1, 0, 1, 17}};
  Matrix5D A = Matrix5D(argumentsM);

  double argumentsB[] = {2, 1, 3, 7, 7};
  Vector5D B = Vector5D(argumentsB);

  double argumentsR[] = {0, 0, 0, 0, 0};
  Vector5D R = Vector5D(argumentsR);

  Vector5D X = A.Equation(A, B);

  CHECK(A.WBledu(A, X, B) == R);
}

TEST_CASE("36. Wektor bledu III") {
  double argumentsM[][SIZE] = {{2, 1, 1, 1, 2},
                               {2, 2, 3, 1, 2},
                               {1, 1.5, 1, 1, 0},
                               {3, 1, 2, 4, 0},
                               {3, 2, 2, 0, 1}};
  Matrix5D A = Matrix5D(argumentsM);

  double argumentsB[] = {2, 1, 3, 7, 7};
  Vector5D B = Vector5D(argumentsB);

  double argumentsR[] = {0, 0, 0, 0, 0};
  Vector5D R = Vector5D(argumentsR);

  Vector5D X = A.Equation(A, B);

  CHECK(A.WBledu(A, X, B) == R);
}

TEST_CASE("37. Wektor bledu IV") {
  double argumentsM[][SIZE] = {{1, 2, 3, 0, 0},
                               {5, 3, 3, 4, 1},
                               {3, 0, 0, 1, 4},
                               {1, 2, 2, 69, 0},
                               {2, 1, 8, 1, 0}};
  Matrix5D A = Matrix5D(argumentsM);

  double argumentsB[] = {2, 1, 3, 7, 7};
  Vector5D B = Vector5D(argumentsB);

  double argumentsR[] = {0, 0, 0, 0, 0};
  Vector5D R = Vector5D(argumentsR);

  Vector5D X = A.Equation(A, B);

  CHECK(A.WBledu(A, X, B) == R);
}

