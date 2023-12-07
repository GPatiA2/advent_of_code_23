#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using namespace std;

template <class T> class Matrix {

private:
  T **matrix;
  int rows;
  int cols;

public:
  Matrix(int r, int c) {
    rows = r;
    cols = c;
    matrix = new T *[rows];
    for (int i = 0; i < rows; i++) {
      matrix[i] = new T[cols];
    }
  }

  Matrix(int r, int c, T init) {
    rows = r;
    cols = c;
    cout << "Initializing matrix with " << init << endl;
    matrix = new T *[rows];
    for (int i = 0; i < rows; i++) {
      matrix[i] = new T[cols];
      for (int j = 0; j < cols; j++) {
        matrix[i][j] = init;
      }
    }
    cout << "MATRIX 0 0 HAS " << matrix[0][0] << endl;
  }

  int get_rows() const { return rows; }
  int get_cols() const { return cols; }

  T *operator[](int row) { return matrix[row]; }

  T *const &operator[](int row) const { return matrix[row]; }

  bool in_bounds(int x, int y) {
    bool x_ok = x >= 0 && x < rows;
    bool y_ok = y >= 0 && y < cols;
    return x_ok && y_ok;
  }
};

template <class T>
inline ostream &operator<<(ostream &out, const Matrix<T> &mat) {
  for (int i = 0; i < mat.get_rows(); i++) {
    for (int j = 0; j < mat.get_cols(); j++) {
      out << mat[i][j] << " ";
    }
    out << '\n';
  }
  return out;
}

#endif
