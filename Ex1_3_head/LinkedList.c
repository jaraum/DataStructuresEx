//
// Created by wangjiacheng on 2026/4/16.
//

#include <stddef.h>
#include <stdlib.h>
#include "LinkedList.h"

Status Init(Polynomial *list) {
  list->head = (Node *)malloc (sizeof(Node));
  if (!list->head)
    return ERROR;
  list->head->next = NULL;
  list->head->coef = 0;
  list->head->exp = -1;
  list->length = 0;
  return OK;
}

Status Append(Polynomial *list) {

}