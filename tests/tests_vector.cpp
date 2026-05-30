#include <gtest/gtest.h>
#include "SVector.hh"
#include "SMatrix.hh"
#include <cmath>

#define DIFFERENCE 1e-9
#define SIZE 5

typedef SVector<double,5> Vector5D;
typedef SMatrix<double,5> Matrix5D;

Vector3D rotateX(Vector3D v, double theta) {
  Vector3D rotated;
  double tmp[3][3] = {
      {1, 0, 0}, {0, cos(theta), -sin(theta)}, {0, sin(theta), cos(theta)}};
  Matrix3D RotationMat = Matrix3D(tmp);
  rotated = RotationMat * v;
  return rotated;
}

Vector3D rotateY(Vector3D v, double theta) {
  Vector3D rotated;
  double tmp[3][3] = {
      {cos(theta), 0, sin(theta)}, {0, 1, 0}, {-sin(theta), 0, cos(theta)}};
  Matrix3D RotationMat = Matrix3D(tmp);
  rotated = RotationMat * v;
  return rotated;
}

Vector3D rotateZ(Vector3D v, double theta) {
  Vector3D rotated;
  double tmp[3][3] = {
      {cos(theta), -sin(theta), 0}, {sin(theta), cos(theta), 0}, {0, 0, 1}};
  Matrix3D RotationMat = Matrix3D(tmp);
  rotated = RotationMat * v;
  return rotated;
}


// Tests that don't naturally fit in the headers/.cpp files directly
// can be placed in a tests/*.cpp file. Integration tests are a good example.

TEST(Tests, Test_1_Gauss) {
 double argumentsM[][SIZE] = {{1, 8, 8, 9,1}, {2,2,3, 1.00, 2}, 
 {1,12,1, 1, 17}, {3,7,2, 4, 0},   {3,2,2, 0, 1}};
  Matrix5D tmpM2 = Matrix5D(argumentsM);
  EXPECT_LT(abs(tmpM2.Gauss() -(-378)), DIFFERENCE); 
  std::cout<<tmpM2.Gauss()<<std::endl;
    std::cout<<tmpM2<<std::endl;
  //  wystapily problemy 
  // z porownywaniem liczb wiec w testach obliczania wyznacznika
  // wiec testy licza roznice miedzy liczbami i porownuja
  // z liczba bliska 0

}

TEST(Tests, Test_2_Determinant) {
  double argumentsM[][SIZE] = {{1, 2, 3, 4, 1},
                               {0, 3, 2, 1, 0},
                               {2, 1, 1, 0, 0},
                               {0, 1, 0, 0, 0},
                               {3, 0, 0, 0, 0}};
  Matrix5D A = Matrix5D(argumentsM);

  EXPECT_LT(abs(A.Gauss() - (3)), DIFFERENCE);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST(Tests, Test_3_Determinant) {
  double argumentsM[][SIZE] = {{2, 3, 4, 5, 1},
                               {1, 0, 4, 1, 2},
                               {0, 0, 1, 1, 4},
                               {0, 1, 2, 4, 2},
                               {3, 2, 2, 3, 1}};
  Matrix5D A = Matrix5D(argumentsM);
  EXPECT_LT(abs(A.Gauss() - (-139)), DIFFERENCE);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST(Tests, Test_4_Determinant) {
  double argumentsM[][SIZE] = {{9, 8, 8, 9, 1},
                               {2, 2, 3, 1.00, 2},
                               {1, 1, 1, 1, 0},
                               {3, 1, 2, 4, 0},
                               {0, 1, 0, 1, 0}};
  Matrix5D A = Matrix5D(argumentsM);
  EXPECT_LT(abs(A.Gauss() - (-6)), DIFFERENCE);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST(Tests, Test_5_Determinant) {
  double argumentsM[][SIZE] = {{1, 2, 3, 4, 5},
                               {2, 2, 3, 1.00, 2},
                               {1, 1, 1, 1, 0},
                               {3, 1, 2, 4, 0},
                               {0, 1, 0, 1, 0}};
  Matrix5D A = Matrix5D(argumentsM);

  EXPECT_LT(abs(A.Gauss() - (6)), DIFFERENCE);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST(Tests, Test_6_Determinant) {
  double argumentsM[][SIZE] = {{1, 2, 3, 4, 5},
                               {2, 1, 3, 7, 0},
                               {1, 1, 1, 1, 0},
                               {3, 1, 2, 4, 0},
                               {0, 1, 0, 1, 0}};
  Matrix5D A = Matrix5D(argumentsM);

  EXPECT_LT(abs(A.Gauss() - (-45)), DIFFERENCE);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST(Tests, Test_7_Determinant) {
  double argumentsM[][SIZE] = {{1, 1, 3, 4, 5},
                               {2, 0, 3, 7, 0},
                               {1, 7, 1, 1, 0},
                               {3, 4, 2, 4, 0},
                               {0, 8, 0, 1, 0}};
  Matrix5D A = Matrix5D(argumentsM);

  EXPECT_LT(abs(A.Gauss() - (-395)), DIFFERENCE);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST(Tests, Test_8_Determinant) {
  double argumentsM[][SIZE] = {{1, 1, 3, 4, 5},
                               {2, 0, 3, 7, 0},
                               {1, 7, 1, 0, 0},
                               {3, 4, 0, 0, 0},
                               {77, 0, 0, 0, 0}};
  Matrix5D A = Matrix5D(argumentsM);

  EXPECT_LT(abs(A.Gauss() - (10780)), DIFFERENCE);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST(Tests, Test_9_Determinant) {
  double argumentsM[][SIZE] = {{1, 1, 3, 4, 5},
                               {2, 0, 3, 7, 0},
                               {1, 7, 1, 0, 0},
                               {3, 4, 0, 0, 0},
                               {77, 0, 0, 0, 0}};
  Matrix5D A = Matrix5D(argumentsM);

  EXPECT_LT(abs(A.Gauss() - (10780)), DIFFERENCE);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST(Tests, Test_10_Determinant) {
  double argumentsM[][SIZE] = {{11, 1, 3, 4, 5},
                               {2, 0, 3, 7, 1},
                               {1, 7, 1, 0, 30},
                               {3, 4, 0, 0, 0},
                               {77, 0, 4, 8, 0}};
  Matrix5D A = Matrix5D(argumentsM);

  EXPECT_LT(abs(A.Gauss() - (-66288)), DIFFERENCE);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST(Tests, Test_11_Determinant) {
  double argumentsM[][SIZE] = {{2},
                               {0, 1, 3, 7, 3},
                               {1, 7, 7, 4, 9},
                               {3, 4, 0, 0, 0},
                               {77, 0, 0, 11, 0}};
  Matrix5D A = Matrix5D(argumentsM);

  EXPECT_LT(abs(A.Gauss() - (-528)), DIFFERENCE);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

#if 0
TEST(Tests, Test_12_Complex_determinant) {
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

  EXPECT_EQ(A.Gauss(), result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST(Tests, Test_13_Complex_determinant) {
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

  EXPECT_EQ(A.Gauss(), result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST(Tests, Test_14_Complex_determinant) {
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

  EXPECT_EQ(A.Gauss(), result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST(Tests, Test_15_Complex_determinant) {
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

  EXPECT_EQ(A.Gauss(), result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST(Tests, Test_16_Complex_determinant) {
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

  EXPECT_EQ(A.Gauss(), result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST(Tests, Test_17_Complex_determinant) {
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

  EXPECT_EQ(A.Gauss(), result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST(Tests, Test_18_Complex_determinant) {
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

  EXPECT_EQ(A.Gauss(), result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST(Tests, Test_19_Complex_determinant) {
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

  EXPECT_EQ(A.Gauss(), result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}

TEST(Tests, Test_20_Complex_determinant) {
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

  EXPECT_EQ(A.Gauss(), result);
  std::cout << A.Gauss() << std::endl;
  std::cout << A << std::endl;
}
#endif




TEST(Tests, Test_21_Equation_function_I) {
 double argumentsM[][SIZE] = {{69, 2, 3, 4,5}, {4,69,3, 7, 0}, 
 {3,1,69, 1, 0}, {1,1,2, 69, 0},   {2,1,0, 1,69}};
  Matrix5D A = Matrix5D(argumentsM);

   double argumentsB[] = {2, 1, 3, 7, 7};
  Vector5D B = Vector5D(argumentsB);

  double argumentsR[] = {0.0141227531425317, 0.0017275517908462, 0.0413896279325196, 0.1000198614377041,0.0995653200070491};
  Vector5D R = Vector5D(argumentsR);

  EXPECT_EQ(A.Equation(A,B), R);
 
} 


TEST(Tests, Test_22_Equation_function_II) {
 double argumentsM[][SIZE] = {{1, 2, 1, 4,5}, {4,3,3, 1, 0}, 
 {3,1,0, 1, 0}, {11,1,2, 0, 9},   {2,1,0, 1,17}};
  Matrix5D A = Matrix5D(argumentsM);

   double argumentsB[] = {4, 2, 1, 0, 2};
  Vector5D B = Vector5D(argumentsB);

  double argumentsR[] = {-0.0912913,0.613213 , -0.045045 ,0.660661,0.0534535};
  Vector5D R = Vector5D(argumentsR);

  EXPECT_EQ(A.Equation(A,B), R);
 
} 



TEST(Tests, Test_23_Equation_function_III) {
 double argumentsM[][SIZE] = {{2,1, 1, 1,2}, {2,2,3, 1,2}, 
 {1,1.5,1, 1, 0}, {3,1,2, 4, 0},   {3,2,2, 0,1}};
  Matrix5D A = Matrix5D(argumentsM);

   double argumentsB[] = {9, 8, 8, 9, 1};
  Vector5D B = Vector5D(argumentsB);

  double argumentsR[] = {-2.74286 , 6.68571 ,-3.84286,4.55714 ,3.54286 };
  Vector5D R = Vector5D(argumentsR);

  EXPECT_EQ(A.Equation(A,B), R);
 
} 

TEST(Tests, Test_24_Equation_function_IV) {
 double argumentsM[][SIZE] = {{2,2, 1, 3,3}, {1,2,1.5, 1,2}, 
 {1,3,1, 2, 2}, {1,1,1, 4, 0},   {2,2,0, 0,1}};
  Matrix5D A = Matrix5D(argumentsM);

   double argumentsB[] = {9, 8, 8, 9, 1};
  Vector5D B = Vector5D(argumentsB);

  double argumentsR[] = {-0.13 , 0.47 ,3.51,1.29 ,0.31 };
  Vector5D R = Vector5D(argumentsR);

  EXPECT_EQ(A.Equation(A,B), R);
 
} 


TEST(Tests, Test_25_Rotation_X_I) {
  double argumentsM[3] = {1, 0, 0};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {1, 0, 0};
  Vector3D R = Vector3D(argumentsR);

  EXPECT_EQ(rotateX(B, M_PI / 2), R);
}

TEST(Tests, Test_26_Rotation_X_II) {
  double argumentsM[3] = {0, 1, 0};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {0, 0, 1};
  Vector3D R = Vector3D(argumentsR);

  EXPECT_EQ(rotateX(B, M_PI / 2), R);
}

TEST(Tests, Test_27_Rotation_X_III) {
  double argumentsM[3] = {0, 0, 1};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {0, -1, 0};
  Vector3D R = Vector3D(argumentsR);

  EXPECT_EQ(rotateX(B, M_PI / 2), R);
}

TEST(Tests, Test_28_Rotation_Y_I) {
  double argumentsM[3] = {1, 0, 0};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {1, 0, 0};
  Vector3D R = Vector3D(argumentsR);

  EXPECT_EQ(rotateX(B, M_PI / 2), R);
}

TEST(Tests, Test_29_Rotation_Y_II) {
  double argumentsM[3] = {0, 1, 0};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {0, 1, 0};
  Vector3D R = Vector3D(argumentsR);

  EXPECT_EQ(rotateY(B, M_PI / 2), R);
}

TEST(Tests, Test_30_Rotation_Y_III) {
  double argumentsM[3] = {0, 0, 1};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {1, 0, 0};
  Vector3D R = Vector3D(argumentsR);

  EXPECT_EQ(rotateY(B, M_PI / 2), R);
}

TEST(Tests, Test_31_Rotation_Z_I) {
  double argumentsM[3] = {1, 0, 0};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {0, 1, 0};
  Vector3D R = Vector3D(argumentsR);

  EXPECT_EQ(rotateZ(B, M_PI / 2), R);
}

TEST(Tests, Test_32_Rotation_Z_II) {
  double argumentsM[3] = {0, 1, 0};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {-1, 0, 0};
  Vector3D R = Vector3D(argumentsR);

  EXPECT_EQ(rotateZ(B, M_PI / 2), R);
}

TEST(Tests, Test_33_Rotation_Z_III) {
  double argumentsM[3] = {0, 0, 1};
  Vector3D B = Vector3D(argumentsM);

  double argumentsR[3] = {0, 0, 1};
  Vector3D R = Vector3D(argumentsR);

  EXPECT_EQ(rotateZ(B, M_PI / 2), R);
}

TEST(Tests, Test_34_Wektor_bledu_I) {
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

  EXPECT_EQ(A.ErrorVector(A, X, B), R);
}

TEST(Tests, Test_35_Wektor_bledu_II) {
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

  EXPECT_EQ(A.ErrorVector(A, X, B), R);
}

TEST(Tests, Test_36_Wektor_bledu_III) {
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

  EXPECT_EQ(A.ErrorVector(A, X, B), R);
}

TEST(Tests, Test_37_Wektor_bledu_IV) {
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

  EXPECT_EQ(A.ErrorVector(A, X, B), R);
}

