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

void Build(node_t *nodes, int i, int l, int r) {
    nodes[i].left = l;
    nodes[i].right = r;
    nodes[i].total_len = l - r + 1;
    nodes[i].max_len = l - r + 1;
    nodes[i].left_clr = WHITE;
    nodes[i].left_len = l - r + 1;
    nodes[i].right_clr = WHITE;
    nodes[i].right_len = l - r + 1;
    if(nodes[i].left == nodes[i].right) {
        return ;
    }
    Build(nodes, i*2 + 1, l, (l+r)/2);
    Build(nodes, i*2 + 2, (l+r)/2 + 1, r);
}

void Blacken(node_t *nodes, int p) {
    //forward
    int i = 0;
    while(1) {
        if(nodes[i].left == nodes[i].right) {
            assert(nodes[i].left == p);
            break;
        }
        
        int mid = (nodes[i].left + nodes[i].right)/2;
        if(p <= mid) {
            i = i * 2 + 1;
        }
        else {
            i = i * 2 + 2;
        }
    }
    nodes[i].left_clr = BLACK;
    nodes[i].right_clr = BLACK;

    //back
    while(1) {
        int par = (i - 1) / 2;
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
        else {
            bro = i - 1;
            
        }

        if(i == 0) return ;
    }
}

int main() {
    int n, p;
    scanf("%d", &n);
    node_t *nodes = (node_t*)malloc(sizeof(node_t)*4*n);
    Build(nodes, 0, 0, n - 1);
    return 0;
}