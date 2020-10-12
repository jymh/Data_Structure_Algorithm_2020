import numpy as np

with open("1.txt", "r") as f:
	info = {}
	cnt = 0
	for line in f:
		lst = line[:-2].split(" ")
		info[cnt] = lst
		cnt += 1
	#print(info, cnt)

n = 3000
A = np.zeros((n,n))
for index in range(0, len(info)-1, 2):
	for i in range(len(info[index])):
		for j in range(len(info[index+1])):
			row = int(info[index][i]) - 1
			column = int(info[index+1][j]) - 1
			if row == column or row == column:
				print("i={},j={} is invalid!".format(row, column))
			else:
				A[row][column] = 1

for i in range(n):
	for j in range(n):
		if i == j or i == j+1:
			continue
		if A[i][j] == 0:
			print("A[{}][{}] is not 1!".format(i+1,j+1))
print(A)
