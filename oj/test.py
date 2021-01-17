import numpy as np
import random

def check():
	resLst = []
	with open("res.txt", "r") as f:
		for line in f:
			resLst.append(line)

	res_cor = []
	with open("res_correct.txt", "r") as f:
		for line in f:
			res_cor.append(line)

	assert len(resLst) == len(res_cor)
	for i in range(len(resLst)):
		if int(resLst[i]) == int(res_cor[i]):
			continue
		else:
			print("no!")
			print("reslist "+str(i)+" "+resLst[i])
			print("res_cor " + str(i) + " " + res_cor[i])
			break
	print("finish")

def gen(n,k):
	print(n,k)
	with open("values.txt", "w") as f:
		for i in range(n):
			f.write(str(random.randint(1000,100000))+" ")

	with open("prices.txt", "w") as f:
		for i in range(n):
			f.write(str(random.randint(1, 100000))+" ")


if __name__ == "__main__":
	gen(10000,1000)

