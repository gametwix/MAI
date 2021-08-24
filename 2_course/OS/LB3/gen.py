import random

random.seed()
r_list = []
size = int(input())
for i in range(size):
    r_list.append(random.randint(-10000000,10000000))

with open("test","w") as f:
    f.write(str(size)+"\n")
    for x in r_list:
        f.write(str(x)+"\n")

r_list.sort()

with open("ans","w") as f:
    for x in r_list:
        f.write(str(x)+"\n")