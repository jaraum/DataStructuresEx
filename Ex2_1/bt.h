//
// Created by wangjiacheng on 2026/4/17.
//

#ifndef EX2_1_BT_H
#define EX2_1_BT_H

#include <stdbool.h>
#define OK 0
#define ERROR 1

typedef int ElemType;

typedef struct btnode {
  ElemType element;
  struct btnode *lChild;
  struct btnode *rChild;
} BTNode;

typedef struct binarytree {
  BTNode *root;
} BinaryTree;

void Create(BinaryTree *bt);
BTNode *NewNode(ElemType x, BTNode *ln, BTNode *rn);
bool GetRootVal(BinaryTree *bt, ElemType *x);
void MakeTree(BinaryTree *bt, ElemType e,BinaryTree *left, BinaryTree *right);

#endif //EX2_1_BT_H
