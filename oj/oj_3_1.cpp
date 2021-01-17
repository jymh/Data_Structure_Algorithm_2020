#include <bits/stdc++.h>
using namespace std;

//#define DEBUG

typedef struct c_and_index {
    double c;
    int index;
} cindex_t;

int InplacePartition(cindex_t *arr, int lo, int hi) {//[lo,hi)
    cindex_t temp;
    int x_index = rand()%(hi-lo) + lo;
    temp = arr[hi-1];
    arr[hi-1] = arr[x_index];
    arr[x_index] = temp;

    cindex_t x = arr[hi-1];
    int i = lo - 1;
    for(int j = lo; j < hi-1; j++) {
        if(arr[j].c > x.c) {//max
            i ++;
            temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    }
    arr[hi-1] = arr[i+1];
    arr[i+1] = x;
    return i+1;
}

void FirstK(cindex_t *arr, int lo, int hi, int k) {//modify arr s.t. the max k items is in the front of arr
    int i = InplacePartition(arr, lo, hi);//arr[lo,...,i] all greater/smaller than arr[i+1,i+2,...hi]
    //printf("lo is %d, hi is %d, i is %d\n", lo, hi, i);
    int len = i - lo + 1;
    if(len == k || hi - lo == 1) return;
    else if(len > k) {
        FirstK(arr, lo, i + 1, k);
    } 
    else {
        FirstK(arr, i + 1, hi, k-len);
    }
}

double divide(int first, int second) {
    if(second == 0) {
        return 0;
    }
    else {
        return (double)first / (double)second;
    }
}

int main() {
    srand((unsigned)time(0));
    
    #ifdef DEBUG
    FILE *vfile = fopen("values.txt", "r");
    FILE *pfile = fopen("prices.txt", "r");
    #endif

    int n, k;
    scanf("%d %d", &n, &k);
    int *values = (int*)malloc(sizeof(int)*n);
    int *prices = (int*)malloc(sizeof(int)*n);
    cindex_t *cFunc = (cindex_t*)malloc(sizeof(cindex_t)*n);//C_j(x)=v_ij - x*p_ij
    double max_ratio = 1e6, min_ratio = 0;

    for(int i = 0; i < n; i++) {
        #ifdef DEBUG
        fscanf(vfile, "%d ", &values[i]);
        #else
        scanf("%d", &values[i]);
        #endif
    }
        
    for(int i = 0; i < n; i++) {
        #ifdef DEBUG
        fscanf(pfile, "%d ", &prices[i]);
        #else
        scanf("%d", &prices[i]);
        #endif
    }

    double x = 0, max_average = 0;
    while(fabs(max_ratio - min_ratio) > 1e-9) {
        x = (max_ratio + min_ratio) / 2;
        //printf("x:%.10lf, max_ratio:%.10lf, min_ratio:%.10lf\n", x, max_ratio, min_ratio);
        for(int i = 0; i < n; i++) {
            cFunc[i].c = (double)values[i] - (double)(x*prices[i]);
            cFunc[i].index = i;
        }
        FirstK(cFunc, 0, n, k);

        double max_sum_c = 0;
        int max_val = 0, max_prices = 0;
        for(int i = 0; i < k; i++) {
            max_sum_c += cFunc[i].c;
            max_val += values[cFunc[i].index];
            max_prices += prices[cFunc[i].index];
        }  
        max_average = divide(max_val, max_prices);
        
        //printf("max_sum_c:%.10lf\n", max_sum_c);
        if(max_sum_c < 0 || max_average - x < -1e-9) {
            max_ratio = x;
        }
        else if(max_average - x > 1e-9) {
            min_ratio = x;
        }
        else {
            break;
        }
        //printf("min_ratio:%.10lf, max_ration:%.10lf, x:%.10lf\n", min_ratio, max_ratio, x);
    }
    printf("%.10lf\n", max_average);
    return 0;
}