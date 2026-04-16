//
// Created by wangjiacheng on 2026/4/2.
//
#include "polynomial.h"

#include <stdio.h>
#include <stdlib.h>

Status Init(Polynomial *P) {
  P->head = NULL;
  P->length = 0;
  return OK;
}

Status Insert(Polynomial *P, int i, int coef, int exp) {
  PNode *pre, *cur;
  if (i < -1 || i > P->length - 1) return ERROR;

  pre = P->head;
  for (int j = 0; j < i; j++) pre = pre->link;

  cur = (PNode *)malloc(sizeof(PNode));
  cur->coef = coef;
  cur->exp = exp;

  if (i > -1) {
    cur->link = pre->link;
    pre->link = cur;
  } else {
    cur->link = P->head;
    P->head = cur;
  }

  P->length++;
  return OK;
}

Status Output(Polynomial *P) {
  PNode *p;
  if (!P) return ERROR;
  int first = 1;
  p = P->head;

  while (p) {
    if (p->coef == 0) {
      p = p->link;
      continue;
    }
    if (!first) {
      printf(p->coef > 0 ? " + " : " - ");
      printf("%dx^%d", abs(p->coef), p->exp);
    } else {
      printf("%d", abs(p->coef));
    }
    p = p->link;
    first = 0;
  }
  printf("\n");
  return OK;
}

void Destroy(Polynomial *P) {
  PNode *p;
  while (P->head) {
    p = P->head->link;
    free(P->head);
    P->head = p;
  }
}

Status Plus(Polynomial *A, Polynomial *B, Polynomial *C) {
  PNode *pa, *pb, *temp, *node;

  if (!A || !B || !C) return ERROR;

  Init(C);
  pa = A->head;
  pb = B->head;

  while (pa && pb) {
    if (pa->exp > pb->exp) {
      // expA > expB
      temp = (PNode *)malloc(sizeof(PNode));
      temp->coef = pa->coef;
      temp->exp = pa->exp;
      temp->link = NULL;
      pa = pa->link;
    } else if (pa->exp < pb->exp) {
      // expA < expB
      temp = (PNode *)malloc(sizeof(PNode));
      temp->coef = pb->coef;
      temp->exp = pb->exp;
      temp->link = NULL;
      pb = pb->link;
    } else {
      if (pa->coef + pb->coef != 0) {
        temp = (PNode *)malloc(sizeof(PNode));
        temp->coef = pa->coef + pb->coef;
        temp->exp = pa->exp;
        temp->link = NULL;
      } else {
        temp = NULL;
      }
      pa = pa->link;
      pb = pb->link;
    }

    // 下面是AI实现的功能，用于将temp有序插入到C
    if (temp) {
      if (!C->head || C->head->exp > temp->exp) {
        // 插入到表头
        temp->link = C->head;
        C->head = temp;
      } else {
        // 找合适的位置插入
        node = C->head;
        while (node->link && node->link->exp < temp->exp) {
          node = node->link;
        }
        temp->link = node->link;
        node->link = temp;
      }
      C->length++;
    }
  }

  // 处理AorB的剩余项（使用同样的有序插入逻辑）
  while (pa) {
    temp = (PNode *)malloc(sizeof(PNode));
    temp->coef = pa->coef;
    temp->exp = pa->exp;
    temp->link = NULL;

    if (!C->head || C->head->exp > temp->exp) {
      temp->link = C->head;
      C->head = temp;
    } else {
      node = C->head;
      while (node->link && node->link->exp < temp->exp) {
        node = node->link;
      }
      temp->link = node->link;
      node->link = temp;
    }
    C->length++;
    pa = pa->link;
  }

  while (pb) {
    temp = (PNode *)malloc(sizeof(PNode));
    temp->coef = pb->coef;
    temp->exp = pb->exp;
    temp->link = NULL;

    if (!C->head || C->head->exp > temp->exp) {
      temp->link = C->head;
      C->head = temp;
    } else {
      node = C->head;
      while (node->link && node->link->exp < temp->exp) {
        node = node->link;
      }
      temp->link = node->link;
      node->link = temp;
    }
    C->length++;
    pb = pb->link;
  }

  return OK;
}

Status Multiply(Polynomial *A, Polynomial *B, Polynomial *C) {
  PNode *pa, *pb, *temp, *node;
  int new_coef, new_exp;

  if (!A || !B || !C) return ERROR;

  Init(C);

  for (pa = A->head; pa; pa = pa->link) {
    for (pb = B->head; pb; pb = pb->link) {
      new_coef = pa->coef * pb->coef;
      new_exp = pa->exp + pb->exp;
      temp = (PNode *)malloc(sizeof(PNode));
      temp->coef = new_coef;
      temp->exp = new_exp;
      temp->link = NULL;

      // 有序插入到C中，处理相同指数的合并
      if (!C->head) {
        // C为空，直接作为表头
        C->head = temp;
        C->length++;
      } else if (C->head->exp > temp->exp) {
        // 插入到表头
        temp->link = C->head;
        C->head = temp;
        C->length++;
      } else if (C->head->exp == temp->exp) {
        // 表头指数相同，系数相加
        C->head->coef += temp->coef;
        free(temp);
      } else {
        // 在链表中间或表尾找合适位置
        node = C->head;
        while (node->link && node->link->exp < temp->exp) {
          node = node->link;
        }

        if (node->link && node->link->exp == temp->exp) {
          // 找到相同指数的项，系数相加
          node->link->coef += temp->coef;
          free(temp);
        } else {
          // 新位置插入
          temp->link = node->link;
          node->link = temp;
          C->length++;
        }
      }
    }
  }
  return OK;
}
