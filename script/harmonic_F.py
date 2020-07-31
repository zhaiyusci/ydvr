#!/usr/bin/env python3
# coding: utf-8

# In[1]:


from sympy import *


# In[2]:


N = symbols("N", Integer=True)


# In[3]:


def U(polyn):
    c=polyn.all_coeffs()
    res = 0
    for i in range(0,len(c),2):
        res += c[i] * N **(len(c)-1-i)
    return res


# In[4]:


def F(p,r):
    if r%2 != p%2:
        return []
    if r == p :
        return [1]
    if r == p-2 :
        return [0,1]
    coeff1 = F(p, r+4)
    coeff2 = F(p, r+2)
    # build the polynomial from the coeffs
    Fr2p = 0
    Frp = 0
    for i,c in enumerate(coeff1):
        Fr2p += c*N**i
    for i,c in enumerate(coeff2):
        Frp += c*N**i
    r +=2
    Fr_2p=Rational((p-r),(p+r))*(N**2-(r+1)**2)*Fr2p +Rational(2*r,(p+r))*U(Poly((N+r+1)*Frp.subs(N,N+2)))
    r -= 2
    return list(reversed(Poly(Fr_2p).all_coeffs()))
    


# In[23]:


print("// generate using tools/harmonic_F.py")
for p in range(0,21):
    for r in range(p,-1,-2):
        print("{", end = "")
        print(f"std::make_pair({p:2d}, {r:2d}), ", end = "")
        print("std::vector<int>({", end = "")
        print(*F(p, r), sep=", ", end = "")
        print("})},")
        


# In[ ]:




