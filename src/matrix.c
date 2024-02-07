#include "matrix.h"

#include <math.h>
#include <stdlib.h>

matrix_t get_cropped_matrix(matrix_t *A, int x, int y);
double get_minor_elem(matrix_t *A, int x, int y);
int is_square_matrix(matrix_t *A);
int eq_size_matrix(matrix_t *A, matrix_t *B);
int check_type_matrix(matrix_t *A);
void set_type_matrix(matrix_t *A);

matrix_t create_matrix(int rows, int columns) {
  matrix_t matrixS;

  if (rows >= 1 && columns >= 1) {
    matrixS.matrix_type = ZERO_MATRIX;
  } else {
    matrixS.matrix_type = INCORRECT_MATRIX;
  }

  matrixS.rows = rows;
  matrixS.columns = columns;

  if (matrixS.matrix_type == ZERO_MATRIX) {
    matrixS.matrix = (double **)malloc(rows * sizeof(double *));

    for (int i = 0; i < rows; i++) {
      matrixS.matrix[i] = (double *)malloc(columns * sizeof(double));

      for (int j = 0; j < columns; j++) {
        matrixS.matrix[i][j] = 0.0f;
      }
    }
  } else {
    matrixS.matrix = NULL;
  }

  return matrixS;
}

matrix_t sum_matrix(matrix_t *A, matrix_t *B) {
  matrix_t matrixS = create_matrix(0, 0);

  if (A != NULL && B != NULL) {
    if (check_type_matrix(A) && check_type_matrix(B)) {
      if (eq_size_matrix(A, B)) {
        int rows = A->rows;
        int columns = A->columns;
        matrixS = create_matrix(rows, columns);

        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < columns; j++) {
            matrixS.matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          }
        }

        set_type_matrix(&matrixS);
      }
    }
  }

  return matrixS;
}

matrix_t sub_matrix(matrix_t *A, matrix_t *B) {
  matrix_t matrixS = create_matrix(0, 0);

  if (A != NULL && B != NULL) {
    if (check_type_matrix(A) && check_type_matrix(B)) {
      if (eq_size_matrix(A, B)) {
        int rows = A->rows;
        int columns = A->columns;
        matrixS = create_matrix(rows, columns);

        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < columns; j++) {
            matrixS.matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
          }
        }

        set_type_matrix(&matrixS);
      }
    }
  }

  return matrixS;
}

matrix_t mult_number(matrix_t *A, double number) {
  matrix_t matrixS = create_matrix(0, 0);

  if (A != NULL && !isnan(number)) {
    if (check_type_matrix(A)) {
      int rows = A->rows;
      int columns = A->columns;
      matrixS = create_matrix(rows, columns);

      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
          matrixS.matrix[i][j] = A->matrix[i][j] * number;
        }
      }

      set_type_matrix(&matrixS);
    }
  }

  return matrixS;
}

matrix_t mult_matrix(matrix_t *A, matrix_t *B) {
  matrix_t matrixS = create_matrix(0, 0);

  if (A != NULL && B != NULL) {
    if (check_type_matrix(A) && check_type_matrix(B)) {
      if (A->columns == B->rows) {
        int rows = A->rows;
        int columns = B->columns;
        double res = 0;
        matrixS = create_matrix(rows, columns);

        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < columns; j++) {
            for (int k = 0; k < B->rows; k++) {
              res += A->matrix[i][k] * B->matrix[k][j];
            }

            matrixS.matrix[i][j] = res;
            res = 0;
          }
        }

        set_type_matrix(&matrixS);
      }
    }
  }

  return matrixS;
}

matrix_t transpose(matrix_t *A) {
  matrix_t matrixS = create_matrix(0, 0);

  if (A != NULL) {
    if (check_type_matrix(A)) {
      int rows = A->rows;
      int columns = A->columns;
      matrixS = create_matrix(A->columns, A->rows);

      for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
          matrixS.matrix[i][j] = A->matrix[j][i];
        }
      }

      set_type_matrix(&matrixS);
    }
  }

  return matrixS;
}

matrix_t calc_complements(matrix_t *A) {
  matrix_t matrixS = create_matrix(0, 0);

  if (A != NULL) {
    if (check_type_matrix(A)) {
      if (is_square_matrix(A)) {
        int rows = A->rows;
        int columns = A->columns;
        matrixS = create_matrix(A->rows, A->columns);

        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < columns; j++) {
            matrixS.matrix[i][j] = pow(-1, i + j) * get_minor_elem(A, i, j);
          }
        }

        if (A->columns == 1 && A->rows == 1) {
          matrixS = create_matrix(1, 1);
          matrixS.matrix[0][0] = 1;
        }

        set_type_matrix(&matrixS);
      }
    }
  }

  return matrixS;
}

matrix_t inverse_matrix(matrix_t *A) {
  matrix_t matrixSRes = create_matrix(0, 0);

  if (A != NULL) {
    if (check_type_matrix(A)) {
      if (determinant(A) != 0) {
        if (is_square_matrix(A)) {
          matrix_t complemetsMatrixS = calc_complements(A);
          matrix_t matrixS = transpose(&complemetsMatrixS);
          matrixSRes = mult_number(&matrixS, 1/determinant(A));

          remove_matrix(&complemetsMatrixS);
          remove_matrix(&matrixS);

          set_type_matrix(&matrixSRes);
        }
      }
    }
  }

  return matrixSRes;
}

double determinant(matrix_t *A) {
  double result = NAN;

  if (A != NULL) {
    if (check_type_matrix(A)) {
      if (is_square_matrix(A)) {
        result = 0;

        if (A->rows == 2) {
          result += A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
        } else if (A->rows > 2) {
          matrix_t matrixS = create_matrix(A->rows - 1, A->columns - 1);

          for (int col = 0; col < A->columns; col++) {
            for (int col2 = 0; col2 < A->columns - 1; col2++) {
              for (int row = 0, k = 0; row < A->rows - 1; row++, k++) {
                if (row == col) { k++; }

                matrixS.matrix[col2][row] = A->matrix[col2 + 1][k];
              }
            }

            result += pow(-1, (double)col) * A->matrix[0][col] * determinant(&matrixS);
          }

          remove_matrix(&matrixS);
        }
      }
    }
  }

  if (A->columns == 1 && A->rows == 1) { result = A->matrix[0][0]; }

  return result;
}

matrix_t get_cropped_matrix(matrix_t *A, int x, int y) {
  matrix_t matrixS;
  int rows = A->rows, columns = A->columns;

  if (x >= rows || x < 0 || y >= columns || y < 0) {
    matrixS = create_matrix(0, 0);
  } else {
    matrixS = create_matrix(rows - 1, columns - 1);

    for (int i = 0, iA = 0; i < matrixS.rows; i++, iA++) {
      if (iA == x) { iA++; }

      for (int j = 0, jA = 0; j < matrixS.columns; j++, jA++) {
        if (jA == y) { jA++; }

        matrixS.matrix[i][j] = A->matrix[iA][jA];
      }
    }

    set_type_matrix(&matrixS);
  }

  return matrixS;
}

double get_minor_elem(matrix_t *A, int x, int y) {
  double res = 0;
  int rows = A->rows, columns = A->columns;

  if (!is_square_matrix(A) || x >= rows || x < 0 || y >= columns || y < 0) {
    res = NAN;
  } else {
    matrix_t croppedMatrixS = get_cropped_matrix(A, x, y);
    res = determinant(&croppedMatrixS);

    remove_matrix(&croppedMatrixS);
  }

  return res;
}

int is_square_matrix(matrix_t *A) {
  return (A->rows == A->columns) ? SUCCESS : FAILURE;
}

int eq_matrix(matrix_t *A, matrix_t *B) {
  int isEqual = FAILURE;

  if (A != NULL && B != NULL) {
    if (check_type_matrix(A) && check_type_matrix(B)) {
      if (eq_size_matrix(A, B)) {
        int rows = A->rows;
        int columns = A->columns;
        int equalCount = 0;

        for (int i = 0; i < rows; i++) {
          for (int j = 0; j < columns; j++) {
            if (fabs(A->matrix[i][j] - B->matrix[i][j]) < PRECISION) { equalCount++; }
          }
        }

        if (equalCount == rows * columns) { isEqual = SUCCESS; }
      }
    }
  }

  return isEqual;
}

int eq_size_matrix(matrix_t *A, matrix_t *B) {
  return (A->rows == B->rows && A->columns == B->columns) ? SUCCESS : FAILURE;
}

int check_type_matrix(matrix_t *A) {
  return (A->matrix_type != INCORRECT_MATRIX) ? SUCCESS : FAILURE;
}

void set_type_matrix(matrix_t *A) {
  if (A != NULL && check_type_matrix(A)) {
    int flagI = 1, flagZ = 1;
    int rows = A->rows, columns = A->columns;

    if (!is_square_matrix(A)) { flagI = 0; }

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        if (i == j && fabs(A->matrix[i][j] - 1.0) > PRECISION) flagI = 0;
        if (i != j && fabs(A->matrix[i][j]) > PRECISION) flagI = 0;
        if (fabs(A->matrix[i][j]) > PRECISION) flagZ = 0;
      }
    }

    if (rows == 0 || columns == 0) {
      A->matrix_type = INCORRECT_MATRIX;
    } else if (flagI) {
      A->matrix_type = IDENTITY_MATRIX;
    } else if (flagZ) {
      A->matrix_type = ZERO_MATRIX;
    } else {
      A->matrix_type = CORRECT_MATRIX;
    }
  }
}

void remove_matrix(matrix_t *A) {
  if (A != NULL) {
    A->matrix_type = INCORRECT_MATRIX;

    if (A->matrix != NULL) {
      int rows = A->rows;

      for (int i = 0; i < rows; i++) { free(A->matrix[i]); }
      free(A->matrix);

      A->matrix = NULL;
    }

    A->rows = 0;
    A->columns = 0;
  }
}
