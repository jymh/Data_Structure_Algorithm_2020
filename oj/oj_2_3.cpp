#include <bits/stdc++.h>
using namespace std;

struct node {
    int color;//0 white; 1 black;
    int parent;
    int rank;
    int blklen;
};
typedef struct node node_t;

int Find(node_t *nodes, int x) {
    while(nodes[x].parent != x) {
        x = nodes[x].parent;
    }
    return x;
}

int Union(node_t *nodes, int x, int y) {//return the blklen after union
    assert(nodes[x].color == 1 && nodes[y].color == 1);

    int x_led = Find(nodes, x);
    int y_led = Find(nodes, y);
    if(x_led == y_led) return nodes[x_led].blklen;
    else if(nodes[x_led].rank > nodes[y_led].rank) {
        nodes[y_led].parent = x_led;
        nodes[x_led].blklen += nodes[y_led].blklen;
        return nodes[x_led].blklen;
    } 
    else if(nodes[x_led].rank < nodes[y_led].rank) {
        nodes[x_led].parent = y_led;
        nodes[y_led].blklen += nodes[x_led].blklen;
        return nodes[y_led].blklen;
    }
    else {//randomly
        nodes[x_led].parent = y_led;
        nodes[y_led].blklen += nodes[x_led].blklen;
        nodes[y_led].rank ++;
        return nodes[y_led].blklen;
    }
}

int main() {
    int n, p;
    int first_maxlen = 1, second_maxlen = 1;
    scanf("%d", &n);
    node_t *nodes = (node_t*)malloc(sizeof(node_t)*n);
    int *inputs = (int*)malloc(sizeof(int)*n);
    int *blk_maxlens = (int*)malloc(sizeof(int)*n);
    int *wht_maxlens = (int*)malloc(sizeof(int)*n);

    //initialize
    for(int i = 0; i < n; i++) {
        blk_maxlens[i] = 0;
        wht_maxlens[i] = 0;

        nodes[i].color = 0;//white
        nodes[i].parent = i;
        nodes[i].rank = 1;
        nodes[i].blklen = 0;
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &inputs[i]);
        inputs[i] --;//begin with 0
        p = inputs[i];
        nodes[p].color = 1;//black
        nodes[p].blklen = 1;
        blk_maxlens[i] = first_maxlen;

        if(p == 0) {
            if(nodes[1].color == 1) {
                int len = Union(nodes, 0, 1);
                first_maxlen = first_maxlen > len ? first_maxlen : len;
                blk_maxlens[i] = first_maxlen;
            }
        }
        else if(p == n-1) {
            if(nodes[n-2].color == 1) {
                int len = Union(nodes, n-1, n-2);
                first_maxlen = first_maxlen > len ? first_maxlen : len;
                blk_maxlens[i] = first_maxlen;
            }
        }
        else {
            if(nodes[p-1].color == 1 && nodes[p+1].color == 1) {
                Union(nodes, p-1, p);
                int len = Union(nodes, p, p+1);
                first_maxlen = first_maxlen > len ? first_maxlen : len;
                blk_maxlens[i] = first_maxlen;
            }
            else if(nodes[p-1].color == 1) {
                int len = Union(nodes, p-1, p);
                first_maxlen = first_maxlen > len ? first_maxlen : len;
                blk_maxlens[i] = first_maxlen;
            }
            else if(nodes[p+1].color == 1) {
                int len = Union(nodes, p, p+1);
                first_maxlen = first_maxlen > len ? first_maxlen : len;
                blk_maxlens[i] = first_maxlen;
            }
        }
    }
    //after that, all nodes are black(1)

    for(int i = 0; i < n; i++) {
        nodes[i].color = 0;//white
        nodes[i].parent = i;
        nodes[i].rank = 1;
        nodes[i].blklen = 0;
    }
    for(int i = n-1; i >= 0; i--) {
        p = inputs[i];
        nodes[p].color = 1;
        nodes[p].blklen = 1;
        wht_maxlens[i] = second_maxlen;

        if(p == 0) {
            if(nodes[1].color == 1) {
                int len = Union(nodes, 0, 1);
                second_maxlen = second_maxlen > len ? second_maxlen : len;
                wht_maxlens[i] = second_maxlen;
            }
        }
        else if(p == n-1) {
            if(nodes[n-2].color == 1) {
                int len = Union(nodes, n-1, n-2);
                second_maxlen = second_maxlen > len ? second_maxlen : len;
                wht_maxlens[i] = second_maxlen;
            }
        }
        else {
            if(nodes[p-1].color == 1 && nodes[p+1].color == 1) {
                Union(nodes, p-1, p);
                int len = Union(nodes, p, p+1);
                second_maxlen = second_maxlen > len ? second_maxlen : len;
                wht_maxlens[i] = second_maxlen;
            }
            else if(nodes[p-1].color == 1) {
                int len = Union(nodes, p-1, p);
                second_maxlen = second_maxlen > len ? second_maxlen : len;
                wht_maxlens[i] = second_maxlen;
            }
            else if(nodes[p+1].color == 1) {
                int len = Union(nodes, p, p+1);
                second_maxlen = second_maxlen > len ? second_maxlen : len;
                wht_maxlens[i] = second_maxlen;
            }
        }
    }

    for(int i = 0; i < n - 1; i++) {
        int max = blk_maxlens[i] > wht_maxlens[i + 1] ? blk_maxlens[i] : wht_maxlens[i + 1];
        //printf("blk: %d, wht: %d\n", blk_maxlens[i], wht_maxlens[i]);
        printf("%d ", max);
    }
    printf("%d", blk_maxlens[n-1]);
    return 0;
}