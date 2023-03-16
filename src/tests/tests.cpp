#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

void fillMatrixWithStep(const S21Matrix &m, double step) {
  double num = 0;
  for (int i = 0; i < m.GetRows(); i++) {
    for (int j = 0; j < m.GetCols(); j++) {
      m(i, j) = num;
      num += step;
    }
  }
}

void fillMatrix(const S21Matrix &m, double val) {
  for (int i = 0; i < m.GetRows(); i++) {
    for (int j = 0; j < m.GetCols(); j++) {
      m(i, j) = val;
    }
  }
}

TEST(test, constructor_default_1) {
  S21Matrix m;
  EXPECT_EQ(m.GetRows(), 0);
  EXPECT_EQ(m.GetCols(), 0);
}

TEST(test, constructor_with_parameters_1) {
  S21Matrix m(1, 1);
  EXPECT_EQ(m.GetRows(), 1);
  EXPECT_EQ(m.GetCols(), 1);
}

TEST(test, constructor_with_parameters_2) {
  S21Matrix m(300, 400);
  EXPECT_EQ(m.GetRows(), 300);
  EXPECT_EQ(m.GetCols(), 400);
}

TEST(test, constructor_with_parameters_3) {
  EXPECT_THROW(S21Matrix m(-1, 4), std::invalid_argument);
}

TEST(test, constructor_with_parameters_4) {
  EXPECT_THROW(S21Matrix m(2, 0), std::invalid_argument);
}

TEST(test, constructor_copy_1) {
  S21Matrix m1 = S21Matrix(2, 2);
  S21Matrix m2(m1);
  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_EQ(m2.GetCols(), 2);
}

TEST(test, constructor_move_1) {
  S21Matrix m1 = S21Matrix(100, 200);
  S21Matrix m2(std::move(m1));
  EXPECT_EQ(m2.GetRows(), 100);
  EXPECT_EQ(m2.GetCols(), 200);
  EXPECT_EQ(m1.GetRows(), 0);
  EXPECT_EQ(m1.GetCols(), 0);
}

TEST(test, seters_1) {
  S21Matrix m = S21Matrix(11, 22);
  fillMatrixWithStep(m, 1);
  EXPECT_NE(m.GetRows(), 15);
  m.SetRows(15);
  EXPECT_EQ(m.GetRows(), 15);
  EXPECT_EQ(m(14, 21), 0);
}

TEST(test, seters_2) {
  S21Matrix m = S21Matrix(11, 22);
  EXPECT_NE(m.GetRows(), 15);
  EXPECT_THROW(m.SetRows(0), std::invalid_argument);
}

TEST(test, seters_3) {
  S21Matrix m = S21Matrix(10, 10);
  fillMatrixWithStep(m, 1);
  EXPECT_NE(m.GetCols(), 2);
  m.SetCols(2);
  EXPECT_EQ(m.GetCols(), 2);
  EXPECT_EQ(m(1, 1), 11);
}

TEST(test, seters_4) {
  S21Matrix m = S21Matrix(2, 2);
  fillMatrixWithStep(m, 1);
  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_EQ(m.GetCols(), 2);
  m.SetRows(3);
  m.SetCols(3);
  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 3);
  S21Matrix expect = S21Matrix(3, 3);
  expect(0, 0) = 0;
  expect(0, 1) = 1;
  expect(0, 2) = 0;
  expect(1, 0) = 2;
  expect(1, 1) = 3;
  expect(1, 2) = 0;
  expect(2, 0) = 0;
  expect(2, 1) = 0;
  expect(2, 2) = 0;
  EXPECT_TRUE(expect == m);
}

TEST(test, seters_5) {
  S21Matrix m = S21Matrix(3, 3);
  fillMatrixWithStep(m, 1);
  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 3);
  m.SetRows(2);
  m.SetCols(2);
  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_EQ(m.GetCols(), 2);
  S21Matrix expect = S21Matrix(2, 2);
  expect(0, 0) = 0;
  expect(0, 1) = 1;
  expect(1, 0) = 3;
  expect(1, 1) = 4;
  EXPECT_TRUE(expect == m);
}

TEST(test, eq_1) {
  S21Matrix m1 = S21Matrix(4, 5);
  S21Matrix m2 = S21Matrix(4, 5);
  EXPECT_TRUE(m1.EqMatrix(m2));
}

TEST(test, eq_2) {
  S21Matrix m1 = S21Matrix(4, 5);
  S21Matrix m2 = S21Matrix(5, 4);
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(test, eq_3) {
  S21Matrix m1 = S21Matrix(4, 5);
  S21Matrix m2 = S21Matrix(4, 5);
  fillMatrixWithStep(m1, 1.2);
  fillMatrixWithStep(m2, 1.2);
  EXPECT_TRUE(m1.EqMatrix(m2));
  EXPECT_EQ(m1(0, 2), 2.4);
}

TEST(test, eq_4) {
  S21Matrix m1 = S21Matrix(11, 22);
  S21Matrix m2 = S21Matrix(11, 22);
  fillMatrixWithStep(m1, 0.2);
  fillMatrixWithStep(m2, 0.2);
  m2(3, 6) = 11;
  EXPECT_FALSE(m1 == m2);
}

TEST(test, eq_5) {
  S21Matrix m1 = S21Matrix(11, 22);
  S21Matrix m2 = S21Matrix();
  EXPECT_THROW(m1.EqMatrix(m2), std::logic_error);
}

TEST(test, sum_1) {
  S21Matrix m1 = S21Matrix(4, 4);
  S21Matrix m2 = S21Matrix(4, 3);
  EXPECT_THROW(m1.SumMatrix(m2), std::logic_error);
}

TEST(test, sum_2) {
  S21Matrix m1 = S21Matrix(4, 4);
  S21Matrix m2 = S21Matrix();
  EXPECT_THROW(m1.SumMatrix(m2), std::logic_error);
}

TEST(test, sum_3) {
  S21Matrix m1 = S21Matrix(4, 4);
  S21Matrix m2 = S21Matrix(4, 4);
  S21Matrix expect = S21Matrix(4, 4);
  fillMatrixWithStep(m1, 1);
  fillMatrixWithStep(m2, 2);
  fillMatrixWithStep(expect, 3);
  S21Matrix result = m1 + m2;
  EXPECT_TRUE(result.EqMatrix(expect));
}

TEST(test, sum_4) {
  S21Matrix m1 = S21Matrix(4, 4);
  S21Matrix m2 = S21Matrix(4, 4);
  S21Matrix expect = S21Matrix(4, 4);
  fillMatrix(m1, 5);
  fillMatrix(m2, 6);
  fillMatrix(expect, 11);
  m1 += m2;
  EXPECT_TRUE(expect == m1);
}

TEST(test, sub_1) {
  S21Matrix m1 = S21Matrix(4, 4);
  S21Matrix m2 = S21Matrix(4, 4);
  S21Matrix expect = S21Matrix(4, 4);
  fillMatrixWithStep(m1, 3);
  fillMatrixWithStep(m2, 2);
  fillMatrixWithStep(expect, 1);
  m1 -= m2;
  EXPECT_EQ(m1(1, 3), 7);
  EXPECT_TRUE(m1.EqMatrix(expect));
}

TEST(test, sub_2) {
  S21Matrix m1 = S21Matrix(2, 2);
  S21Matrix m2 = S21Matrix(2, 2);
  S21Matrix expect = S21Matrix(2, 2);
  fillMatrixWithStep(m1, -1);
  fillMatrixWithStep(m2, 2);
  fillMatrixWithStep(expect, -3);
  EXPECT_TRUE((m1 - m2).EqMatrix(expect));
}

TEST(test, mult_num_1) {
  S21Matrix m = S21Matrix(4, 4);
  S21Matrix expect = S21Matrix(4, 4);
  fillMatrixWithStep(m, 2.5);
  m *= 2;
  fillMatrixWithStep(expect, 5);
  EXPECT_EQ(m(0, 3), 15);
  EXPECT_TRUE(m.EqMatrix(expect));
}

TEST(test, mult_num_2) {
  S21Matrix m = S21Matrix(2, 3);
  S21Matrix expect = S21Matrix(2, 3);
  fillMatrixWithStep(m, 10);
  S21Matrix result = m * 3;
  fillMatrixWithStep(expect, 30);
  EXPECT_TRUE(result == expect);
}

TEST(test, mult_num_3) {
  S21Matrix m = S21Matrix();
  EXPECT_THROW(m.MulNumber(-1), std::logic_error);
}

TEST(test, mult_mtrx_1) {
  S21Matrix m1 = S21Matrix(3, 4);
  S21Matrix m2 = S21Matrix(4, 3);
  S21Matrix expect = S21Matrix(3, 3);
  fillMatrixWithStep(m1, 1);
  fillMatrixWithStep(m2, 2);
  m1 *= m2;
  expect(0, 0) = 84;
  expect(0, 1) = 96;
  expect(0, 2) = 108;
  expect(1, 0) = 228;
  expect(1, 1) = 272;
  expect(1, 2) = 316;
  expect(2, 0) = 372;
  expect(2, 1) = 448;
  expect(2, 2) = 524;
  EXPECT_TRUE(m1.EqMatrix(expect));
}

TEST(test, mult_mtrx_2) {
  S21Matrix m1 = S21Matrix(2, 3);
  S21Matrix m2 = S21Matrix(3, 3);
  S21Matrix expect = S21Matrix(2, 3);
  fillMatrixWithStep(m1, -1.1);
  fillMatrixWithStep(m2, 0.2);
  S21Matrix result = m1 * m2;
  expect(0, 0) = -3.3;
  expect(0, 1) = -3.96;
  expect(0, 2) = -4.62;
  expect(1, 0) = -9.24;
  expect(1, 1) = -11.88;
  expect(1, 2) = -14.52;
  EXPECT_TRUE(result == expect);
}

TEST(test, mult_mtrx_3) {
  S21Matrix m1 = S21Matrix(4, 3);
  S21Matrix m2 = S21Matrix(4, 4);
  EXPECT_THROW(m1 *= m2, std::logic_error);
}

TEST(test, mult_mtrx_4) {
  S21Matrix m1 = S21Matrix();
  S21Matrix m2 = S21Matrix(4, 4);
  EXPECT_THROW(m1 *= m2, std::logic_error);
}

TEST(test, mult_mtrx_5) {
  S21Matrix m1 = S21Matrix(2, 3);
  S21Matrix m2 = S21Matrix();
  EXPECT_THROW(m1 *= m2, std::logic_error);
}

TEST(test, transpose_1) {
  S21Matrix m = S21Matrix();
  EXPECT_THROW(m.Transpose(), std::logic_error);
}

TEST(test, transpose_2) {
  S21Matrix m = S21Matrix(3, 4);
  fillMatrixWithStep(m, 1.01);
  S21Matrix result = m.Transpose();
  S21Matrix expect = S21Matrix(4, 3);
  expect(0, 0) = 0;
  expect(0, 1) = 4.04;
  expect(0, 2) = 8.08;
  expect(1, 0) = 1.01;
  expect(1, 1) = 5.05;
  expect(1, 2) = 9.09;
  expect(2, 0) = 2.02;
  expect(2, 1) = 6.06;
  expect(2, 2) = 10.1;
  expect(3, 0) = 3.03;
  expect(3, 1) = 7.07;
  expect(3, 2) = 11.11;
  EXPECT_EQ(result.GetRows(), 4);
  EXPECT_EQ(result.GetCols(), 3);
  EXPECT_TRUE(result == expect);
}

TEST(test, calc_complements_1) {
  S21Matrix m = S21Matrix(1, 1);
  m(0, 0) = 5;
  S21Matrix result = m.CalcComplements();
  EXPECT_EQ(result(0, 0), 5);
}

TEST(test, calc_complements_2) {
  S21Matrix m = S21Matrix(2, 2);
  S21Matrix expect = S21Matrix(2, 2);
  fillMatrixWithStep(m, 1);
  S21Matrix result = m.CalcComplements();
  expect(0, 0) = 3;
  expect(0, 1) = -2;
  expect(1, 0) = -1;
  expect(1, 1) = 0;
  EXPECT_TRUE(expect == result);
}

TEST(test, determinant_1) {
  S21Matrix m = S21Matrix(3, 3);
  fillMatrixWithStep(m, 2);
  EXPECT_EQ(m.Determinant(), 0);
}

TEST(test, determinant_2) {
  S21Matrix m = S21Matrix(6, 6);
  fillMatrixWithStep(m, 1);
  m(0, 0) = -0.99;
  m(0, 4) = -99;
  m(2, 2) = -76.12;
  m(4, 0) = 25.1;
  m(5, 1) = -1.11;
  EXPECT_FLOAT_EQ(m.Determinant(), -7868693.5);
}

TEST(test, determinant_3) {
  S21Matrix m = S21Matrix(7, 7);
  fillMatrixWithStep(m, -1);
  m(0, 0) = 5;
  m(0, 1) = -1.33;
  m(2, 4) = 0;
  m(3, 1) = 1;
  m(3, 6) = 2.122;
  m(5, 3) = -1;
  m(6, 3) = 1.1;
  m(6, 6) = 2;
  EXPECT_FLOAT_EQ(m.Determinant(), -241258500);
}

TEST(test, determinant_4) {
  S21Matrix m = S21Matrix();
  EXPECT_THROW(m.Determinant(), std::logic_error);
}

TEST(test, determinant_5) {
  S21Matrix m = S21Matrix(10, 9);
  EXPECT_THROW(m.Determinant(), std::logic_error);
}

TEST(test, inverse_1) {
  S21Matrix m = S21Matrix(1, 1);
  m(0, 0) = -5.11;
  S21Matrix result = m.InverseMatrix();
  EXPECT_FLOAT_EQ(result(0, 0), -0.195694716);
}

TEST(test, inverse_2) {
  S21Matrix m = S21Matrix(2, 2);
  fillMatrixWithStep(m, 1);
  S21Matrix result = m.InverseMatrix();
  S21Matrix expect = S21Matrix(2, 2);
  expect(0, 0) = -1.5;
  expect(0, 1) = 0.5;
  expect(1, 0) = 1;
  expect(1, 1) = 0;
  EXPECT_TRUE(expect == result);
}

TEST(test, inverse_3) {
  S21Matrix m = S21Matrix(4, 4);
  fillMatrixWithStep(m, 1.1);
  m(0, 0) = 11;
  m(2, 2) = 11;
  m(3, 2) = -10;
  S21Matrix result = m.InverseMatrix();
  S21Matrix expect = S21Matrix(4, 4);
  expect(0, 0) = 0.090909091;
  expect(0, 1) = -0.181818182;
  expect(0, 2) = 0.090909091;
  expect(0, 3) = 0;
  expect(1, 0) = -0.136363636;
  expect(1, 1) = -0.957587688;
  expect(1, 2) = 0.61972083;
  expect(1, 3) = 0.019685039;
  expect(2, 0) = 0;
  expect(2, 1) = -0.039370079;
  expect(2, 2) = 0.078740157;
  expect(2, 3) = -0.039370079;
  expect(3, 0) = 0.045454545;
  expect(3, 1) = 0.951503221;
  expect(3, 2) = -0.562097351;
  expect(3, 3) = 0.019685039;
  EXPECT_TRUE(expect == result);
}

TEST(test, inverse_4) {
  S21Matrix m = S21Matrix(5, 6);
  fillMatrixWithStep(m, 1);
  EXPECT_THROW(m.InverseMatrix(), std::logic_error);
}

TEST(test, inverse_5) {
  S21Matrix m = S21Matrix();
  EXPECT_THROW(m.InverseMatrix(), std::logic_error);
}

TEST(test, operator_brackets_1) {
  S21Matrix m = S21Matrix(3, 3);
  EXPECT_THROW(m(-1, 1), std::out_of_range);
}

TEST(test, operator_brackets_2) {
  S21Matrix m = S21Matrix(3, 3);
  EXPECT_THROW(m(2, 3), std::out_of_range);
}

TEST(test, operator_eq_1) {
  S21Matrix m1 = S21Matrix(5, 4);
  fillMatrixWithStep(m1, 1);
  S21Matrix m2 = S21Matrix();
  S21Matrix m3 = S21Matrix();
  m3 = m2 = m1;
  EXPECT_TRUE(m1 == m2);
  EXPECT_TRUE(m2 == m3);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
