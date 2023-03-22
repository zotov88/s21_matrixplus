#include "s21_matrix_oop.h"

S21Matrix ::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    throw std::invalid_argument("Illegal parameters");
  }
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
  }
  FillMatrixByZero_();
}

S21Matrix ::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) = other(i, j);
    }
  }
}

S21Matrix ::S21Matrix(S21Matrix&& other) noexcept {
  this->matrix_ = other.matrix_;
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  if (IsValidMatrix_()) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
      matrix_[i] = nullptr;
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(const int rows) {
  if (rows_ != rows) {
    ResizeMatrix_(rows, cols_);
  }
}

void S21Matrix::SetCols(const int cols) {
  if (cols_ != cols) {
    ResizeMatrix_(rows_, cols);
  }
}

void S21Matrix::ResizeMatrix_(const int rows, const int cols) {
  if ((rows <= 0) || (cols <= 0)) {
    throw std::invalid_argument("Incorrect size");
  }
  S21Matrix tmp(*this);
  S21Matrix dest(rows, cols);
  dest.FillMatrixByZero_();
  for (int i = 0; i < std::min(dest.rows_, tmp.rows_); i++) {
    for (int j = 0; j < std::min(dest.cols_, tmp.cols_); j++) {
      dest(i, j) = tmp(i, j);
    }
  }
  *this = dest;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (!this->IsValidMatrix_() || !other.IsValidMatrix_()) {
    throw std::logic_error("Incorrect matrix");
  }
  bool result = true;
  if (!this->IsEqSizeMatrix_(other)) {
    result = false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs((*this)(i, j) - other(i, j)) > EPS) {
          result = false;
          break;
        }
      }
    }
  }
  return result;
}

void S21Matrix::SumOrSubMatrix_(const S21Matrix& other, char sign) {
  if (!this->IsValidMatrix_() || !other.IsValidMatrix_()) {
    throw std::logic_error("Incorrect matrix");
  }
  if (!this->IsEqSizeMatrix_(other)) {
    throw std::logic_error("Matrixes are not equals");
  }
  int num = (sign == '-') ? -1 : 1;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) += num * other(i, j);
    }
  }
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  SumOrSubMatrix_(other, '+');
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  SumOrSubMatrix_(other, '-');
}

void S21Matrix::MulNumber(const double num) {
  if (!IsValidMatrix_()) {
    throw std::logic_error("Incorrect matrix");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (!other.IsValidMatrix_()) {
    throw std::logic_error("Incorrect matrix");
  }
  if (this->cols_ != other.rows_) {
    throw std::logic_error("Incorrect dimension of matrices");
  }
  S21Matrix tmp(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < this->cols_; k++) {
        tmp(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  *this = S21Matrix(std::move(tmp));
}

S21Matrix S21Matrix::Transpose() const {
  if (!IsValidMatrix_()) {
    throw std::logic_error("Incorrect matrix");
  }
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(j, i) = (*this)(i, j);
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  CheckMatrixAndSize_();
  S21Matrix result = S21Matrix(rows_, cols_);
  result.CreateMinorMatrix_(*this);
  return result;
}

void S21Matrix::CreateMinorMatrix_(const S21Matrix& other) {
  if (other.cols_ == 1) {
    (*this)(0, 0) = other(0, 0);
  } else {
    S21Matrix tmp;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        tmp.CreateMatrixForDet_(other, i, j);
        (*this)(i, j) = tmp.Determinant() * GetSign_(i, j);
      }
    }
  }
}

void S21Matrix::CreateMatrixForDet_(const S21Matrix& other, const int Is,
                                    const int Js) {
  this->~S21Matrix();
  *this = S21Matrix(other.rows_ - 1, other.cols_ - 1);
  int row = 0;
  for (int i = 0; i < other.rows_; i++) {
    if (i == Is) continue;
    for (int j = 0, col = 0; j < other.cols_; j++) {
      if (j == Js) continue;
      (*this)(row, col++) = other(i, j);
    }
    row++;
  }
}

double S21Matrix::Determinant() const {
  CheckMatrixAndSize_();
  double result = (cols_ > 1) ? GetDet_(cols_) : (*this)(0, 0);
  return result;
}

double S21Matrix::GetDet_(const int size) const {
  double det = 0;
  if (size == 2) {
    det += (*this)(0, 0) * (*this)(1, 1) - (*this)(1, 0) * (*this)(0, 1);
  } else {
    int i = 0;
    while (i < size) {
      S21Matrix tmp;
      tmp.CreateMatrixForDet_(*this, i, 0);
      det += (*this)(i, 0) * GetSign_(i, 0) * tmp.GetDet_(size - 1);
      i++;
    }
  }
  return det;
}

S21Matrix S21Matrix::InverseMatrix() const {
  CheckMatrixAndSize_();
  S21Matrix result = S21Matrix(rows_, cols_);
  if (rows_ == 1) {
    result(0, 0) = 1 / (*this)(0, 0);
  } else if (Determinant() != 0) {
    result = CalcComplements().Transpose();
    result.MulNumber(1 / Determinant());
  } else {
    throw std::logic_error("Determinant = 0");
  }
  return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result = *this;
  result += other;
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result = *this;
  result -= other;
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result = *this;
  result *= num;
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result = *this;
  result *= other;
  return result;
}

void S21Matrix::operator+=(const S21Matrix& other) { SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix& other) { SubMatrix(other); }

void S21Matrix::operator*=(const double num) { MulNumber(num); }

void S21Matrix::operator*=(const S21Matrix& other) { MulMatrix(other); }

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    S21Matrix tmp(other);
    this->~S21Matrix();
    this->rows_ = tmp.rows_;
    this->cols_ = tmp.cols_;
    this->matrix_ = tmp.matrix_;
    tmp.matrix_ = nullptr;
  }
  return *this;
}

double& S21Matrix::operator()(const int i, const int j) const {
  if ((i < 0 || i >= rows_) || (j < 0 || j >= cols_)) {
    throw std::out_of_range("Incorrect index");
  }
  return matrix_[i][j];
}

bool S21Matrix::IsEqSizeMatrix_(const S21Matrix& other) const {
  return this->cols_ == other.cols_ && this->rows_ == other.rows_;
}

bool S21Matrix::IsValidMatrix_() const { return matrix_ != nullptr; }

bool S21Matrix::IsSquareMatrix_() const { return cols_ == rows_; };

int S21Matrix::GetSign_(const int indRow, const int indCol) const {
  return (indRow + indCol) % 2 == 0 ? 1 : -1;
}

void S21Matrix::CheckMatrixAndSize_() const {
  if (!IsValidMatrix_()) {
    throw std::logic_error("Incorrect matrix");
  }
  if (!IsSquareMatrix_()) {
    throw std::logic_error("Incorrect size of matrix");
  }
}

void S21Matrix::FillMatrixByZero_() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      (*this)(i, j) = 0;
    }
  }
}
