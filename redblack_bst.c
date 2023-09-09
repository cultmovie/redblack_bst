#include <stdlib.h>
#include "redblack_bst.h"

typedef enum {RED, BLACK} Color;

struct redblack_node {
    Key key;
    Value value;
    struct redblack_node *left, *right;
    int sub_node_num;
    Color color;
};

typedef struct redblack_node RedBlackNode;

struct redblack_bst {
    RedBlackNode *root;
};

static bool is_red(RedBlackNode *node);
static bool is_black(RedBlackNode *node);
static int get_sub_node_num(RedBlackNode *node);
static RedBlackNode *rotate_left(RedBlackNode *node);
static RedBlackNode *rotate_right(RedBlackNode *node);
static void flip_colors(RedBlackNode *node);
static RedBlackNode *new_node(Key key, Value value, Color color);
static RedBlackNode *insert(RedBlackNode *node, Key key, Value value);
static int cmp_key(Key key1, Key key2);
static Value get(RedBlackNode *node, Key key, bool *is_exist);

RedBlackBST *
redblack_new() {
    RedBlackBST *tree = malloc(sizeof(*tree));
    tree->root = NULL;
    return tree;
}

void
redblack_insert(RedBlackBST *tree, Key key, Value value) {
    tree->root = insert(tree->root, key, value);
    tree->root->color = BLACK;
}

Value
redblack_get(RedBlackBST *tree, Key key, bool *is_exist) {
    return get(tree->root, key, is_exist);
}

static Value
get(RedBlackNode *node, Key key, bool *is_exist) {
    if(node == NULL) {
        *is_exist = false;
        return 0;
    }
    switch(cmp_key(key, node->key)) {
    case 0:
        *is_exist = true;
        return node->value;
    case 1:
        return get(node->right, key, is_exist);
    case -1:
        return get(node->left, key, is_exist);
    }
}

static RedBlackNode *
new_node(Key key, Value value, Color color) {
    RedBlackNode *node = malloc(sizeof(*node));
    node->key = key;
    node->value = value;
    node->color = color;
    node->left = NULL;
    node->right = NULL;
    node->sub_node_num = 1;
    return node;
}

static int
cmp_key(Key key1, Key key2) {
    if(key1 == key2)
        return 0;
    else if(key1 > key2)
        return 1;
    else if(key1 < key2)
        return -1;
}

static RedBlackNode *
insert(RedBlackNode *node, Key key, Value value) {
    if(node == NULL) 
        return new_node(key, value, RED);
    switch(cmp_key(key, node->key)) {
    case 0:
        node->value = value;
        break;
    case 1:
        node->right = insert(node->right, key, value);
        break;
    case -1:
        node->left = insert(node->left, key, value);
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
