#include <graphviz/gvc.h>
#include <stdlib.h>
#include "redblack_draw.h"

static Agnode_t *draw_tree(RedBlackBST *tree, RedBlackNode *node, Agraph_t *g, int *i);

void
redblack_draw(RedBlackBST *tree, const char *file_name) {
    GVC_t *gvc = gvContext();
    Agraph_t *g = agopen("redblack_tree", Agundirected, 0);
    int i = 0;
    draw_tree(tree, redblack_get_root(tree), g, &i);
    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "svg", file_name);
    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
}

static Agnode_t *
draw_tree(RedBlackBST *tree, RedBlackNode *node, Agraph_t *g, int *i) {
    if(node == NULL)
        return NULL;
    (*i)++;
    const char *fmt = "node_%d";
    int sz = snprintf(NULL, 0, fmt, *i);
    char buffer[sz + 1];
    snprintf(buffer, sizeof(buffer), fmt, *i);

    Agnode_t *n = agnode(g, buffer, 1);

    const char *str = redblack_get_draw_str(tree, node);
    agsafeset(n, "label", str, "0");
    free((char *)str);

    Agnode_t *left_n = draw_tree(tree, redblack_get_left(node), g, i);
    if(left_n){
        Agedge_t *e = agedge(g, n, left_n, 0, 1);
        agattr(g, AGEDGE, "style", "filled");
        agattr(g, AGEDGE, "color", "black");
        if(redblack_is_red(redblack_get_left(node))) {
            agset(e, "color", "red");
            agset(e, "style", "bold");
        }
        else
            agset(e, "color", "black");
    }

    Agnode_t *right_n = draw_tree(tree, redblack_get_right(node), g, i);
    if(right_n) {
        Agedge_t * e = agedge(g, n, right_n, 0, 1);
        agattr(g, AGEDGE, "style", "filled");
        agattr(g, AGEDGE, "color", "black");
        if(redblack_is_red(redblack_get_right(node))) {
            agset(e, "color", "red");
            agset(e, "style", "bold");
        }
        else
            agset(e, "color", "black");
    }
    return n;
}
