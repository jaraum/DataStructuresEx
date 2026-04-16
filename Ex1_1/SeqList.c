//
// Created by wangjiacheng on 26-3-31.
//
#include <stdio.h>
#include <stdlib.h>

#include "SeqList.h"

Status Init(SeqList *L, int mSize) {
  L->maxLength = mSize;
  L->length = 0;
  L->element = (ElemType *)malloc(sizeof(ElemType) * L->maxLength);
  if (!L->element)
    return ERROR;
  return OK;
}

Status Find(SeqList L, int i, ElemType *x) {
  if (i < 0 || i > L.length - 1)
    return ERROR;
  *x = L.element[i];
  return OK;
}

Status Insert(SeqList *L, int i, ElemType x) {
  int j;
  if (i < -1 || i > L->length - 1)
    return ERROR;
  if (L->length == L->maxLength)
    return ERROR;
  for (j = L->length - 1; j > i; j--)
    L->element[j + 1] = L->element[j];
  L->element[i + 1] = x;
  L->length = L->length + 1;
  return OK;
}

/**
 *不返回删除元素的值
Status Delete(SeqList *L, int i) {
  int j;
  if (i < 0 || i > L->length - 1)
    return ERROR;
  if (!L->length)
    return ERROR;
  for (j = i + 1; j < L->length; j++)
    L->element[j - 1] = L->element[j];
  L->length--;
  return OK;
}
**/

//实现返回删除元素的值
Status Delete(SeqList *L, int i, ElemType *x) {
  int j;
  if (i < 0 || i > L->length - 1)
    return ERROR;
  if (!L->length)
    return ERROR;

  *x = L->element[i]; // ← 保存要删除的元素值

  for (j = i + 1; j < L->length; j++)
    L->element[j - 1] = L->element[j];
  L->length--;
  return OK;
}

Status Output(SeqList *L) {
  int i;
  if (L->length == 0)
    return ERROR;
  for (i = 0; i <= L->length - 1; i++)
    printf("%d", L->element[i]);
  printf("\n");
  return OK;
}

void Destroy(SeqList *L) {
  L->length = 0;
  L->maxLength = 0;
  free(L->element);
}
