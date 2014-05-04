#31
import copy
def compound_money(pound_list, currency, ways):
    if currency == 0:
        ways += 1
        return ways
    if not pound_list  or  len(pound_list) == 0:
        return ways
    store_pound_list = pound_list[1:]

    if currency >= pound_list[0]:
        ways = compound_money(pound_list, currency - pound_list[0], ways)

    ways = compound_money(store_pound_list, currency, ways)
    return ways

pound_list = [1, 2, 5 ,10, 20, 50, 100, 200]
currency = 200
ways = 0
ways = compound_money(pound_list, currency, 0)
print ways
