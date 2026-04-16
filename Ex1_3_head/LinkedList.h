//
// Created by wangjiacheng on 2026/4/16.
//

#ifndef DSEX_LINKEDLIST_H
#define DSEX_LINKEDLIST_H

#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4
#define Duplicate 5

typedef int Status;

typedef struct Node {
  int coef;
  int exp;
  struct Node *next;
}Node;

typedef struct polynomial {
  Node *head; //头指针
  int length;
}Polynomial;

Status Init(Polynomial *list);
// Status Append();
// Status OutPut();
// Status Destroy();


#endif //DSEX_LINKEDLIST_H
