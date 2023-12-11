#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>
using namespace std;

template <class T> class Matrix {

private:
  T **matrix;
  int rows;
  int cols;

public:
  struct Coords {
    int x;
    int y;

    Coords() {}
    Coords(int cx, int cy) {
      x = cx;
      y = cy;
    }

    friend ostream &operator<<(ostream &out, const Coords &c) {
      out << c.x << " " << c.y;
      return out;
    }

    friend int operator-(const Coords &c1, const Coords &c2) {
      int d1 = c1.x - c2.x;
      int d2 = c1.y - c2.y;
      return sqrt(pow(d1, 2) + pow(d2, 2));
    }
  };

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
    matrix = new T *[rows];
    for (int i = 0; i < rows; i++) {
      matrix[i] = new T[cols];
      for (int j = 0; j < cols; j++) {
        matrix[i][j] = init;
      }
    }
  }

  int get_rows() const { return rows; }
  int get_cols() const { return cols; }

  T *operator[](int row) { return matrix[row]; }

  T *const &operator[](int row) const { return matrix[row]; }

  T &operator[](Coords c) { return matrix[c.x][c.y]; }

  T const &operator[](Coords c) const { return matrix[c.x][c.y]; }

  bool in_bounds(int x, int y) const {
    bool x_ok = x >= 0 && x < rows;
    bool y_ok = y >= 0 && y < cols;
    return x_ok && y_ok;
  }

  bool in_bounds(const Coords &c) const { return in_bounds(c.x, c.y); }

  long int to_arr_pos(int x, int y) const { return x * cols + y; }

  long int to_arr_pos(const Coords &c) const { return to_arr_pos(c.x, c.y); }

  Coords from_arr_pos(long int i) const {
    Coords c;
    c.x = i / rows;
    c.y = i % cols;
    return c;
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
