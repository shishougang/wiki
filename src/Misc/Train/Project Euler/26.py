#26
import math

def nReciprocalCycles(num):
    div = 1
    div_list = []
    len_res = 0
    div *= (10 ** (int(math.log(num/div, 10) + 1)))
    while True:
        div = div % num
        if div == 0:
            len_res = 0
            break
        if div in div_list:
            break
        div_list.append(div)
        n = int(math.log(num/div, 10)) + 1
        len_res += (n + 1)
        div *= (10 ** n)
    return len_res

max_len = 1
res = 0
for i in range(2, 1000):
    n = nReciprocalCycles(i)
    if n > max_len:
        max_len = n
        res = i
print res
