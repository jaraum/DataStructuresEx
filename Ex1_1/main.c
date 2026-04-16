//
// Created by wangjiacheng on 26-3-31.
//

#include <stdio.h>

#include "SeqList.h"

Status main(void) {
  int i;
  SeqList list;
  Init(&list, 10);
  for (i = 0; i < 10; i++)
    Insert(&list, i - 1, i);
  Output(&list);
  int del;
  Delete(&list, 6, &del);
  Output(&list);
  Destroy(&list);

  return 0;
}