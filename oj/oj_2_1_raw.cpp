#include <bits/stdc++.h>
using namespace std;

#define DEBUG

static map<int, int> info;

void Insert(int x) {
    if(info.count(x) == 0) {
        info[x] = 1;
    }
    else {
        assert(info[x] >= 1);
        info[x] ++;
    }
}

void Delete(int x) {
    if(info[x] == 1) {
        info.erase(x);
    }
    else {
        info[x] --;
    }
}


int main() {
    FILE *f = fopen("res_correct.txt", "w");

    int Q = 0, mod = 0;
    int ops[3];
    int lans = 0;
    scanf("%d %d", &Q, &mod);
    for(int i = 0; i < Q; i++) {
        for(int j = 0; j < 3; j++) {
            if(j==2) {
                if(ops[0] != 2) break;
            }
            scanf("%d", &ops[j]);
        }
        switch(ops[0]) {
            int x;
            case 0:
                x = (ops[1] + lans) % mod;
                Insert(x);
                break;
            case 1:
                x = (ops[1] + lans) % mod;
                if(info.count(x) == 0) {
                    #ifdef DEBUG
                        fprintf(f, "%d\n", 0);
                    #else    
                        printf("0\n");
                    #endif
                }
                else {
                    #ifdef DEBUG
                        fprintf(f, "%d\n", info[x]);
                    #else    
                        printf("%d\n", info[x]);
                    #endif
                    Delete(x);
                }
                break;
            case 2:
                int l = (ops[1] + lans) % mod;
                int r = (ops[2] + lans) % mod;
                if(l > r) {
                    int temp = l;
                    l = r;
                    r = temp;
                }

                int output = 0;
                for(map<int, int>::iterator it = info.begin(); it != info.end(); it++) {
                    if(it->first > l && it->first <= r) {
                        output += it->first * it->second;
                    }
                }
                #ifdef DEBUG
                    fprintf(f, "%d\n", output);
                #else    
                    printf("%d\n", output);
                #endif
                lans = output;
                break;
        }
    }
    fclose(f);
    return 0;
}