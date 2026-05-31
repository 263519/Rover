#include <gtest/gtest.h>
#include "SVector.hh"
#include "SMatrix.hh"
#include <cmath>

#define DIFFERENCE 1e-9

typedef SVector<double, 5> Vector5D;
typedef SMatrix<double, 5> Matrix5D;

Vector3D rotateX(Vector3D v, double theta) {
  Matrix3D rotationMat({
      {1, 0, 0}, 
      {0, cos(theta), -sin(theta)}, 
      {0, sin(theta), cos(theta)}
  });
  return rotationMat * v;
}

Vector3D rotateY(Vector3D v, double theta) {
  Matrix3D rotationMat({
      {cos(theta), 0, sin(theta)}, 
      {0, 1, 0}, 
      {-sin(theta), 0, cos(theta)}
  });
  return rotationMat * v;
}

Vector3D rotateZ(Vector3D v, double theta) {
  Matrix3D rotationMat({
      {cos(theta), -sin(theta), 0}, 
      {sin(theta), cos(theta), 0}, 
      {0, 0, 1}
  });
  return rotationMat * v;
}

TEST(Tests, Test_1_Gauss) {
  Matrix5D A({
      {1, 8, 8, 9, 1}, 
      {2, 2, 3, 1.00, 2}, 
      {1, 12, 1, 1, 17}, 
      {3, 7, 2, 4, 0}, 
      {3, 2, 2, 0, 1}
  });
  EXPECT_NEAR(A.Gauss(), -378.0, DIFFERENCE); 
}

TEST(Tests, Test_2_Determinant) {
  Matrix5D A({
      {1, 2, 3, 4, 1},
      {0, 3, 2, 1, 0},
      {2, 1, 1, 0, 0},
      {0, 1, 0, 0, 0},
      {3, 0, 0, 0, 0}
  });
  EXPECT_NEAR(A.Gauss(), 3.0, DIFFERENCE);
}

TEST(Tests, Test_3_Determinant) {
  Matrix5D A({
      {2, 3, 4, 5, 1},
      {1, 0, 4, 1, 2},
      {0, 0, 1, 1, 4},
      {0, 1, 2, 4, 2},
      {3, 2, 2, 3, 1}
  });
  EXPECT_NEAR(A.Gauss(), -139.0, DIFFERENCE);
}

TEST(Tests, Test_4_Determinant) {
  Matrix5D A({
      {9, 8, 8, 9, 1},
      {2, 2, 3, 1.00, 2},
      {1, 1, 1, 1, 0},
      {3, 1, 2, 4, 0},
      {0, 1, 0, 1, 0}
  });
  EXPECT_NEAR(A.Gauss(), -6.0, DIFFERENCE);
}

TEST(Tests, Test_5_Determinant) {
  Matrix5D A({
      {1, 2, 3, 4, 5},
      {2, 2, 3, 1.00, 2},
      {1, 1, 1, 1, 0},
      {3, 1, 2, 4, 0},
      {0, 1, 0, 1, 0}
  });
  EXPECT_NEAR(A.Gauss(), 6.0, DIFFERENCE);
}

TEST(Tests, Test_6_Determinant) {
  Matrix5D A({
      {1, 2, 3, 4, 5},
      {2, 1, 3, 7, 0},
      {1, 1, 1, 1, 0},
      {3, 1, 2, 4, 0},
      {0, 1, 0, 1, 0}
  });
  EXPECT_NEAR(A.Gauss(), -45.0, DIFFERENCE);
}

TEST(Tests, Test_7_Determinant) {
  Matrix5D A({
      {1, 1, 3, 4, 5},
      {2, 0, 3, 7, 0},
      {1, 7, 1, 1, 0},
      {3, 4, 2, 4, 0},
      {0, 8, 0, 1, 0}
  });
  EXPECT_NEAR(A.Gauss(), -395.0, DIFFERENCE);
}

TEST(Tests, Test_8_Determinant) {
  Matrix5D A({
      {1, 1, 3, 4, 5},
      {2, 0, 3, 7, 0},
      {1, 7, 1, 0, 0},
      {3, 4, 0, 0, 0},
      {77, 0, 0, 0, 0}
  });
  EXPECT_NEAR(A.Gauss(), 10780.0, DIFFERENCE);
}

TEST(Tests, Test_9_Determinant) {
  Matrix5D A({
      {1, 1, 3, 4, 5},
      {2, 0, 3, 7, 0},
      {1, 7, 1, 0, 0},
      {3, 4, 0, 0, 0},
      {77, 0, 0, 0, 0}
  });
  EXPECT_NEAR(A.Gauss(), 10780.0, DIFFERENCE);
}

TEST(Tests, Test_10_Determinant) {
  Matrix5D A({
      {11, 1, 3, 4, 5},
      {2, 0, 3, 7, 1},
      {1, 7, 1, 0, 30},
      {3, 4, 0, 0, 0},
      {77, 0, 4, 8, 0}
  });
  EXPECT_NEAR(A.Gauss(), -66288.0, DIFFERENCE);
}

TEST(Tests, Test_11_Determinant) {
  Matrix5D A({
      {2, 0, 0, 0, 0},
      {0, 1, 3, 7, 3},
      {1, 7, 7, 4, 9},
      {3, 4, 0, 0, 0},
      {77, 0, 0, 11, 0}
  });
  EXPECT_NEAR(A.Gauss(), -528.0, DIFFERENCE);
}

TEST(Tests, Test_21_Equation_function_I) {
  Matrix5D A({
      {69, 2, 3, 4, 5}, 
      {4, 69, 3, 7, 0}, 
      {3, 1, 69, 1, 0}, 
      {1, 1, 2, 69, 0},   
      {2, 1, 0, 1, 69}
  });
  Vector5D B{2, 1, 3, 7, 7};
  Vector5D R{0.0141227531425317, 0.0017275517908462, 0.0413896279325196, 0.1000198614377041, 0.0995653200070491};

  EXPECT_EQ(A.Equation(A, B), R);
} 

TEST(Tests, Test_22_Equation_function_II) {
  Matrix5D A({
      {1, 2, 1, 4, 5}, 
      {4, 3, 3, 1, 0}, 
      {3, 1, 0, 1, 0}, 
      {11, 1, 2, 0, 9},   
      {2, 1, 0, 1, 17}
  });
  Vector5D B{4, 2, 1, 0, 2};
  Vector5D R{-0.0912913, 0.613213, -0.045045, 0.660661, 0.0534535};

  EXPECT_EQ(A.Equation(A, B), R);
} 

TEST(Tests, Test_23_Equation_function_III) {
  Matrix5D A({
      {2, 1, 1, 1, 2}, 
      {2, 2, 3, 1, 2}, 
      {1, 1.5, 1, 1, 0}, 
      {3, 1, 2, 4, 0},   
      {3, 2, 2, 0, 1}
  });
  Vector5D B{9, 8, 8, 9, 1};
  Vector5D R{-2.74286, 6.68571, -3.84286, 4.55714, 3.54286};

  EXPECT_EQ(A.Equation(A, B), R);
} 

TEST(Tests, Test_24_Equation_function_IV) {
  Matrix5D A({
      {2, 2, 1, 3, 3}, 
      {1, 2, 1.5, 1, 2}, 
      {1, 3, 1, 2, 2}, 
      {1, 1, 1, 4, 0},   
      {2, 2, 0, 0, 1}
  });
  Vector5D B{9, 8, 8, 9, 1};
  Vector5D R{-0.13, 0.47, 3.51, 1.29, 0.31};

  EXPECT_EQ(A.Equation(A, B), R);
} 

TEST(Tests, Test_25_Rotation_X_I) {
  Vector3D B{1, 0, 0};
  Vector3D R{1, 0, 0};
  EXPECT_EQ(rotateX(B, M_PI / 2), R);
}

TEST(Tests, Test_26_Rotation_X_II) {
  Vector3D B{0, 1, 0};
  Vector3D R{0, 0, 1};
  EXPECT_EQ(rotateX(B, M_PI / 2), R);
}

TEST(Tests, Test_27_Rotation_X_III) {
  Vector3D B{0, 0, 1};
  Vector3D R{0, -1, 0};
  EXPECT_EQ(rotateX(B, M_PI / 2), R);
}

TEST(Tests, Test_28_Rotation_Y_I) {
  Vector3D B{1, 0, 0};
  Vector3D R{1, 0, 0};
  EXPECT_EQ(rotateX(B, M_PI / 2), R);
}

TEST(Tests, Test_29_Rotation_Y_II) {
  Vector3D B{0, 1, 0};
  Vector3D R{0, 1, 0};
  EXPECT_EQ(rotateY(B, M_PI / 2), R);
}

TEST(Tests, Test_30_Rotation_Y_III) {
  Vector3D B{0, 0, 1};
  Vector3D R{1, 0, 0};
  EXPECT_EQ(rotateY(B, M_PI / 2), R);
}

TEST(Tests, Test_31_Rotation_Z_I) {
  Vector3D B{1, 0, 0};
  Vector3D R{0, 1, 0};
  EXPECT_EQ(rotateZ(B, M_PI / 2), R);
}

TEST(Tests, Test_32_Rotation_Z_II) {
  Vector3D B{0, 1, 0};
  Vector3D R{-1, 0, 0};
  EXPECT_EQ(rotateZ(B, M_PI / 2), R);
}

TEST(Tests, Test_33_Rotation_Z_III) {
  Vector3D B{0, 0, 1};
  Vector3D R{0, 0, 1};
  EXPECT_EQ(rotateZ(B, M_PI / 2), R);
}

TEST(Tests, Test_34_Wektor_bledu_I) {
  Matrix5D A({
      {69, 2, 3, 4, 5},
      {4, 69, 3, 7, 0},
      {3, 1, 69, 1, 0},
      {1, 1, 2, 69, 0},
      {2, 1, 0, 1, 69}
  });
  Vector5D B{2, 1, 3, 7, 7};
  Vector5D R{0, 0, 0, 0, 0};

  Vector5D X = A.Equation(A, B);
  EXPECT_EQ(A.ErrorVector(A, X, B), R);
}

TEST(Tests, Test_35_Wektor_bledu_II) {
  Matrix5D A({
      {1, 2, 1, 4, 5},
      {4, 3, 3, 1, 0},
      {3, 1, 0, 1, 0},
      {11, 1, 2, 0, 9},
      {2, 1, 0, 1, 17}
  });
  Vector5D B{2, 1, 3, 7, 7};
  Vector5D R{0, 0, 0, 0, 0};

  Vector5D X = A.Equation(A, B);
  EXPECT_EQ(A.ErrorVector(A, X, B), R);
}

TEST(Tests, Test_36_Wektor_bledu_III) {
  Matrix5D A({
      {2, 1, 1, 1, 2},
      {2, 2, 3, 1, 2},
      {1, 1.5, 1, 1, 0},
      {3, 1, 2, 4, 0},
      {3, 2, 2, 0, 1}
  });
  Vector5D B{2, 1, 3, 7, 7};
  Vector5D R{0, 0, 0, 0, 0};

  Vector5D X = A.Equation(A, B);
  EXPECT_EQ(A.ErrorVector(A, X, B), R);
}

TEST(Tests, Test_37_Wektor_bledu_IV) {
  Matrix5D A({
      {1, 2, 3, 0, 0},
      {5, 3, 3, 4, 1},
      {3, 0, 0, 1, 4},
      {1, 2, 2, 69, 0},
      {2, 1, 8, 1, 0}
  });
  Vector5D B{2, 1, 3, 7, 7};
  Vector5D R{0, 0, 0, 0, 0};

  Vector5D X = A.Equation(A, B);
  EXPECT_EQ(A.ErrorVector(A, X, B), R);
}
