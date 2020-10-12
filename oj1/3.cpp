#include <bits/stdc++.h>
using namespace std;

typedef struct line {
    deque<char> l;
} l_t;
static l_t text[100];

void operate(int st, int side, int choice, char c) {
    //printf("st is %d, side is %d, choice is %d\n", st, side, choice);
    switch(choice){
        case 0:
            if(side == 0) {//leftmost
                text[st].l.push_front(c);
            }
            else {//rightmost
                text[st].l.push_back(c);
            }
            break;
        case 1:
            if(text[st].l.empty()) printf("#\n");
            else {
                if(side == 0) {
                    printf("%c\n", text[st].l.front());
                    text[st].l.pop_front();
                }
                else {
                    printf("%c\n", text[st].l.back());
                    text[st].l.pop_back();
                }
            }
            break;
        case 2:
            if(text[st].l.empty()) printf("#\n");
            else {
                if(side == 0) {
                    printf("%c\n", text[st].l.front());
                }
                else {
                    printf("%c\n", text[st].l.back());
                }
            }
            break;
    }
}

int main() {
    int Q;
    scanf("%d", &Q);

    char op[4][4];

    for(int i = 0; i < Q; i++) {
        for(int j = 0; j < 4; j++) {
            scanf("%s", &op[j]);
            if(j == 2) {
                if(atoi(op[j]) != 0) break;
            }   
        }
        operate(atoi(op[0]), atoi(op[1]), atoi(op[2]), op[3][0]);
    }     
    return 0;
}