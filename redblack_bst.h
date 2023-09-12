#ifndef REDBLACK_BST_H
#define REDBLACK_BST_H
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct redblack_bst RedBlackBST;
typedef struct redblack_node RedBlackNode;

typedef int (*CmpFunc)(void *data1, void *data2);
typedef void (*UpdateFunc)(void *data1, void *data2);
typedef void (*FreeFunc)(void *data);
typedef const char *(*GetDrawStrFunc)(RedBlackNode *node);

RedBlackBST *redblack_new(CmpFunc cmp_func, UpdateFunc update_func, FreeFunc free_func, GetDrawStrFunc get_draw_str_func);
void redblack_free(RedBlackBST *tree);
void redblack_insert(RedBlackBST *tree, void *data);
void *redblack_get(RedBlackBST *tree, void *data);
void *redblack_get_min(RedBlackBST *tree);
void *redblack_get_max(RedBlackBST *tree);
void redblack_traverse(RedBlackBST *tree);
RedBlackNode *redblack_get_root(RedBlackBST *tree);
RedBlackNode *redblack_get_left(RedBlackNode *node);
RedBlackNode *redblack_get_right(RedBlackNode *node);
void *redblack_get_data(RedBlackNode *node);
const char *redblack_get_draw_str(RedBlackBST *tree, RedBlackNode *node);
size_t redblack_get_sub_node_num(RedBlackNode *node);
bool redblack_is_red(RedBlackNode *node);
bool redblack_is_empty(RedBlackBST *tree);

#endif
