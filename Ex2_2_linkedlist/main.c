//
// Created by wangjiacheng on 2026/4/23.
//

#include "hfmTree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void PrintCodes(const HFMCodeTable *table, const ElemType symbols[], int count);

int main(void) {
  const ElemType symbols[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                              'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

  const int weights[] = {817, 149, 278, 425, 1270, 223, 202, 609, 697, 15,  77, 403, 241,
                         675, 751, 193, 10,  599,  633, 906, 276, 98,  236, 15, 197, 7};

  const int count = (int) (sizeof(symbols) / sizeof(symbols[0]));
  const char *sourceText = "HELLOWORLD";

  BinaryTree tree;
  HFMCodeTable codeTable;
  char *encoded = NULL;
  char *decoded = NULL;

  if (CreateHuffmanTree(symbols, weights, count, &tree) != OK) {
    printf("CreateHuffmanTree failed\n");
    return 1;
  }

  if (CreateHuffmanCode(&tree, &codeTable) != OK) {
    printf("GenerateHuffmanCodes failed\n");
    ClearHuffmanTree(&tree);
    return 1;
  }

  printf("Huffman codes:\n");
  PrintCodes(&codeTable, symbols, count);

  if (EncodeText(sourceText, &codeTable, &encoded) != OK) {
    printf("EncodeText failed\n");
    DestroyHuffmanCodes(&codeTable);
    ClearHuffmanTree(&tree);
    return 1;
  }

  if (DecodeBits(encoded, &tree, &decoded) != OK) {
    printf("DecodeBits failed\n");
    free(encoded);
    DestroyHuffmanCodes(&codeTable);
    ClearHuffmanTree(&tree);
    return 1;
  }

  printf("\nSource : %s\n", sourceText);
  printf("Encoded: %s\n", encoded);
  printf("Decoded: %s\n", decoded);

  if (strcmp(sourceText, decoded) == 0) {
    printf("Round-trip check: PASS\n");
  } else {
    printf("Round-trip check: FAIL\n");
  }

  free(encoded);
  free(decoded);
  DestroyHuffmanCodes(&codeTable);
  ClearHuffmanTree(&tree);
  return 0;
}


static void PrintCodes(const HFMCodeTable *table, const ElemType symbols[], int count) {
  for (int i = 0; i < count; ++i) {
    const unsigned char symbol = (unsigned char) symbols[i];
    printf("%c: %s\n", symbol, table->codes[symbol]);
  }
}
