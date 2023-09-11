#ifndef REDBLACK_BST_H
#define REDBLACK_BST_H
#include <stdint.h>
#include <stdbool.h>

typedef struct redblack_bst RedBlackBST;

typedef int (*CmpFunc)(void *data1, void *data2);
typedef void (*UpdateFunc)(void *data1, void *data2);
typedef void (*FreeFunc)(void *data);
typedef uint64_t (*GetScoreFunc)(void *data);

RedBlackBST *redblack_new(CmpFunc cmp_func, UpdateFunc update_func, FreeFunc free_func, GetScoreFunc get_score_func);
void redblack_free(RedBlackBST *tree);
void redblack_insert(RedBlackBST *tree, void *data);
void *redblack_get(RedBlackBST *tree, void *data);
void *redblack_get_min(RedBlackBST *tree);
void *redblack_get_max(RedBlackBST *tree);
void redblack_draw(RedBlackBST *tree);
void redblack_traverse(RedBlackBST *tree);

#endif
