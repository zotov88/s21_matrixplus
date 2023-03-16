#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

#define EPS 1e-7

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  int GetRows() const;
  int GetCols() const;
  void SetRows(const int rows);
  void SetCols(const int cols);

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);

  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  S21Matrix operator*(const S21Matrix& other) const;

  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  void operator*=(const double num);
  void operator*=(const S21Matrix& other);

  double& operator()(const int i, const int j) const;
  S21Matrix& operator=(const S21Matrix& other);
  bool operator==(const S21Matrix& other) const;

 private:
  int rows_, cols_;
  double** matrix_;

  bool IsValidMatrix_() const;
  bool IsSquareMatrix_() const;
  bool IsEqSizeMatrix_(const S21Matrix& other) const;

  double GetDet_(const int size) const;
  int GetSign_(const int indRow, const int indCol) const;

  void ResizeMatrix_(const int rows, const int cols);
  void SumOrSubMatrix_(const S21Matrix& other, char sign);
  void FillMatrixByZero_();
  void CreateMinorMatrix_(const S21Matrix& other);
  void CreateMatrixForDet_(const S21Matrix& other, const int Is, const int Js);
  void CheckMatrixAndSize_() const;
};

#endif  // SRC_S21_MATRIX_OOP_H_
