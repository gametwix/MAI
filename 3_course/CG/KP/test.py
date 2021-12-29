import matplotlib.pyplot as plt
import numpy as np



def func(tt,listx,listy,listw,m):
    t = list()
    for i in range(len(listx)-m):
        t.append(i+1)
    k = t[-1]+1
    for i in range(m):
        t.insert(0,0)
        t.append(k)
    d = 0
    for i in range(len(t)-1):
        if tt >= t[i] and tt < t[i+1]:
            d = i
            break
    cx = list()
    cy = list()
    cw = list()
    for i in range(m):
        print(d)
        cx.append(listx[d-i]*listw[d-i])
        cy.append(listy[d-i]*listw[d-i])
        cw.append(listw[d-i])
    for r in range(m,1,-1):
        i = d
        for s in range(r-1):
           
            u_i = t[i]
            u_ir = t[i+r-1]
            print(u_i,u_ir)
            omega = (tt - u_i)/(u_ir - u_i)
            cx[s] = omega*cx[s] + (1 - omega)*cx[s+1]
            cy[s] = omega*cy[s] + (1 - omega)*cy[s+1]
            cw[s] = omega*cw[s] + (1 - omega)*cw[s+1]
            i = i-1
    return [cx[0]/cw[0],cy[0]/cw[0]]
    

listx = [1,3,4,5,7,8,1]
listy = [2,7,1,10,3,3,10]
listw = [1,3,1,5,1.3,1,1]

fig = plt.figure()
fig.subplots_adjust(right=0.7)

t = np.linspace(0, len(listx) - 3+1 - 0.001, 100)
x = [func(ti,listx,listy,listw,3)[0] for ti in t]
y = [func(ti,listx,listy,listw,3)[1] for ti in t]


plt.plot(x,y)
plt.plot(listx,listy,"o")



plt.show()