#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#include "s21_matrix.h"

#define FAIL "FAIL"

START_TEST(createMatrix) {
  matrix_t arrayZMatrixS[2] = {s21_create_matrix(3, 3),
                               s21_create_matrix(3, 1)};
  matrix_t arrayIMatrixS[2] = {s21_create_matrix(0, 0),
                               s21_create_matrix(-18, -1)};

  for (int i = 0; i < 2; i++) {
    ck_assert_msg(arrayZMatrixS[i].matrix_type == ZERO_MATRIX, FAIL);
    s21_remove_matrix(&arrayZMatrixS[i]);

    ck_assert_msg(arrayIMatrixS[i].matrix_type == INCORRECT_MATRIX, FAIL);
    s21_remove_matrix(&arrayIMatrixS[i]);
  }
}

START_TEST(sumMatrix) {
  matrix_t arrayCMatrixS[3] = {s21_create_matrix(3, 3),
                               s21_create_matrix(3, 3),
                               s21_create_matrix(3, 3)};
  matrix_t arrayIMatrixS[2] = {s21_create_matrix(0, 0),
                               s21_create_matrix(0, 0)};
  matrix_t arrayZMatrixS[2] = {s21_create_matrix(3, 3),
                               s21_create_matrix(3, 3)};

  for (int i = 0; i < 3; i++) {
    arrayCMatrixS[i].matrix_type = CORRECT_MATRIX;

    for (int j = 0; j < 3; j++) {
      arrayCMatrixS[0].matrix[i][j] = i + j;
      arrayCMatrixS[1].matrix[i][j] = i + j;
      arrayCMatrixS[2].matrix[i][j] = (i + j) * 2;
    }
  }

  matrix_t resCC = s21_sum_matrix(&arrayCMatrixS[0], &arrayCMatrixS[1]);
  matrix_t resII = s21_sum_matrix(&arrayIMatrixS[0], &arrayIMatrixS[1]);
  matrix_t resZZ = s21_sum_matrix(&arrayZMatrixS[0], &arrayZMatrixS[1]);
  matrix_t resCI = s21_sum_matrix(&arrayCMatrixS[0], &arrayIMatrixS[0]);
  matrix_t resCZ = s21_sum_matrix(&arrayCMatrixS[0], &arrayZMatrixS[0]);
  matrix_t resZI = s21_sum_matrix(&arrayZMatrixS[0], &arrayIMatrixS[0]);
  matrix_t arrayResMatrixS[6] = {resCC, resII, resZZ, resCI, resCZ, resZI};

  ck_assert_msg(s21_eq_matrix(&resCC, &arrayCMatrixS[2]) == 1, FAIL);
  ck_assert_msg(s21_eq_matrix(&resII, &arrayIMatrixS[1]) == 0, FAIL);
  ck_assert_msg(s21_eq_matrix(&resZZ, &arrayZMatrixS[1]) == 1, FAIL);
  ck_assert_msg(s21_eq_matrix(&resCI, &arrayIMatrixS[1]) == 0, FAIL);
  ck_assert_msg(s21_eq_matrix(&resCZ, &arrayCMatrixS[0]) == 1, FAIL);
  ck_assert_msg(s21_eq_matrix(&resZI, &arrayIMatrixS[0]) == 0, FAIL);

  for (int i = 0; i < 6; i++) { s21_remove_matrix(&arrayResMatrixS[i]); }
  for (int i = 0; i < 3; i++) { s21_remove_matrix(&arrayCMatrixS[i]); }
  for (int i = 0; i < 2; i++) {
    s21_remove_matrix(&arrayIMatrixS[i]);
    s21_remove_matrix(&arrayZMatrixS[i]);
  }
}

START_TEST(subMatrix) {
  matrix_t arrayCMatrixS[3] = {s21_create_matrix(3, 3),
                               s21_create_matrix(3, 3),
                               s21_create_matrix(3, 3)};
  matrix_t arrayIMatrixS[2] = {s21_create_matrix(0, 0),
                               s21_create_matrix(0, 0)};
  matrix_t arrayZMatrixS[2] = {s21_create_matrix(3, 3),
                               s21_create_matrix(3, 3)};

  for (int i = 0; i < 3; i++) {
    arrayCMatrixS[i].matrix_type = CORRECT_MATRIX;

    for (int j = 0; j < 3; j++) {
      arrayCMatrixS[0].matrix[i][j] = (i + j) * 2;
      arrayCMatrixS[1].matrix[i][j] = i + j;
      arrayCMatrixS[2].matrix[i][j] = i + j;
    }
  }

  matrix_t resCC = s21_sub_matrix(&arrayCMatrixS[0], &arrayCMatrixS[1]);
  matrix_t resII = s21_sub_matrix(&arrayIMatrixS[0], &arrayIMatrixS[1]);
  matrix_t resZZ = s21_sub_matrix(&arrayZMatrixS[0], &arrayZMatrixS[1]);
  matrix_t resCI = s21_sub_matrix(&arrayCMatrixS[0], &arrayIMatrixS[0]);
  matrix_t resCZ = s21_sub_matrix(&arrayCMatrixS[0], &arrayZMatrixS[0]);
  matrix_t resZI = s21_sub_matrix(&arrayZMatrixS[0], &arrayIMatrixS[0]);
  matrix_t arrayResMatrixS[6] = {resCC, resII, resZZ, resCI, resCZ, resZI};

  ck_assert_msg(s21_eq_matrix(&resCC, &arrayCMatrixS[2]) == 1, FAIL);
  ck_assert_msg(s21_eq_matrix(&resII, &arrayIMatrixS[1]) == 0, FAIL);
  ck_assert_msg(s21_eq_matrix(&resZZ, &arrayZMatrixS[1]) == 1, FAIL);
  ck_assert_msg(s21_eq_matrix(&resCI, &arrayIMatrixS[1]) == 0, FAIL);
  ck_assert_msg(s21_eq_matrix(&resCZ, &arrayCMatrixS[0]) == 1, FAIL);
  ck_assert_msg(s21_eq_matrix(&resZI, &arrayIMatrixS[0]) == 0, FAIL);

  for (int i = 0; i < 6; i++) { s21_remove_matrix(&arrayResMatrixS[i]); }
  for (int i = 0; i < 3; i++) { s21_remove_matrix(&arrayCMatrixS[i]); }
  for (int i = 0; i < 2; i++) {
    s21_remove_matrix(&arrayIMatrixS[i]);
    s21_remove_matrix(&arrayZMatrixS[i]);
  }
}

START_TEST(multNumberMatrix) {
  matrix_t arrayCMatrixS[3] = {s21_create_matrix(2, 2),
                               s21_create_matrix(2, 2),
                               s21_create_matrix(2, 2)};
  matrix_t arrayIMatrixS[2] = {s21_create_matrix(0, 0),
                               s21_create_matrix(0, 0)};
  matrix_t arrayZMatrixS[2] = {s21_create_matrix(2, 2),
                               s21_create_matrix(2, 2)};

  for (int i = 0; i < 2; i++) {
    arrayCMatrixS[i].matrix_type = CORRECT_MATRIX;

    for (int j = 0; j < 2; j++) {
      arrayCMatrixS[0].matrix[i][j] = 3.27;
      arrayCMatrixS[1].matrix[i][j] = 31.392;
      arrayCMatrixS[2].matrix[i][j] = -31.392;
    }
  }

  matrix_t resC = s21_mult_number(&arrayCMatrixS[0], 9.6);
  matrix_t resI = s21_mult_number(&arrayIMatrixS[0], 9.6);
  matrix_t resZ = s21_mult_number(&arrayZMatrixS[0], 9.6);
  matrix_t resCN = s21_mult_number(&arrayCMatrixS[0], -9.6);
  matrix_t resIN = s21_mult_number(&arrayIMatrixS[0], -9.6);
  matrix_t resZN = s21_mult_number(&arrayZMatrixS[0], -9.6);
  matrix_t arrayResMatrixS[6] = {resC, resI, resZ, resCN, resIN, resZN};

  ck_assert_msg(s21_eq_matrix(&resC, &arrayCMatrixS[1]) == 1, FAIL);
  ck_assert_msg(s21_eq_matrix(&resI, &arrayIMatrixS[1]) == 0, FAIL);
  ck_assert_msg(s21_eq_matrix(&resZ, &arrayZMatrixS[1]) == 1, FAIL);
  ck_assert_msg(s21_eq_matrix(&resCN, &arrayCMatrixS[2]) == 1, FAIL);
  ck_assert_msg(s21_eq_matrix(&resIN, &arrayIMatrixS[1]) == 0, FAIL);
  ck_assert_msg(s21_eq_matrix(&resZN, &arrayZMatrixS[1]) == 1, FAIL);

  for (int i = 0; i < 6; i++) { s21_remove_matrix(&arrayResMatrixS[i]); }
  for (int i = 0; i < 3; i++) { s21_remove_matrix(&arrayCMatrixS[i]); }
  for (int i = 0; i < 2; i++) {
    s21_remove_matrix(&arrayIMatrixS[i]);
    s21_remove_matrix(&arrayZMatrixS[i]);
  }
}

START_TEST(multMatrix) {
  matrix_t arrayCMatrixS[3] = {s21_create_matrix(3, 3),
                               s21_create_matrix(3, 3),
                               s21_create_matrix(3, 3)};
  matrix_t arrayIMatrixS[2] = {s21_create_matrix(0, 0),
                               s21_create_matrix(0, 0)};
  matrix_t arrayZMatrixS[2] = {s21_create_matrix(3, 3),
                               s21_create_matrix(3, 3)};

  for (int i = 0; i < 3; i++) {
    arrayCMatrixS[i].matrix_type = CORRECT_MATRIX;

    for (int j = 0; j < 3; j++) {
      arrayCMatrixS[0].matrix[i][j] = 3.2;
      arrayCMatrixS[1].matrix[i][j] = 2.13;
      arrayCMatrixS[2].matrix[i][j] = 20.448;
    }
  }

  matrix_t resCC = s21_mult_matrix(&arrayCMatrixS[0], &arrayCMatrixS[1]);
  matrix_t resII = s21_mult_matrix(&arrayIMatrixS[0], &arrayIMatrixS[1]);
  matrix_t resZZ = s21_mult_matrix(&arrayZMatrixS[0], &arrayZMatrixS[1]);
  matrix_t resCI = s21_mult_matrix(&arrayCMatrixS[0], &arrayIMatrixS[0]);
  matrix_t resCZ = s21_mult_matrix(&arrayCMatrixS[0], &arrayZMatrixS[0]);
  matrix_t resZI = s21_mult_matrix(&arrayZMatrixS[0], &arrayIMatrixS[0]);
  matrix_t arrayResMatrixS[6] = {resCC, resII, resZZ, resCI, resCZ, resZI};

  ck_assert_msg(s21_eq_matrix(&resCC, &arrayCMatrixS[2]) == 1, FAIL);
  ck_assert_msg(s21_eq_matrix(&resII, &arrayIMatrixS[1]) == 0, FAIL);
  ck_assert_msg(s21_eq_matrix(&resZZ, &arrayZMatrixS[1]) == 1, FAIL);
  ck_assert_msg(s21_eq_matrix(&resCI, &arrayIMatrixS[1]) == 0, FAIL);
  ck_assert_msg(s21_eq_matrix(&resCZ, &arrayZMatrixS[0]) == 1, FAIL);
  ck_assert_msg(s21_eq_matrix(&resZI, &arrayIMatrixS[0]) == 0, FAIL);

  for (int i = 0; i < 6; i++) { s21_remove_matrix(&arrayResMatrixS[i]); }
  for (int i = 0; i < 3; i++) { s21_remove_matrix(&arrayCMatrixS[i]); }
  for (int i = 0; i < 2; i++) {
    s21_remove_matrix(&arrayIMatrixS[i]);
    s21_remove_matrix(&arrayZMatrixS[i]);
  }
}

START_TEST(transposeMatrix) {
  matrix_t arrayCMatrixS[2] = {s21_create_matrix(2, 3),
                               s21_create_matrix(3, 2)};
  matrix_t arrayIMatrixS[2] = {s21_create_matrix(0, 0),
                               s21_create_matrix(0, 0)};
  matrix_t arrayZMatrixS[2] = {s21_create_matrix(2, 3),
                               s21_create_matrix(3, 2)};
  double value = 0;

  for (int i = 0; i < 2; i++) {
    arrayCMatrixS[i].matrix_type = CORRECT_MATRIX;

    for (int j = 0; j < 3; j++) {
      arrayCMatrixS[0].matrix[i][j] = value;
      arrayCMatrixS[1].matrix[j][i] = value++;
    }
  }

  matrix_t resC = s21_transpose(&arrayCMatrixS[0]);
  matrix_t resI = s21_transpose(&arrayIMatrixS[0]);
  matrix_t resZ = s21_transpose(&arrayZMatrixS[0]);
  matrix_t arrayResMatrixS[3] = {resC, resI, resZ};

  ck_assert_msg(s21_eq_matrix(&resC, &arrayCMatrixS[1]) == 1, FAIL);
  ck_assert_msg(s21_eq_matrix(&resI, &arrayIMatrixS[1]) == 0, FAIL);
  ck_assert_msg(s21_eq_matrix(&resZ, &arrayZMatrixS[1]) == 1, FAIL);

  for (int i = 0; i < 3; i++) { s21_remove_matrix(&arrayResMatrixS[i]); }
  for (int i = 0; i < 2; i++) {
    s21_remove_matrix(&arrayCMatrixS[i]);
    s21_remove_matrix(&arrayIMatrixS[i]);
    s21_remove_matrix(&arrayZMatrixS[i]);
  }
}

START_TEST(calcComplementsMatrix) {
  matrix_t arrayCMatrixS[2] = {s21_create_matrix(3, 3),
                               s21_create_matrix(3, 3)};
  matrix_t arrayIMatrixS[2] = {s21_create_matrix(0, 0),
                               s21_create_matrix(0, 0)};
  matrix_t arrayZMatrixS[2] = {s21_create_matrix(3, 3),
                               s21_create_matrix(3, 3)};
  int valuesCMatrixS1[9] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  int valuesCMatrixS2[9] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
  int counter = 0;

  for (int i = 0; i < 3; i++) {
    if (i > 0) { arrayCMatrixS[i - 1].matrix_type = CORRECT_MATRIX; }

    for (int j = 0; j < 3; j++) {
      arrayCMatrixS[0].matrix[i][j] = valuesCMatrixS1[counter];
      arrayCMatrixS[1].matrix[i][j] = valuesCMatrixS2[counter++];
    }
  }

  matrix_t resC = s21_calc_complements(&arrayCMatrixS[0]);
  matrix_t resI = s21_calc_complements(&arrayIMatrixS[0]);
  matrix_t resZ = s21_calc_complements(&arrayZMatrixS[0]);
  matrix_t arrayResMatrixS[3] = {resC, resI, resZ};

  ck_assert_msg(s21_eq_matrix(&resC, &arrayCMatrixS[1]) == 1, FAIL);
  ck_assert_msg(s21_eq_matrix(&resI, &arrayIMatrixS[1]) == 0, FAIL);
  ck_assert_msg(s21_eq_matrix(&resZ, &arrayZMatrixS[1]) == 1, FAIL);

  for (int i = 0; i < 3; i++) { s21_remove_matrix(&arrayResMatrixS[i]); }
  for (int i = 0; i < 2; i++) {
    s21_remove_matrix(&arrayCMatrixS[i]);
    s21_remove_matrix(&arrayIMatrixS[i]);
    s21_remove_matrix(&arrayZMatrixS[i]);
  }
}

START_TEST(inverseMatrix) {
  matrix_t arrayCMatrixS[2] = {s21_create_matrix(3, 3),
                               s21_create_matrix(3, 3)};
  matrix_t arrayIMatrixS[2] = {s21_create_matrix(0, 0),
                               s21_create_matrix(0, 0)};
  matrix_t arrayZMatrixS[2] = {s21_create_matrix(3, 3),
                               s21_create_matrix(3, 3)};
  int valuesCMatrixS1[9] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  int valuesCMatrixS2[9] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
  int counter = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      arrayCMatrixS[0].matrix[i][j] = valuesCMatrixS1[counter];
      arrayCMatrixS[1].matrix[i][j] = valuesCMatrixS2[counter++];
    }
  }

  matrix_t resC = s21_inverse_matrix(&arrayCMatrixS[0]);
  matrix_t resI = s21_inverse_matrix(&arrayIMatrixS[0]);
  matrix_t resZ = s21_inverse_matrix(&arrayZMatrixS[0]);
  matrix_t arrayResMatrixS[3] = {resC, resI, resZ};

  ck_assert_msg(s21_eq_matrix(&resC, &arrayCMatrixS[1]) == 1, FAIL);
  ck_assert_msg(s21_eq_matrix(&resI, &arrayIMatrixS[1]) == 0, FAIL);
  ck_assert_msg(s21_eq_matrix(&resZ, &arrayZMatrixS[1]) == 0, FAIL);

  for (int i = 0; i < 3; i++) { s21_remove_matrix(&arrayResMatrixS[i]); }
  for (int i = 0; i < 2; i++) {
    s21_remove_matrix(&arrayCMatrixS[i]);
    s21_remove_matrix(&arrayIMatrixS[i]);
    s21_remove_matrix(&arrayZMatrixS[i]);
  }
}

START_TEST(determinantMatrix) {
  matrix_t matrixSC = s21_create_matrix(3, 3);
  matrix_t matrixSI = s21_create_matrix(0, 0);
  matrix_t matrixSZ = s21_create_matrix(5, 5);
  matrix_t arrayMatrixS[3] = {matrixSC, matrixSI, matrixSZ};
  int valuesMatrixSC[9] = {1, -2, 3, 4, 0, 6, -7, 8, 9};
  int counter = 0;
  double result = 204;

  matrixSC.matrix_type = CORRECT_MATRIX;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrixSC.matrix[i][j] = valuesMatrixSC[counter++];
    }
  }

  double resC = s21_determinant(&matrixSC);
  double resI = s21_determinant(&matrixSI);
  double resZ = s21_determinant(&matrixSZ);

  ck_assert_msg(resC == result, FAIL);
  ck_assert_msg(resI != NAN, FAIL);
  ck_assert_msg(resZ == 0, FAIL);

  for (int i = 0; i < 3; i++) { s21_remove_matrix(&arrayMatrixS[i]); }
}

START_TEST(eqMatrix) {
  matrix_t arrayCMatrixS[3] = {s21_create_matrix(2, 3),
                               s21_create_matrix(2, 3)};
  matrix_t arrayIMatrixS[2] = {s21_create_matrix(0, 0),
                               s21_create_matrix(0, 0)};
  matrix_t arrayZMatrixS[2] = {s21_create_matrix(2, 3),
                               s21_create_matrix(2, 3)};

  for (int i = 0; i < 2; i++) {
    arrayCMatrixS[i].matrix_type = CORRECT_MATRIX;

    for (int j = 0; j < 3; j++) {
      arrayCMatrixS[0].matrix[i][j] = i + j;
      arrayCMatrixS[1].matrix[i][j] = i + j;
    }
  }

  int resC = s21_eq_matrix(&arrayCMatrixS[0], &arrayCMatrixS[1]);
  int resI = s21_eq_matrix(&arrayIMatrixS[0], &arrayIMatrixS[1]);
  int resZ = s21_eq_matrix(&arrayZMatrixS[0], &arrayZMatrixS[1]);

  ck_assert_msg(resC == 1, FAIL);
  ck_assert_msg(resI == 0, FAIL);
  ck_assert_msg(resZ == 1, FAIL);

  for (int i = 0; i < 3; i++) {
    s21_remove_matrix(&arrayCMatrixS[i]);
    s21_remove_matrix(&arrayIMatrixS[i]);
    s21_remove_matrix(&arrayZMatrixS[i]);
  }
}

START_TEST(removeMatrix) {
  matrix_t arrayZMatrixS[2] = {s21_create_matrix(3, 3),
                               s21_create_matrix(3, 1)};
  matrix_t arrayIMatrixS[2] = {s21_create_matrix(0, 0),
                               s21_create_matrix(-18, -1)};

  for (int i = 0; i < 2; i++) {
    s21_remove_matrix(&arrayZMatrixS[i]);
    ck_assert_msg(arrayZMatrixS[i].matrix == NULL, FAIL);

    s21_remove_matrix(&arrayIMatrixS[i]);
    ck_assert_msg(arrayIMatrixS[i].matrix == NULL, FAIL);
  }
}

Suite *Suite_create(void) {
  Suite *s21_matrix = suite_create("s21_matrix");
  TCase *tcase_test = tcase_create("test");

  tcase_add_test(tcase_test, createMatrix);
  tcase_add_test(tcase_test, sumMatrix);
  tcase_add_test(tcase_test, subMatrix);
  tcase_add_test(tcase_test, multNumberMatrix);
  tcase_add_test(tcase_test, multMatrix);
  tcase_add_test(tcase_test, transposeMatrix);
  tcase_add_test(tcase_test, calcComplementsMatrix);
  tcase_add_test(tcase_test, inverseMatrix);
  tcase_add_test(tcase_test, determinantMatrix);
  tcase_add_test(tcase_test, eqMatrix);
  tcase_add_test(tcase_test, removeMatrix);

  suite_add_tcase(s21_matrix, tcase_test);

  return s21_matrix;
}

int main(void) {
  Suite *suite = Suite_create();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);

  int failed_count = srunner_ntests_failed(suite_runner);

  srunner_free(suite_runner);

  return (failed_count != 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}
