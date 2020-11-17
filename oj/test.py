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

def gen(test2):
	Q = 100
	mod = 1032
	print("{} {}".format(Q, mod))
	for i in range(Q):
		if test2 == True:
			op = random.randint(0,2)
			if op != 2:
				x = random.randint(0,1000)
				print("{} {}".format(op, x))
			else:
				y = random.randint(0,1000)
				z = random.randint(0,1000)
				print("{} {} {}".format(op,y,z))
		else:
			op = random.randint(0,1)
			x = random.randint(0,1000)
			print("{} {}".format(op, x))

if __name__ == "__main__":
	#gen(True)
	check()