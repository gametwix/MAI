import random

random.seed()
size = int(input())
test = []
ans = []

for i in range(size):
    a = random.randint(0,pow(10,100))
    b = random.randint(0,pow(10,100))
    s = random.randint(0,7)
    sym = ' '
    if s == 0:
        sym = '+'
        ans.append(a + b)
    elif s == 1:
        sym = '-'
        if b > a :
            ans.append('Error')
        else:
            ans.append(a - b)
    elif s == 2:
        sym = '*'
        ans.append(a * b)
    elif s == 3:
        sym = '/'
        if b == 0 :
            ans.append('Error')
        else:
            ans.append(a // b)
    elif s == 4:
        sym = '+'
        ans.append(a + b)
    elif s == 5:
        sym = '>'
        if a > b:
            s = 'true'
        else:
            s = 'false'
        ans.append(s)
    elif s == 6:
        sym = '<'
        if a < b:
            s = 'true'
        else:
            s = 'false'
        ans.append(s)
    elif s == 7:
        sym = '='
        if a == b:
            s = 'true'
        else:
            s = 'false'
        ans.append(s)
    
    test.append(a)
    test.append(b)
    test.append(sym)
    

with open("test","w") as f:
    for s in test:
        f.write(str(s)+"\n")
with open("ans","w") as f:
     for s in ans:
        f.write(str(s)+"\n")


