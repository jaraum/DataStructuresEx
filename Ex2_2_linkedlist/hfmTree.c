//
// Created by wangjiacheng on 2026/4/23.
//

#include "hfmTree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HFMTNode *CreateNode(const ElemType element, const int w, HFMTNode *lChild, HFMTNode *rChild) {
  HFMTNode *p = (HFMTNode *) malloc(sizeof(HFMTNode));
  if (!p) {
    printf("malloc error, please try again!");
    return NULL;
  }
  p->element = element;
  p->w = w;
  p->lChild = lChild;
  p->rChild = rChild;
  return p;
}

bool IsLeaf(const HFMTNode *node) { return node != NULL && node->lChild == NULL && node->rChild == NULL; }

void Clear(HFMTNode *node) {
  if (!node)
    return;
  Clear(node->lChild);
  Clear(node->rChild);
  free(node);
  node = NULL;
}

int DuplicateString(const char *src, char **dst) {
  const size_t len = strlen(src);
  *dst = (char *) malloc(len + 1);
  if (*dst == NULL) {
    return ERROR;
  }
  memcpy(*dst, src, len + 1);
  return OK;
}

void ClearHuffmanTree(BinaryTree *tree) {
  if (!tree) {
    return;
  }
  Clear(tree->root);
  tree->root = NULL;
}

void DestroyHuffmanCodes(HFMCodeTable *table) {
  if (!table)
    return;
  for (int i = 0; i < HFM_SYMBOL_RANGE; ++i) {
    free(table->codes[i]);
    table->codes[i] = NULL;
  }
}

PriorityQueue *CreatePQ(const int capacity) {
  PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
  if (!pq)
    return NULL;
  pq->data = (HFMTNode **) malloc(sizeof(HFMTNode *) * (capacity + 1));
  if (!pq->data) {
    free(pq);
    return NULL;
  }
  pq->size = 0;
  pq->capacity = capacity;
  return pq;
}

void InsertPQ(PriorityQueue *pq, HFMTNode *node) {
  if (pq->size == pq->capacity)
    return;
  int i = ++pq->size;
  while (i > 1 && pq->data[i / 2]->w > node->w) {
    pq->data[i] = pq->data[i / 2];
    i /= 2;
  }
  pq->data[i] = node;
}

HFMTNode *Serve(PriorityQueue *pq) {
  if (pq->size == 0)
    return NULL;
  HFMTNode *minNode = pq->data[1];
  HFMTNode *lastNode = pq->data[pq->size--];
  int i = 1;
  while (i * 2 <= pq->size) {
    int child = i * 2;
    if (child != pq->size && pq->data[child + 1]->w < pq->data[child]->w) {
      child++;
    }
    if (lastNode->w > pq->data[child]->w) {
      pq->data[i] = pq->data[child];
      i = child;
    } else {
      break;
    }
  }
  pq->data[i] = lastNode;
  return minNode;
}

void DestroyPQ(PriorityQueue *pq) {
  free(pq->data);
  free(pq);
}

void MakeTree(BinaryTree *bt, const ElemType e, BinaryTree *lChild, BinaryTree *rChild) {
  if (bt == NULL || lChild == NULL || rChild == NULL) {
    return;
  }
  if (bt->root != NULL || lChild == rChild) {
    return;
  }

  HFMTNode *left = lChild->root;
  HFMTNode *right = rChild->root;
  int w = (left ? left->w : 0) + (right ? right->w : 0);

  bt->root = CreateNode(e, w, left, right);

  lChild->root = NULL;
  rChild->root = NULL;
}

int CreateHuffmanTree(const ElemType symbols[], const int weights[], int count, BinaryTree *tree) {
  if (count <= 0)
    return ERROR;
  PriorityQueue *pq = CreatePQ(count);
  if (!pq)
    return ERROR;

  for (int i = 0; i < count; ++i) {
    HFMTNode *node = CreateNode(symbols[i], weights[i], NULL, NULL);
    if (!node) {
      DestroyPQ(pq);
      return ERROR;
    }
    InsertPQ(pq, node);
  }

  while (pq->size > 1) {
    HFMTNode *left = Serve(pq);
    HFMTNode *right = Serve(pq);
    if (!left || !right) {
      DestroyPQ(pq);
      return ERROR;
    }
    BinaryTree leftTree = {left};
    BinaryTree rightTree = {right};
    BinaryTree parentTree = {NULL};
    MakeTree(&parentTree, '\0', &leftTree, &rightTree);
    if (!parentTree.root) {
      DestroyPQ(pq);
      return ERROR;
    }
    InsertPQ(pq, parentTree.root);
  }

  tree->root = Serve(pq);
  DestroyPQ(pq);
  return OK;
}

void TraverseCode(HFMTNode *node, char *code, int depth, HFMCodeTable *table) {
  if (!node)
    return;
  if (IsLeaf(node)) {
    code[depth] = '\0';
    DuplicateString(code, &table->codes[(unsigned char) node->element]);
    return;
  }
  code[depth] = '0';
  TraverseCode(node->lChild, code, depth + 1, table);
  code[depth] = '1';
  TraverseCode(node->rChild, code, depth + 1, table);
}

int CreateHuffmanCode(const BinaryTree *tree, HFMCodeTable *table) {
  if (!tree || !tree->root || !table)
    return ERROR;
  for (int i = 0; i < HFM_SYMBOL_RANGE; ++i)
    table->codes[i] = NULL;
  char code[HFM_SYMBOL_RANGE];
  if (IsLeaf(tree->root)) {
    code[0] = '0';
    code[1] = '\0';
    DuplicateString(code, &table->codes[(unsigned char) tree->root->element]);
    return OK;
  }
  TraverseCode(tree->root, code, 0, table);
  return OK;
}

int EncodeText(const char *text, const HFMCodeTable *table, char **encodedBits) {
  size_t totalLen = 0;
  size_t i;

  if (text == NULL || table == NULL || encodedBits == NULL) {
    return ERROR;
  }

  for (i = 0; text[i] != '\0'; ++i) {
    const char *code = table->codes[(unsigned char) text[i]];
    if (code == NULL) {
      return ERROR;
    }
    totalLen += strlen(code);
  }

  char *result = (char *) malloc(totalLen + 1);
  if (result == NULL) {
    return ERROR;
  }

  result[0] = '\0';
  for (i = 0; text[i] != '\0'; ++i) {
    strcat(result, table->codes[(unsigned char) text[i]]);
  }

  *encodedBits = result;
  return OK;
}

int DecodeBits(const char *bits, const BinaryTree *tree, char **decodedText) {
  size_t outPos = 0;
  size_t i;

  if (bits == NULL || tree == NULL || tree->root == NULL || decodedText == NULL) {
    return ERROR;
  }

  const size_t bitLen = strlen(bits);
  char *result = (char *) malloc(bitLen + 2);
  if (result == NULL) {
    return ERROR;
  }

  if (IsLeaf(tree->root)) {
    for (i = 0; i < bitLen; ++i) {
      if (bits[i] != '0') {
        free(result);
        return ERROR;
      }
      result[outPos++] = (char) tree->root->element;
    }
    result[outPos] = '\0';
    *decodedText = result;
    return OK;
  }

  const HFMTNode *cur = tree->root;
  for (i = 0; i < bitLen; ++i) {
    if (bits[i] == '0') {
      cur = cur->lChild;
    } else if (bits[i] == '1') {
      cur = cur->rChild;
    } else {
      free(result);
      return ERROR;
    }

    if (cur == NULL) {
      free(result);
      return ERROR;
    }

    if (IsLeaf(cur)) {
      result[outPos++] = (char) cur->element;
      cur = tree->root;
    }
  }

  if (cur != tree->root) {
    free(result);
    return ERROR;
  }

  result[outPos] = '\0';
  *decodedText = result;
  return OK;
}
