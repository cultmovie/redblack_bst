#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <stdlib.h>
#include "redblack_bst.h"
#include "redblack_draw.h"

typedef struct {
    uint64_t roleid;
    uint64_t score;
} Score;

static int
cmp_func(void *data1, void *data2) {
    Score *score1 = (Score *)data1;
    Score *score2 = (Score *)data2;
    if(score1->roleid == score2->roleid) {
        assert(score1->score == score2->score);
        return 0;
    }
    if(score1->score > score2->score)
        return 1;
    else if(score1->score < score2->score)
        return -1;
    else
        return score1->roleid < score2->roleid ? -1 : 1;
}

static void
update_func(void *data1, void *data2) {
    Score *score1 = (Score *)data1;
    Score *score2 = (Score *)data2;
    assert(score1->roleid == score2->roleid);
    score1->score = score2->score;
}

static void
free_func(void *data) {
    if(data)
        free(data);
}

static const char *
get_draw_str_func(RedBlackNode *node) {
    Score *score = (Score *)redblack_get_data(node);
	const char *draw_fmt = "score:%"PRIu64"\nroleid:%"PRIu64"\nn:%ld\n";
    int sz = snprintf(NULL, 0, draw_fmt, score->score, score->roleid, redblack_get_sub_node_num(node));
    size_t buffer_size = sizeof(char)*(sz + 1);
    char *draw_buffer = malloc(buffer_size);
    snprintf(draw_buffer, buffer_size, draw_fmt, score->score, score->roleid, redblack_get_sub_node_num(node));
    return (const char *)draw_buffer;
}

int main() {
    RedBlackBST *tree = redblack_new(cmp_func, update_func, free_func, get_draw_str_func);
    for(int i = 0;i < 10;i++) {
        Score *score = malloc(sizeof(*score));
        score->roleid = i;
        score->score = i+10;
        redblack_insert(tree, score);

        const char *fmt = "redblack_tree_%d.svg";
        int sz = snprintf(NULL, 0, fmt, i);
        char buffer[sz + 1];
        snprintf(buffer, sizeof(buffer), fmt, i);
        redblack_draw(tree, buffer);
    }
    redblack_delete_min(tree);
    redblack_draw(tree, "redblack_tree_10.svg");
    for(int i = 0;i < 10;i++) {
        Score score = {i, i+10};
        Score *result_score = redblack_get(tree, &score);
        if(result_score)
            printf("roleid:%"PRId64",score%"PRId64"\n", result_score->roleid, result_score->score);
    }
    Score * min_score = redblack_get_min(tree);
    Score * max_score = redblack_get_max(tree);
    printf("min in tree,roleid:%"PRId64",score:%"PRId64"\n", min_score->roleid, min_score->score);
    printf("max in tree,roleid:%"PRId64",score:%"PRId64"\n", max_score->roleid, max_score->score);
    redblack_free(tree);
    return 0;
}
