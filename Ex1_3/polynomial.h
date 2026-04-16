//
// Created by wangjiacheng on 2026/4/2.
//

#ifndef EX1_3_POLYNOMIAL_H
#define EX1_3_POLYNOMIAL_H

#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4
#define Duplicate 5

typedef int Status;

typedef struct pNode {
  int coef;   //系数
  int exp;    //指数
  struct pNode *link;
} PNode;

typedef struct polynomial {
  PNode *head;
  int length;
} Polynomial;

Status Init(Polynomial *P);
Status Insert(Polynomial *P, int i, int coef, int exp);
Status Output(Polynomial *P);
void Destroy(Polynomial *P);
Status Plus(Polynomial *A, Polynomial *B, Polynomial *C);
Status Multiply(Polynomial *A, Polynomial *B, Polynomial *C);

#endif  // EX1_3_POLYNOMIAL_H
