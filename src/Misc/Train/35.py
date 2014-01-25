#35
import math
import sets
def all_circulars(str):
    for i in range(len(str)):
        yield str[i:] + str[:i]

def is_prime(number, primes_list):
    number_sqrt = int(math.sqrt(number))
    for factor in primes_list:
        if factor > (number_sqrt + 1):
            return True
        if number % factor == 0:
            return False
    while factor <= (number_sqrt + 1):
        if number % factor == 0:
            return False
        factor += 2
    return True

primes_list = [2]
circular_primes_list = sets.Set()
circular_primes_list.add('2')


for n in range(3, 1000000, 2):
    if str(n) in circular_primes_list:
        primes_list.append(n)
        continue
    if not is_prime(n, primes_list):
        continue
    primes_list.append(n)

    tmp_list = []
    is_circular = True
    for perm in all_circulars(str(n)):
        if not is_prime(int(perm), primes_list):
            is_circular = False
            break
        tmp_list.append(perm)
    if is_circular:
        for circular_prime in tmp_list:
            circular_primes_list.add(circular_prime)

print circular_primes_list
print len(circular_primes_list)


