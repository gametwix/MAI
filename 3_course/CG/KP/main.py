import matplotlib.pyplot as plt
import numpy as np

def nbol(x,s,k,listx):
    if(k == 1):
        if(x<=listx[s+1] and x>=listx[s]):
            return 1
        else:
            return 0
    else:
        if(listx[s+k-1]-listx[s] != 0 and listx[s+k]-listx[s+1] != 0):
            return (x-listx[s])*nbol(x,s,k-1,listx)/(listx[s+k-1]-listx[s]) + (listx[k+s] - x)*nbol(x,s+1,k-1,listx)/(listx[s+k]-listx[s+1])
        else:
            return 0


def func(tt,listx,listy,m):
    t = list()
    for i in range(len(listx)-m):
        t.append(i+1)
    k = t[-1]+1
    for i in range(m):
        t.insert(0,0)
        t.append(k)
    d = 0
    #print(t)
    for i in range(len(t)-1):
        if tt >= t[i] and tt < t[i+1]:
            #print(tt)
            d = i
            break
    cx = list()
    cy = list()
    for i in range(m):
        print(d)
        cx.append(listx[d-i])
        cy.append(listy[d-i])
    for r in range(m,1,-1):
        i = d
        for s in range(r-1):
           
            u_i = t[i]
            u_ir = t[i+r-1]
            print(u_i,u_ir)
            omega = (tt - u_i)/(u_ir - u_i)
            cx[s] = omega*cx[s] + (1 - omega)*cx[s+1]
            cy[s] = omega*cy[s] + (1 - omega)*cy[s+1]
            i = i-1
    return [cx[0],cy[0]]
    

listx = [1,3,4,5,7,5]
listy = [2,7,1,10,3,3]

fig = plt.figure()
fig.subplots_adjust(right=0.7)

t = np.linspace(0, len(listx) - 3+1 - 0.001, 100)
func(3.8,listx,listy,3)
#x = [func(ti,listx,listy,3)[0] for ti in t]
#y = [func(ti,listx,listy,3)[1] for ti in t]


#plt.plot(x,y)
plt.plot(listx,listy,"o")



plt.show()