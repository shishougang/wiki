#24
import math

def nthPermutationCore(num_list, n, nth_num):
    len_sum = len(num_list) - 1
    fac_num = math.factorial(len_sum)
    if n < fac_num:
        nth_num += num_list[0]
        num_list.remove(num_list[0])
        return nthPermutationCore(num_list, n, nth_num)
    nth = n / fac_num
    nth_num += num_list[nth]
    num_list.remove(num_list[nth])
    n -= nth * fac_num
    if n == 0:
        return nth_num
    return nthPermutationCore(num_list, n, nth_num)

def nthPermutation(num_list, n):
    nth_num = ''
    nth_num = nthPermutationCore(num_list, n, nth_num)
    for i in range(len(num_list)):
        nth_num += num_list[i]
    return nth_num

num_list = []
for i in range(10):
    num_list.append(str(i))
print num_list

n_millionth_num = nthPermutation(num_list, 1000000 - 1)
print n_millionth_num
