import os
l = os.listdir(path="./tests")

for d in l:
    print("tests/"+d[:-3])