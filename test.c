#include <stdio.h>
#include <inttypes.h>
#include <assert.h>
#include <stdlib.h>
#include "redblack_bst.h"
//#include "redblack_draw.h"

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

static uint64_t
get_score_func(void *data) {
    return ((Score *)data)->score;
}

int main() {
    RedBlackBST *tree = redblack_new(cmp_func, update_func, free_func, get_score_func);
    for(int i = 0;i < 10;i++) {
        Score *score = malloc(sizeof(*score));
        score->roleid = i;
        score->score = i+10;
        redblack_insert(tree, score);
    }
    redblack_draw(tree);
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
