#include <stdio.h>

#include "polynomial.h"

int main(void) {
  Polynomial A, B, C;

  Init(&A);
  int coef_A[] = {3, -5, 7};
  int ecp_A[] = {0, 1, 2};
  int len_A = 3;

  for (int i = 0; i < len_A; i++) {
    Insert(&A, i - 1, coef_A[i], ecp_A[i]);
  }
  printf("A = ");
  Output(&A);

  Init(&B);
  int coef_B[] = {1, 3, 2, 5};
  int ecp_B[] = {0, 1, 2, 3};
  int len_B = 4;

  for (int i = 0; i < len_B; i++) {
    Insert(&B, i - 1, coef_B[i], ecp_B[i]);
  }
  printf("B = ");
  Output(&B);

  printf("\n========PLUS DEMO=======\n");
  Init(&C);
  Plus(&A, &B, &C);
  printf("C = ");
  Output(&C);
  Destroy(&C);

  printf("\n========MULTIPLAY DEMO=======\n");
  Init(&C);
  Multiply(&A, &B, &C);
  printf("C = ");
  Output(&C);
  Destroy(&C);

  return 0;
}
