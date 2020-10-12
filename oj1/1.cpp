#include <bits/stdc++.h>
using namespace std;

static int rec_time = 0;
static vector<int> biases;

void AddSubsets(vector<int>& subsets, int pow_size, int size) {//pow_size = 2^size - 1
	vector<int> temp;
	for(int i = size-1; i >= 0; i--) {
		temp.push_back(biases[i]);
	}//temp.size() = size;

	int temp_sum;
	for(int i = 1; i <= pow_size; i++) {
		temp_sum = 0;
		for(int j = 0; j < size; j++) {
			if(i & (1<<j)) {
				temp_sum += temp[j];
			}
		}
		subsets.push_back(temp_sum);
	}
}

void LoopPrint(int first, int brk1, int brk2, int last) {
	int loop_time = pow(2, rec_time) - 1;
	vector<int> cur_biases;
	AddSubsets(cur_biases, loop_time, rec_time);
	sort(cur_biases.begin(), cur_biases.end());
	assert(cur_biases.size() == loop_time);

	for(int i = first; i < brk1; i++) {
		printf("%d ", i);
	}
	for(int i = brk2; i < last; i++) {
		printf("%d ", i);	
	}
	for(int k = 0; k < loop_time; k++) {
		for(int i = first + cur_biases[k]; i < brk1 + cur_biases[k]; i++) {
			printf("%d ", i);
		}
		for(int i = brk2 + cur_biases[k]; i < last + cur_biases[k]; i++) {
			printf("%d ", i);
		}		
	}
	printf("\n");
}

void OddPrint(int start, int mid, int end, int len) {
	//upper right row 
	LoopPrint(start, start, start, mid);	
	//upper right column
	LoopPrint(mid, mid, mid, end+1);
		
	if(len > 3) {
		//bottom left row
		LoopPrint(mid, mid, mid, end+1);		
		//bottom left column
		LoopPrint(start, start, start, mid-1);
	}
	
	//bottom left one column
	LoopPrint(mid+1, mid+1, mid+1, end+1);
	LoopPrint(mid-1, mid-1, mid-1, mid);
	
	//mid row
	LoopPrint(mid, mid, mid, mid+1);
	LoopPrint(mid+1, mid+1, mid+1, end+1);
	
	//mid column
	if(len > 3) {
		LoopPrint(mid+2, mid+2, mid+2, end+1);
		LoopPrint(mid, mid, mid, mid+1);
	}
} 

void EvenPrint(int start, int mid, int end, int len) {
	//upper right row 
	LoopPrint(start, start, start, mid);	
	//upper right column
	LoopPrint(mid, mid, mid, end+1);
		
	if(len > 3) {
		//bottom left row
		LoopPrint(mid, mid, mid, end+1);		
		//bottom left column
		LoopPrint(start, start, start, mid-1);
	}
	
	//bottom left one column
	if(len > 2) {
		LoopPrint(mid+1, mid+1, mid+1, end+1);
		LoopPrint(mid-1, mid-1, mid-1, mid);
	
		//mid two columns
		/*fail to package the code*/
		LoopPrint(start, mid-1, mid+2, end+1);
		LoopPrint(mid-1, mid-1, mid-1, mid+1);	
		
		//mid two rows
		LoopPrint(mid-1, mid-1, mid-1, mid+1);
		LoopPrint(start, mid-2, mid+1, end+1);
	}
}

void GoldMiner(int start, int end) {
	int len = end - start + 1;
	if(len <= 1) return;
	
	int mid = (start + end + 1)/2;
	
	if(len % 2 == 1) {
		OddPrint(start, mid, end, len);
		rec_time ++;
		biases.push_back(mid);
		GoldMiner(start, mid-1);
	}
	else {
		EvenPrint(start, mid, end, len);
		rec_time ++;
		biases.push_back(mid);
		GoldMiner(start, mid-2);
	} 
}

int main() {
	int n;
	scanf("%d", &n);
	GoldMiner(1, n);
	return 0;
}
