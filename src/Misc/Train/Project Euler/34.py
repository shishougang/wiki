#34
import math

math.factorial(2)

def is_curious_num(num):
    sum_factorial = 0
    m = num
    while m > 0:
        sum_factorial += math.factorial(m % 10)
        m /= 10
    if sum_factorial == num:
        return True
    else:
        return False

lim = math.factorial(9)
check_point = 100
number = 11
sum_numbers = 0
while number < lim:
    if is_curious_num(number):
        sum_numbers += number
    if number > check_point:
        check_point *= 10
        lim += math.factorial(9)
    number += 1
print sum_numbers
