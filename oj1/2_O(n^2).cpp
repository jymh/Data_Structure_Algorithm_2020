#include <bits/stdc++.h>
#include <limits.h>

uint64_t Merge(int64_t *A, int lo, int mid, int hi, int64_t t) {
	int lindex = 0, rindex = 0;
	int llen = mid - lo + 1;
	int rlen = hi - mid;
	uint64_t count = 0;
	//begin count
	while(1) {
		if(rindex < rlen-1 && lindex < llen-1) {
			if(A[mid + 1 + rindex] - A[lo + lindex] > t) {
				count += rlen - rindex;
				lindex ++;
			}
			else {
				rindex ++;
			}
		}
		else if(rindex == rlen-1 && lindex < llen-1) {
			if(A[mid + 1 + rindex] - A[lo + lindex] > t) {
				count += rlen - rindex;
				lindex ++;
			}
			else {
				break;
			}
		}
		else if(rindex < rlen-1 && lindex == llen-1) {
			if(A[mid + 1 + rindex] - A[lo + lindex] > t) {
				count += rlen - rindex;
				break;
			}
			else {
				rindex ++;
			}
		}
		else if(rindex == rlen-1 && lindex == llen-1){
			if(A[mid + 1 + rindex] - A[lo + lindex] > t) {
				count += rlen - rindex;
			}
			break;
		};
	}
	
	//use in-place mergesort
	int lstart = lo, rstart = mid + 1;
	if(A[mid] <= A[rstart]) return count;

	while(lstart <= mid && rstart <= hi) {
		if(A[lstart] <= A[rstart]) {//A[lstart] in correct place
			lstart ++;
		}
		else {
			int64_t value = A[rstart];//attention!
			int index = rstart;
			while(index > lstart) {
				A[index] = A[index - 1];
				index --;
			}
			A[lstart] = value;
			lstart ++;
			mid ++;
			rstart ++;
		}
	}

	return count;
}

uint64_t MergeSort(int64_t *A, int lo, int hi, int64_t t) {
	if(lo == hi) {
		return 0;
	}
	int mid = (lo + hi) / 2;
	uint64_t left = MergeSort(A, lo, mid, t);
	uint64_t right = MergeSort(A, mid+1, hi, t);
	uint64_t between = Merge(A, lo, mid, hi, t);
	//printf("left:%d, right:%d, between:%d\n", left, right, between);
	return left + right + between;
}

int64_t *CrePrefixArr(int64_t *A, int n) {
	int64_t *pre = (int64_t*)malloc(sizeof(int64_t) * (n+1));
	pre[0] = (int64_t)0;
	for(int i = 0; i < n; i++) {
		pre[i + 1] = A[i] + pre[i]; 
	}
	return pre;
}

int main() {
	int n;
	int64_t t;
	scanf("%d %lld", &n, &t);
	int64_t *A = (int64_t*)malloc(sizeof(int64_t)*n);
	for(int i = 0; i < n; i++) {
		//scanf("%lld", &A[i]);
		A[i] = (int64_t)(-i);
	}

	int64_t *pre = CrePrefixArr(A, n);	
	uint64_t cnt = MergeSort(pre, 0, n, t);
	printf("%lu", cnt);	

	return 0;
}
