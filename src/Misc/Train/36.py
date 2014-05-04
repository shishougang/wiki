
def is_palindromic_base10(num):
    num_str = str(num)
    h = len(num_str) - 1
    l = 0
    while l < h:
        if num_str[l] != num_str[h]:
            return False
        l += 1
        h -= 1
    return True

def is_palindromic_base2(num):
    num_str = ''
    while (num / 2) != 0:
        if num % 2 == 1:
            num_str = '1' + num_str
        else:
            num_str = '0' + num_str
        num = num / 2
    num_str = '1' + num_str
    h = len(num_str) - 1
    l = 0
    while l < h:
        if num_str[l] != num_str[h]:
            return False
        l += 1
        h -= 1
    return True

sum = 0
for i in range(1, 1000000):
    if is_palindromic_base10(i) and is_palindromic_base2(i):
        sum += i
        print i
print sum
        
    
