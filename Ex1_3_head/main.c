//
// Created by wangjiacheng on 2026/4/16.
//

#include <stdio.h>
#include "LinkedList.h"

char InitPolynimial(Polynomial *poly);

void PolynomialAddition();

void PolynomialMultiplication();


int main(void) {
  Polynomial poly1;
  char name1 = InitPolynimial(&poly1);


  void PolynomialAddition();
  void PolynomialMultiplication();
  return 0;
}

// realization
char InitPolynimial(Polynomial *poly) {
  printf("name of your polynomial:");
  char name;
  scanf(" %c", &name);
  InitList(poly);
  return name;
}


void PolynomialAddition() {
  Polynomial C;
  InitList(&C);
}

void PolynomialMultiplication() {
}
