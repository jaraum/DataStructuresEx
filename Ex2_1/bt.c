//
// Created by wangjiacheng on 2026/4/17.
//

#include "bt.h"
#include <stdio.h>
#include <stdlib.h>

void Create(BinaryTree *bt) { bt->root = NULL; }

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
    return false;
  *x = bt->root->element;
  return true;
}

void MakeTree(BinaryTree *bt, ElemType e, BinaryTree *left, BinaryTree *right) {
  if (bt->root || left == right)
    return;
  bt->root = NewNode(e, left->root, right->root);
  left->root = right->root = NULL;
}

void Clear(BTNode *t) {
  if (!t)
    return;
  Clear(t->lChild);
  Clear(t->rChild);
  free(t);
}

void TreeClear(BinaryTree *bt) { Clear(bt->root); }

void PreOrder(BTNode *t) {
  if (!t)
    return;
  printf("%c", t->element);
  PreOrder(t->lChild);
  PreOrder(t->rChild);
}

void PreOrderTree(BinaryTree *bt) {
  if (!bt)
    return;
  PreOrder(bt->root);
}

void InOrder(BTNode *t) {
  if (!t)
    return;
  InOrder(t->lChild);
  printf("%c", t->element);
  InOrder(t->rChild);
}

void InOrderTree(BinaryTree *bt) {
  if (!bt)
    return;
  InOrder(bt->root);
}

void PostOrder(BTNode *t) {
  if (!t)
    return;
  PostOrder(t->lChild);
  PostOrder(t->rChild);
  printf("%c", t->element);
}

void PostOrderTree(BinaryTree *bt) {
  if (!bt)
    return;
  PostOrder(bt->root);
}

int Size(BTNode *t) {
  if (!t)
    return 0;
  return Size(t->lChild) + Size((t->rChild)) + 1;
}

int TreeSize(BinaryTree *bt) {
  if (!bt)
    return 0;
  return Size(bt->root);
}

int LeafNum(BTNode *t) {
  if (!t)
    return 0;
  if (t->lChild == NULL && t->rChild == NULL)
    return 1;
  return LeafNum(t->lChild) + LeafNum((t->rChild));
}

int GetLeafNum(BinaryTree *bt) {
  if (!bt)
    return 0;
  return LeafNum(bt->root);
}

int Height(BTNode *t) {
  if (!t)
    return 0;
  int leftHeight = Height(t->lChild);
  int rightHeight = Height(t->rChild);
  return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int GetTreeHeight(BinaryTree *bt) {
  if (!bt)
    return 0;
  return Height(bt->root);
}

void SwapSubTrees(BTNode *t) {
  if (!t)
    return;
  SwapSubTrees(t->lChild);
  SwapSubTrees(t->rChild);

  BTNode *temp = t->lChild;
  t->lChild = t->rChild;
  t->rChild = temp;
}

void SwapTrees(BinaryTree *bt) {
  if (!bt)
    return;
  SwapSubTrees(bt->root);
  printf("Swap finished!\n");
}

