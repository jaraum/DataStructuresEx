//
// Created by wangjiacheng on 26-3-31.
//

#ifndef SEQLIST_H
#define SEQLIST_H

#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4
#define Duplicate 5

typedef int Status;
typedef int ElemType;

typedef struct seqList {
  int length;//长度
  int maxLength;
  ElemType *element;
} SeqList;

Status Init(SeqList *L, int mSize);
Status Find(SeqList L, int i, ElemType *x);
Status Insert(SeqList *L, int i, ElemType x);
Status Delete(SeqList *L, int i, ElemType *x);
Status Output(SeqList *L);
void Destroy(SeqList *L);

#endif // SEQLIST_H
