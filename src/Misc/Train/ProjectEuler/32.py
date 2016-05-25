#32
"""
m, n ==> (m+n)-1 or (m+n)
2(m+n)-1 = 9 or 2(m+n) = 9
m+n=5
m,n = 1, 4 or 2,3
"""
from sets import Set

def all_perms(str):
    if len(str) <= 1:
        yield str
    else:
        for perm in all_perms(str[1:]):
            for i in range(len(str)+1):
                yield perm[:i] + str[0:1] + perm[i:]

products = Set()

for perm in all_perms('123456789'):
    m_and_n = perm[:5]
    product = perm[5:]

    allowed_position = [1, 2]
    for pos in allowed_position:
        m = m_and_n[:pos]
        n = m_and_n[pos:]
        if int(m) * int (n) == int(product):
            products.add(int(product))

print sum(products)
    
