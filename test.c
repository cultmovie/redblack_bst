#include <stdio.h>
#include <inttypes.h>
#include "redblack_bst.h"

int main() {
    RedBlackBST *tree = redblack_new();
    for(int i = 0;i < 10;i++) {
        redblack_insert(tree, i, i+1);
    }
    for(int i = 0;i < 10;i++) {
        bool is_exist;
        Value value = redblack_get(tree, i, &is_exist);
        if(is_exist)
            printf("key:%"PRId64",value%"PRId64"\n", (Key)i, value);
    }
    return 0;
}
