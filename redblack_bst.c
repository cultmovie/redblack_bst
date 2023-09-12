#include <stdlib.h>
#include <assert.h>
#include "redblack_bst.h"

typedef enum {RED, BLACK} Color;

struct redblack_node {
    void *data;
    struct redblack_node *left, *right;
    size_t sub_node_num;
    Color color;
};

struct redblack_bst {
    RedBlackNode *root;
    size_t node_num;
    CmpFunc cmp_func;
    UpdateFunc update_func;
    FreeFunc free_func;
    GetDrawStrFunc get_draw_str_func;
};

static bool is_red(RedBlackNode *node);
static bool is_black(RedBlackNode *node);
static int get_sub_node_num(RedBlackNode *node);
static RedBlackNode *rotate_left(RedBlackNode *node);
static RedBlackNode *rotate_right(RedBlackNode *node);
static void flip_colors(RedBlackNode *node);
static RedBlackNode *new_node(void *data, Color color);
static RedBlackNode *insert(RedBlackBST *tree, RedBlackNode *node, void *data);
static void *get(RedBlackBST *tree, RedBlackNode *node, void *data);
static RedBlackNode *get_min(RedBlackNode *node);
static RedBlackNode *get_max(RedBlackNode *node);
static RedBlackNode *free_node(RedBlackBST *tree, RedBlackNode *node);
static void traverse_tree(RedBlackBST *tree, RedBlackNode *node);

RedBlackBST *
redblack_new(CmpFunc cmp_func, UpdateFunc update_func,
        FreeFunc free_func, GetDrawStrFunc get_draw_str_func) {
    RedBlackBST *tree = malloc(sizeof(*tree));
    tree->root = NULL;
    tree->cmp_func = cmp_func;
    tree->update_func = update_func;
    tree->free_func = free_func;
    tree->get_draw_str_func = get_draw_str_func;
    return tree;
}

void
redblack_free(RedBlackBST *tree) {
    tree->root = free_node(tree, tree->root);
    free(tree);
}

void
redblack_insert(RedBlackBST *tree, void *data) {
    tree->root = insert(tree, tree->root, data);
    tree->root->color = BLACK;
}

void *
redblack_get(RedBlackBST *tree, void *data) {
    return get(tree, tree->root, data);
}

void *
redblack_get_min(RedBlackBST *tree) {
    assert(tree->root);
    return get_min(tree->root)->data;
}

void *
redblack_get_max(RedBlackBST *tree) {
    assert(tree->root);
    return get_max(tree->root)->data;
}

void
redblack_traverse(RedBlackBST *tree) {
    traverse_tree(tree, tree->root);
}

bool
redblack_is_empty(RedBlackBST *tree) {
    tree->root == NULL ? true : false;
}

RedBlackNode *
redblack_get_root(RedBlackBST *tree) {
    return tree->root;
}

RedBlackNode *
redblack_get_left(RedBlackNode *node) {
    return node->left;
}

RedBlackNode *
redblack_get_right(RedBlackNode *node) {
    return node->right;
}

void *
redblack_get_data(RedBlackNode *node) {
    return node->data;
}

const char *
redblack_get_draw_str(RedBlackBST *tree, RedBlackNode *node) {
    return tree->get_draw_str_func(node);
}

size_t
redblack_get_sub_node_num(RedBlackNode *node) {
    return node->sub_node_num;
}

bool
redblack_is_red(RedBlackNode *node) {
    return is_red(node);
}

static void
traverse_tree(RedBlackBST *tree, RedBlackNode *node) {
    if(node == NULL)
        return;
    const char *draw_str = tree->get_draw_str_func(node);
    printf("%s", draw_str);
    free((char *)draw_str);
    traverse_tree(tree, node->left);
    traverse_tree(tree, node->right);
}

static RedBlackNode *
free_node(RedBlackBST *tree, RedBlackNode *node) {
    if(node == NULL)
        return NULL;
    node->left = free_node(tree, node->left);
    node->right = free_node(tree, node->right);
    tree->free_func(node->data);
    free(node);
    return NULL;
}

static RedBlackNode *
get_max(RedBlackNode *node) {
    if(node->right == NULL)
        return node;
    return get_max(node->right);
}

static RedBlackNode *
get_min(RedBlackNode *node) {
    if(node->left == NULL)
        return node;
    return get_min(node->left);
}

static void *
get(RedBlackBST *tree, RedBlackNode *node, void *data) {
    if(node == NULL)
        return NULL;
    int result = tree->cmp_func(data, node->data);
    if(result == 0)
        return node->data;
    else if(result > 0)
        return get(tree, node->right, data);
    else
        return get(tree, node->left, data);
}

static RedBlackNode *
new_node(void *data, Color color) {
    RedBlackNode *node = malloc(sizeof(*node));
    node->data = data;
    node->color = color;
    node->left = NULL;
    node->right = NULL;
    node->sub_node_num = 1;
    return node;
}

static RedBlackNode *
insert(RedBlackBST *tree, RedBlackNode *node, void *data) {
    if(node == NULL) 
        return new_node(data, RED);
    switch(tree->cmp_func(data, node->data)) {
    case 0:
        tree->update_func(node->data, data);
        break;
    case 1:
        node->right = insert(tree, node->right, data);
        break;
    case -1:
        node->left = insert(tree, node->left, data);
        break;
    }
    if(is_red(node->right) && is_black(node->left))
        node = rotate_left(node);
    if(is_red(node->left) && is_red(node->left->left))
        node = rotate_right(node);
    if(is_red(node->left) && is_red(node->right))
        flip_colors(node);
    node->sub_node_num = get_sub_node_num(node->left) + get_sub_node_num(node->right) + 1;
    return node;
}

static bool
is_red(RedBlackNode *node) {
    if(node == NULL)
        return false;
    return node->color == RED ? true : false;
}

static bool
is_black(RedBlackNode *node) {
    if(node == NULL)
        return true;
    return node->color == BLACK ? true : false;
}

static int
get_sub_node_num(RedBlackNode *node) {
    if(node == NULL)
        return 0;
    return node->sub_node_num;
}

static RedBlackNode *
rotate_left(RedBlackNode *node) {
    RedBlackNode *sub_tree_root = node->right;
    node->right = sub_tree_root->left;
    sub_tree_root->left = node;
    sub_tree_root->color = node->color;
    node->color = RED;
    sub_tree_root->sub_node_num = node->sub_node_num;
    node->sub_node_num = get_sub_node_num(node->left) + get_sub_node_num(node->right) + 1;
    return sub_tree_root;
}

static RedBlackNode *
rotate_right(RedBlackNode *node) {
    RedBlackNode *sub_tree_root = node->left;
    node->left = sub_tree_root->right;
    sub_tree_root->right = node;
    sub_tree_root->color = node->color;
    node->color = RED;
    sub_tree_root->sub_node_num = node->sub_node_num;
    node->sub_node_num = get_sub_node_num(node->left) + get_sub_node_num(node->right) + 1;
    return sub_tree_root;
}

static void
flip_colors(RedBlackNode *node) {
    node->color = RED;
    node->left->color = BLACK;
    node->right->color = BLACK;
}
