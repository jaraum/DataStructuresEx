//
// Created by wangjiacheng on 2026/4/17.
//

#include <stdlib.h>
#include <stdio.h>
#include "bt.h"


void Create(BinaryTree *bt) {
  bt->root = NULL;
}

BTNode *NewNode(ElemType x, BTNode *ln, BTNode *rn) {
  BTNode *p = (BTNode *)malloc(sizeof(BTNode));
  if (p == NULL) {
    printf("malloc error, please try again!");
    return NULL;
  }
  p->element = x;
  p->lChild = ln;
  p->rChild = rn;
  return p;
}

bool GetRootVal(BinaryTree *bt, ElemType *x) {
  if (bt == NULL || !bt->root)
    return  false;
  *x = bt->root->element;
  return true;
}

void MakeTree(BinaryTree *bt, ElemType e,BinaryTree *left, BinaryTree *right) {
  if (bt->root || left == right)
    return;
  bt->root = NewNode(e, left->root, right->root);
  left->root = right->root = NULL;
}