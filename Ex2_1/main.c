//
// Created by wangjiacheng on 2026/4/17.
//

#include <stdio.h>
#include "bt.h"

BinaryTree InitExampleTree();
void Order();

int main(void) {
  Order();
  return 0;
}

BinaryTree InitExampleTree(){
  BinaryTree a, b, x, y, z;
  Create(&a);
  Create(&b);//a,b as empty node
  Create(&x);
  Create(&y);
  Create(&z);
  MakeTree(&y, 'E', &a, &b);
  MakeTree(&z, 'F', &a, &b);
  MakeTree(&x, 'C', &y, &z);
  MakeTree(&y, 'D', &a, &b);
  MakeTree(&z, 'B', &y, &x);
  return z;
}

void Order() {
  BinaryTree mytree = InitExampleTree();

  PreOrderTree(&mytree);
  printf("\n");

  InOrderTree(&mytree);
  printf("\n");

  PostOrderTree(&mytree);
  printf("\n");

  TreeClear(&mytree);
}
