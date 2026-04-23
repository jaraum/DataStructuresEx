//
// Created by wangjiacheng on 2026/4/17.
//

#include "bt.h"
#include <stdio.h>

BinaryTree InitExampleTree();
void Order(BinaryTree *bt);
void Count(BinaryTree *bt);
void Swap(BinaryTree *bt);


int main(void) {
  BinaryTree mytree = InitExampleTree();
  Order(&mytree);
  Count(&mytree);
  Swap(&mytree);
  printf("New tree order:");
  Order(&mytree);
  return 0;
}

BinaryTree InitExampleTree() {
  BinaryTree a, b, x, y, z;
  Create(&a);
  Create(&b); // a,b as empty node
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

void Order(BinaryTree *bt) {
  printf("Preorder: ");
  PreOrderTree(bt);
  printf("\t\tInorder: ");
  InOrderTree(bt);
  printf("\t\tPostorder: ");
  PostOrderTree(bt);
  printf("\n");
}

void Count(BinaryTree *bt) {
  printf("Node number: %d\n", TreeSize(bt));
  printf("Leaf number: %d\n", GetLeafNum(bt));
  printf("Height: %d\n", GetTreeHeight(bt));
}

void Swap(BinaryTree *bt) {
  SwapTrees(bt);
}