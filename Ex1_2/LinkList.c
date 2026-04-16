//
// Created by wangjiacheng on 26-3-31.
//
#include "LinkList.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Status Init(HeaderList *L) {
  L->head = NULL;
  L->n = 0;
  return OK;
}

Status Find(HeaderList L, int i, ElemType *x) {
  Node *p;
  int j;
  if (i < 0 || i > L.n - 1) return ERROR;
  p = L.head;
  for (j = 0; j < i; j++) p = p->link;
  *x = p->element;
  return OK;
}

Status Insert(HeaderList *L, int i, ElemType x) {
  Node *p, *q;
  int j;
  if (i < -1 || i > L->n - 1) return ERROR;
  p = L->head;
  for (j = 0; j < i; j++) p = p->link;
  q = (Node *)malloc(sizeof(Node));

  q->element = x;
  if (i > -1) {
    q->link = p->link;
    p->link = q;
  } else {
    q->link = L->head;
    L->head = q;
  }
  L->n++;
  return OK;
}

Status Delete(HeaderList *L, int i) {
  int j;
  Node *p, *q;
  if (!L->n) return ERROR;
  if (i < 0 || i > L->n - 1) return ERROR;
  q = L->head;
  p = L->head;
  for (j = 0; j < i - 1; j++) q = q->link;
  if (i == 0) {
    L->head = L->head->link;
  } else {
    p = q->link;
    q->link = p->link;
  }
  free(p);
  L->n--;
  return OK;
}

Status Output(HeaderList *L) {
  Node *p;
  if (!L->n) return ERROR;
  p = L->head;
  while (p) {
    printf("%d", p->element);
    p = p->link;
  }
  return OK;
}

void Destroy(HeaderList *L) {
  Node *p;
  while (L->head) {
    p = L->head->link;
    free(L->head);
    L->head = p;
  }
}

// reverse==逆置
Status Reverse(HeaderList *L) {
  Node *pre, *cur, *next;

  if (!L->n || L->n == 1) return OK;

  pre = NULL;
  cur = L->head;

  while (cur) {
    next = cur->link;  // 1. 保存下一个节点
    cur->link = pre;   // 2. 反向连接：当前节点指向前一个
    pre = cur;         // 3. pre向前移动
    cur = next;        // 4. cur继续遍历
  }

  L->head = pre;  // 5. 更新表头
  return OK;
}

Status Sort(HeaderList *L) {
  Node *sorted, *current, *next_node, *pos, *prev_pos;

  if (!L->n || L->n == 1) return OK;

  sorted = NULL;  // 有序链表初始为空
  current = L->head;

  while (current) {
    next_node = current->link;  // 保存下一个节点
    current->link = NULL;       // 断开当前节点

    // 在有序链表中找合适的插入位置
    if (!sorted || sorted->element >= current->element) {
      // 插入到表头
      current->link = sorted;
      sorted = current;
    } else {
      // 找到合适的插入位置
      pos = sorted;
      while (pos->link && pos->link->element < current->element) {
        pos = pos->link;
      }
      // 在pos之后插入current
      current->link = pos->link;
      pos->link = current;
    }

    current = next_node;  // 继续遍历原链表
  }

  L->head = sorted;  // 更新表头指向有序链表
  return OK;
}