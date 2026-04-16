//
// Created by wangjiacheng on 26-3-31.
//

#include <stdio.h>

#include "LinkList.h"

int main(void) {
  int i, x;
  HeaderList list;
  Init(&list);

  // 填入元素
  for (i = 0; i < 9; i++) Insert(&list, i - 1, i);
  printf("the linklist is: ");
  Output(&list);

  // 删除首位元素
  Delete(&list, 0);
  printf("\nthe new linklist is: ");
  Output(&list);

  // 查找首位元素的值并打印
  Find(list, 0, &x);
  printf("\nthe value is : ");
  printf("%d", x);

  // 链表逆置
  Reverse(&list);
  printf("\nthe reversed linklist is: ");
  Output(&list);

  // 链表排序
  Sort(&list);
  printf("\nthe sorted linklist is: ");
  Output(&list);

  Destroy(&list);

  return 0;
}
