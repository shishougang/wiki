#33
"""
(10i+n)/(10d+i) = n/d ==> 9d(n-i) = i(d-n)
d>n, then d>n>i
n - i = i/9 - in/9d
n - i >= 1
i < 9, i/9 - in/9d < 1, so this equation has no solution.

(10n+i)/(10i+d) = n/d ==> 9n(d-i) = i(n-d)
d > n then n<d<i
"""

def gcd(m, n):
    M = max(m,n)
    N = min(m,n)
    while(N != 0):
        R = M % N
        M = N
        N = R
    return M

product_numerator = 1
product_denominator = 1

for i in range(1, 10):
    for d in range(1, i):
        for n in range(1, d):
            if (10*n + i) * d == (10*i + d) * n:
                product_numerator *= n
                product_denominator *= d
print product_denominator / gcd(product_numerator, product_denominator)
