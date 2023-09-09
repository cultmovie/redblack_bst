#ifndef REDBLACK_BST_H
#define REDBLACK_BST_H
#include <stdint.h>
#include <stdbool.h>

typedef struct redblack_bst RedBlackBST;
typedef int64_t Key;
typedef int64_t Value;

RedBlackBST *redblack_new();
void redblack_insert(RedBlackBST *tree, Key key, Value value);
Value redblack_get(RedBlackBST *tree, Key key, bool *is_exist);

#endif
