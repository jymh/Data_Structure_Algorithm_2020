#include <bits/stdc++.h>
using namespace std;

//#define DEBUG 

struct node {
    long long val;
    long long cnt;//maybe many nodes of same value
    long long subSum;//sum of the subtree rooted at it
    long long priority;
    struct node *left;
    struct node *right;
    struct node *parent;
};
typedef struct node node_t;

static node_t *root = (node_t*)malloc(sizeof(node_t));

void Init() {
    root->val = 0;
    root->cnt = 0;
    root->subSum = 0;
    root->priority = 0;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
}

void InitNode(node_t *node, long long val, long long cnt, long long subSum, long long priority, node_t *left, node_t *right, node_t *parent) {
    node->val = val;
    node->cnt = cnt;
    node->subSum = subSum;
    node->priority = priority;
    node->left = left;
    node->right = right;
    node->parent = parent;
}

node_t* Search(long long value) {
    node_t *x = root;
    if(x->cnt == 0) return NULL;
    else {
        while(x != NULL && x->val != value) {
            if(x->val > value) x = x->left;
            else x = x->right;
        }
        return x;
    }
}

void LeftRotate(node_t *x) {//x->right, x->parent changed
    node_t *y = x->right;
    assert(y != NULL);

    //update sum
    x->subSum -= y->subSum;
    x->subSum += (y->left == NULL) ? 0 : y->left->subSum;
    y->subSum -= (y->left == NULL) ? 0 : y->left->subSum;
    y->subSum += x->subSum;

    //begin rotate
    x->right = y->left;
    if(y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL) {
        assert(x == root);
        root = y;
    }
    else if(x == x->parent->left) {
        x->parent->left = y;
    }
    else if(x == x->parent->right) {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RightRotate(node_t *x) {//x->left,x->parent changed
    node_t *y = x->left;
    assert(y != NULL);

    //update sum
    x->subSum -= y->subSum;
    x->subSum += (y->right == NULL) ? 0 : y->right->subSum;
    y->subSum -= (y->right == NULL) ? 0 : y->right->subSum;
    y->subSum += x->subSum;

    //begin rotate
    x->left = y->right;
    if(y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL) {
        assert(x == root);
        root = y;
    }
    else if(x == x->parent->left) {
        x->parent->left = y;
    }
    else if(x == x->parent->right) {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
}

void Insert(long long value, long long priority) {
    if(root->cnt == 0) {//root is empty
        InitNode(root, value, 1, value, priority, NULL, NULL, NULL);
    }
    else {//root->cnt != 0
        node_t *x = root, *y = NULL;
        while(x != NULL) {
            y = x;
            if(x->val > value) {
                x->subSum += value;
                x = x->left;    
            }
            else if(x->val == value) {//don't update priority here
                x->subSum += value;
                x->cnt ++;
                break;
            }
            else {
                x->subSum += value;
                x = x->right;
            }
        }
        
        if(x == NULL) {
            node_t *z = (node_t*)malloc(sizeof(node_t));
            InitNode(z, value, 1, value, priority, NULL, NULL, y);
            if(value < y->val) y->left = z;
            else y->right = z;
            
            while(z->priority < z->parent->priority) {
                if(z == z->parent->left) {
                    RightRotate(z->parent);
                }
                else if(z == z->parent->right) {
                    LeftRotate(z->parent);
                }

                if(z->parent == NULL) {
                    assert(z == root);
                    break;
                }
            }
        }
    }
}

/*
void Transplant(node_t *u, node_t *v) {//no update v.left and v.right
    if(u == root && v == NULL) {
        InitNode(u, 0, 0, 0, 0, NULL, NULL, NULL);
        return;
    }

    if(u == root) {
        root = v;
    }
    else if(u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    if(v != NULL) v->parent = u->parent;
}
*/

/*
node_t* Minimum(node_t *z) {
    node_t *temp = z;
    while(temp->left != NULL) temp = temp->left;
    return temp;
}  
*/ 

void ModPathSum(node_t *start, node_t *end, long long dec) {
    node_t *p = start;
    while(p != end->parent) {
        p->subSum -= dec;
        p = p->parent;
    }
}

void Delete(node_t *z) {
    /*
    ModPathSum(z, root, z->val * z->cnt);//necessary
    if(z->left == NULL) {
        Transplant(z, z->right);
    }
    else if(z->right == NULL) {
        Transplant(z, z->left);
    }
    else {
        node_t *y = Minimum(z->right);
        ModPathSum(y->parent, z->right, y->val * y->cnt);
        if(y->parent != z) {//necessary to consider if y->parent==z
            Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        Transplant(z, y);
        y->subSum = z->subSum;
        y->left = z->left;
        y->left->parent = y;
    }
    */
    while(!(z->left == NULL && z->right == NULL)) {
        if(z->left == NULL) {
            LeftRotate(z);
        }
        else if(z->right == NULL) {
            RightRotate(z);
        }
        else {
            if(z->right->priority < z->left->priority) {
                LeftRotate(z);
            }
            else {
                RightRotate(z);
            }
        }
    }
    ModPathSum(z, root, z->val * z->cnt);
    if(z->parent == NULL) {//z is root
        InitNode(z, 0, 0, 0, 0, NULL, NULL, NULL);
    }
    else if(z == z->parent->left){
        z->parent->left = NULL;
    }
    else if(z == z->parent->right) {
        z->parent->right = NULL;
    }
}

bool isLeaf(node_t *z) {
    assert(z != NULL);
    if(z->left == NULL && z->right == NULL) {
        return true;
    }
    return false;
}

long long rangeSum(long long lo, long long hi) {
    node_t *split = root;
    while((!isLeaf(split)) && (split->val <= lo || split->val > hi)) {//find split node
        if(split->val <= hi) split = split->right;
        else split = split->left;

        if(split == NULL) return 0;
    }
    if(isLeaf(split)) {
        return (split->val > lo && split->val <= hi) ? (split->val * split->cnt) : 0;
    }

    assert(split->val > lo && split->val <= hi);
    long long sum = 0, lsum = 0, rsum = 0;//easy to debug
    node_t *pl = split->left, *pr = split->right;
    while(pl != NULL) {
        if(pl->val == lo) {
            lsum += (pl->right == NULL) ? 0 : pl->right->subSum;
            break;
        }
        else if(pl->val > lo) {
            lsum += pl->val * pl->cnt;
            lsum += (pl->right == NULL) ? 0 : pl->right->subSum;
            pl = pl->left;
        }
        else {
            pl = pl->right;
        }
    }

    while(pr != NULL) {
        if(pr->val == hi) {
            rsum += pr->val * pr->cnt;
            rsum += (pr->left == NULL) ? 0 : pr->left->subSum;
            break;
        }
        else if(pr->val < hi) {
            rsum += pr->val * pr->cnt;
            rsum += (pr->left == NULL) ? 0 : pr->left->subSum;
            pr = pr->right;
        }
        else {
            pr = pr->left;
        }
    }
    sum = lsum + rsum + split->val * split->cnt;
    return sum;
}

int main() {
    srand((unsigned)time(0));
    #ifdef DEBUG
        FILE *f = fopen("res.txt", "w");
    #endif
    Init();

    long long Q = 0, mod = 0;
    long long ops[3];
    long long lans = 0;
    scanf("%lld %lld", &Q, &mod);
    for(long long i = 0; i < Q; i++) {
        for(long long j = 0; j < 3; j++) {
            if(j==2) {
                if(ops[0] != 2) break;
            }
            scanf("%lld", &ops[j]);
        }
        switch(ops[0]) {
            case 0: {
                long long x = (ops[1] + lans) % mod;
                long long priority = rand();
                //printf("priority is %lld\n", priority);
                Insert(x, priority);
                break;
            }
            case 1: {
                long long x = (ops[1] + lans) % mod;
                node_t *n = Search(x);
                if(n == NULL) {
                    #ifdef DEBUG
                        fprintf(f, "%lld\n", 0);
                    #else    
                        printf("0\n");
                    #endif    
                }
                else if(n->cnt > 1) {
                    #ifdef DEBUG
                        fprintf(f, "%lld\n", n->cnt);
                    #else    
                        printf("%lld\n", n->cnt);
                    #endif
                    ModPathSum(n, root, n->val);
                    n->cnt --;
                }
                else {
                    assert(n->cnt == 1);
                    #ifdef DEBUG
                        fprintf(f, "%lld\n", n->cnt);
                    #else    
                        printf("%lld\n", n->cnt);
                    #endif
                    Delete(n);
                }
                break;
            }
            case 2: {
                long long l = (ops[1] + lans) % mod;
                long long r = (ops[2] + lans) % mod;
                if(l > r) {
                    long long temp = l;
                    l = r;
                    r = temp;
                }

                long long output = rangeSum(l, r);
                #ifdef DEBUG
                    fprintf(f, "%lld\n", output);
                #else    
                    printf("%lld\n", output);
                #endif
                lans = output;
                break;
            }
        }
    }
    #ifdef DEBUG
        fclose(f);
    #endif
    return 0;
}