//
// Created by wangjiacheng on 2026/4/23.
//

#ifndef EX2_2_HFMTREE_H
#define EX2_2_HFMTREE_H

#define OK 0
#define ERROR 1
#define HFM_SYMBOL_RANGE 30

typedef char ElemType;
typedef struct hfmtNode {
  ElemType element;
  int w; // weight
  struct hfmtNode *lChild;
  struct hfmtNode *rChild;
} HFMTNode;

typedef struct binaryTree {
  HFMTNode *root;
} BinaryTree;

typedef struct hfmCodeTable {
  char *codes[HFM_SYMBOL_RANGE];
} HFMCodeTable;

typedef struct {
  HFMTNode **data;
  int size;
  int capacity;
} PriorityQueue;

int CreateHuffmanTree(const ElemType symbols[], const int weights[], int count, BinaryTree *tree);
int CreateHuffmanCode(const BinaryTree *tree, HFMCodeTable *table);
int EncodeText(const char *text, const HFMCodeTable *table, char **encodedBits);
int DecodeBits(const char *bits, const BinaryTree *tree, char **decodedText);
void ClearHuffmanTree(BinaryTree *tree);
void DestroyHuffmanCodes(HFMCodeTable *table);
void MakeTree(BinaryTree *bt, ElemType e, BinaryTree *lChild, BinaryTree *rChild);

#endif // EX2_2_HFMTREE_H
