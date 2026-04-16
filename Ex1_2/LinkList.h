//
// Created by wangjiacheng on 26-3-31.
//

#ifndef LINKLIST_H
#define LINKLIST_H

#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4
#define Duplicate 5

typedef int Status;
typedef int ElemType;

typedef struct node {
  ElemType element;
  struct node *link;
} Node;
typedef struct headerList {
  Node *head;
  int n;
} HeaderList;

Status Init(HeaderList *L);
Status Find(HeaderList L, int i, ElemType *x);
Status Insert(HeaderList *L, int i, ElemType x);
Status Delete(HeaderList *L, int i);
Status Output(HeaderList *L);
Status Reverse(HeaderList *L);
Status Sort(HeaderList *L);
void Destroy(HeaderList *L);

#endif  // LINKLIST_H
