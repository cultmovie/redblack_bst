#include <graphviz/gvc.h>
#include "redblack_bst.h"

void
redblack_draw(RedBlackBST *tree) {
    GVC_t *gvc = gvContext();
    Agraph_t *g = agopen("g", Agdirected, 0);
    Agnode_t *n = agnode(g, "n", 1);
    Agnode_t *m = agnode(g, "m", 1);
    agedge(g, n, m, 0, 1);
    gvLayout(gvc, g, "dot");
    gvRender(gvc, g, "dot", stdout);
    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
}
