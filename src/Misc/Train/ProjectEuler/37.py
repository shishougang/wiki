#37
import math

def isprime(num, primelist):
    num_sqrt = math.sqrt(num)
    for prime in primelist:
        if num % prime == 0:
            return False
        if prime > num_sqrt:
            break
    return True

def isPrime(num):
    if num == 1:
        return False
    
    num_sqrt = int(math.sqrt(num))
    i = 2
    while i <= num_sqrt:
        if num % i == 0:
            return False
        i += 1
    return True
        
def isTruncatablePrime(num):
    left_trunk = 0
    right_trunk = num
    multiplier = 1
    while right_trunk > 0:
        left_trunk += multiplier * (right_trunk % 10)
        right_trunk /= 10
        if not isPrime(left_trunk) or not isPrime(right_trunk):
            return False
        multiplier *= 10
    return True
    
primelist = [2, 3, 5, 7]
count = 0
sum = 0
num = 11
while count < 11:
    if isprime(num, primelist):
        primelist.append(num)
        if isTruncatablePrime(num):
            sum += num
            count += 1
    num += 2
    
print sum
