#include <bits/stdc++.h>
using namespace std;

typedef enum color {WHITE=0, BLACK} color_t;

typedef struct node {
    int left, right;
    int total_len;
    int max_len;
    color_t left_clr;
    int left_len;
    color_t right_clr;
    int right_len;
} node_t;

void Build(int *indexs, node_t *nodes, int i, int l, int r) {
    nodes[i].left = l;
    nodes[i].right = r;
    nodes[i].total_len = r - l + 1;
    nodes[i].max_len = r - l + 1;
    nodes[i].left_clr = WHITE;
    nodes[i].left_len = r - l + 1;
    nodes[i].right_clr = WHITE;
    nodes[i].right_len = r - l + 1;
    if(nodes[i].left == nodes[i].right) {
        indexs[nodes[i].left] = i;
        return ;
    }
    Build(indexs, nodes, i*2 + 1, l, (l+r)/2);
    Build(indexs, nodes, i*2 + 2, (l+r)/2 + 1, r);
}

void Blacken(int *indexs, node_t *nodes, int p) {
    //forward
    int i = indexs[p];
    nodes[i].left_clr = BLACK;
    nodes[i].right_clr = BLACK;

    //back
    while(1) {
        int par = (i - 1) / 2;
        //printf("in while par is %d\n", par);
        int bro;
        if(i == par * 2 + 1) {//i is left
            bro = i + 1;
            nodes[par].left_clr = nodes[i].left_clr;
            nodes[par].right_clr = nodes[bro].right_clr;
            if(nodes[i].left_len == nodes[i].total_len && nodes[i].right_clr == nodes[bro].left_clr) {
                nodes[par].left_len = nodes[i].left_len + nodes[bro].left_len;
            }
            else {
                nodes[par].left_len = nodes[i].left_len;
            }

            if(nodes[bro].right_len == nodes[bro].total_len && nodes[bro].left_clr == nodes[i].right_clr) {
                nodes[par].right_len = nodes[bro].right_len + nodes[i].right_len;
            }
            else {
                nodes[par].right_len = nodes[bro].right_len;
            }

            int cross_len = (nodes[i].right_clr == nodes[bro].left_clr) ? nodes[i].right_len + nodes[bro].left_len : 0;
            nodes[par].max_len = (nodes[i].max_len > nodes[bro].max_len) ? nodes[i].max_len : nodes[bro].max_len;
            nodes[par].max_len = (nodes[par].max_len > cross_len) ? nodes[par].max_len : cross_len;
        }
        else {//i is right
            bro = i - 1;
            nodes[par].left_clr = nodes[bro].left_clr;
            nodes[par].right_clr = nodes[i].right_clr;
            if(nodes[i].right_len == nodes[i].total_len && nodes[i].left_clr == nodes[bro].right_clr) {
                nodes[par].right_len = nodes[i].right_len + nodes[bro].right_len;
            }
            else {
                nodes[par].right_len = nodes[i].right_len;
            }

            if(nodes[bro].left_len == nodes[bro].total_len && nodes[bro].right_clr == nodes[i].left_clr) {
                nodes[par].left_len = nodes[bro].left_len + nodes[i].left_len;
            }
            else {
                nodes[par].left_len = nodes[bro].left_len;
            }

            int cross_len = (nodes[i].left_clr == nodes[bro].right_clr) ? nodes[i].left_len + nodes[bro].right_len : 0;
            nodes[par].max_len = (nodes[i].max_len > nodes[bro].max_len) ? nodes[i].max_len : nodes[bro].max_len;
            nodes[par].max_len = (nodes[par].max_len > cross_len) ? nodes[par].max_len : cross_len;
        }

        i = par;
        if(i == 0) break;
    }
}

int main() {
    FILE *f = fopen("res_correct.txt", "w");

    int n, p;
    scanf("%d", &n);
    node_t *nodes = (node_t*)malloc(sizeof(node_t)*4*n);
    int *indexs = (int*)malloc(sizeof(int)*n);
    Build(indexs, nodes, 0, 0, n - 1);
    for(int i = 0; i < n; i++) {
        scanf("%d", &p);
        p --;
        Blacken(indexs, nodes, p);
        //printf("%d ", nodes[0].max_len);
        fprintf(f, "%d ", nodes[0].max_len);
    }
    return 0;
}