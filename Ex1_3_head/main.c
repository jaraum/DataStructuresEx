//
// Created by wangjiacheng on 2026/4/16.
//

#include <stdio.h>
#include "LinkedList.h"

char InitPolynomial(Polynomial *poly);

void PolynomialAddition();

void PolynomialMultiplication();


int main(void) {
  Polynomial poly1, poly2, polyPlus;
  char name1 = InitPolynomial(&poly1);
  char name2 = InitPolynomial(&poly2);

  // char name3 = PolynomialAddition(&polyPlus);


  // void PolynomialMultiplication();
  return 0;
}


// realization
char InitPolynomial(Polynomial *poly) {
  printf("name of your polynomial:");
  char name;
  scanf(" %c", &name);
  InitList(poly);
  return name;
}


// char PolynomialAddition(Polynomial *polyPlus) {
//   printf("name of your polynomial:");
//   char name;
//   scanf(" %c", &name);
//   InitList(polyPlus);
//   return name;
// }

void PolynomialMultiplication() {
  //TODO
}
