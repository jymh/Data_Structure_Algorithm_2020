#include <bits/stdc++.h>
#include <limits.h>

uint64_t MergeSpace(int64_t *A, int lo, int mid, int hi, int64_t t) {
	int llen = mid - lo + 1;
	int rlen = hi - mid;
	int64_t *left = (int64_t*)malloc(sizeof(int64_t)*(llen+1));
	int64_t *right = (int64_t*)malloc(sizeof(int64_t)*(rlen+1));
	for(int i = 0; i < llen; i++) {
		left[i] = A[lo + i];
	}
	left[llen] = INT64_MAX;
	for(int i = 0; i < rlen; i++) {
		right[i] = A[mid + 1 + i];
	}
	right[rlen] = INT64_MAX;

	int lindex = 0, rindex = 0;
	uint64_t count = 0;
	//begin count
	while(1) {
		if(rindex < rlen-1 && lindex < llen-1) {
			if(right[rindex] - left[lindex] > t) {
				count += rlen - rindex;
				lindex ++;
			}
			else {
				rindex ++;
			}
		}
		else if(rindex == rlen-1 && lindex < llen-1) {
			if(right[rindex] - left[lindex] > t) {
				count += rlen - rindex;
				lindex ++;
			}
			else {
				break;
			}
		}
		else if(rindex < rlen-1 && lindex == llen-1) {
			if(right[rindex] - left[lindex] > t) {
				count += rlen - rindex;
				break;
			}
			else {
				rindex ++;
			}
		}
		else if(rindex == rlen-1 && lindex == llen-1){
			if(right[rindex] - left[lindex] > t) {
				count += rlen - rindex;
			}
			break;
		};
	}

	//sort
	int i = 0, j = 0;
	for(int k = lo; k <= hi; k++) {
		if(left[i] < right[j]) {
			A[k] = left[i];
			i ++;
		}
		else {
			A[k] = right[j];
			j ++;
		}
	}
	free(left);//it's necessary to do this!
	free(right);
	return count;
}

uint64_t MergeSortSpace(int64_t *A, int lo, int hi, int64_t t) {
	if(lo == hi) {
		return 0;
	}
	int mid = (lo + hi) / 2;
	uint64_t left = MergeSortSpace(A, lo, mid, t);
	uint64_t right = MergeSortSpace(A, mid+1, hi, t);
	uint64_t between = MergeSpace(A, lo, mid, hi, t);
	//printf("left:%d, right:%d, between:%d\n", left, right, between);
	return left + right + between;
}

void CrePrefixArr(int64_t *A, int n) {
	A[0] = 0;
	for(int i = 1; i < n+1; i++) {
		A[i] = A[i] + A[i-1]; 
	}
}

int main() {
	int n;
	int64_t t;
	scanf("%d %lld", &n, &t);
	int64_t *A = (int64_t*)malloc(sizeof(int64_t) * (n+1));
	for(int i = 1; i < n+1; i++) {
		scanf("%lld", &A[i]);
		//A[i] = (int64_t)(-i+1);
	}

	CrePrefixArr(A, n);	

	uint64_t cnt = MergeSortSpace(A, 0, n, t);
	printf("%lu", cnt);	

	return 0;
}