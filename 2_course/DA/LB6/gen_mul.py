import random

random.seed()
size = int(input())
test = []
ans = []

for i in range(size):
    a = random.randint(10,pow(10,100))
    b = random.randint(10,pow(10,100))
    
    sym = '/'
    if b == 0 :
        ans.append('Error')
    else:
        ans.append(a // b)
    #ans.append(a - b)
    #ans.append(a - b)
    test.append(a)
    test.append(b)
    test.append(sym)
    

with open("test","w") as f:
    for s in test:
        f.write(str(s)+"\n")
with open("ans","w") as f:
     for s in ans:
        f.write(str(s)+"\n")
