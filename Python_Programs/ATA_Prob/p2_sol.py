def pthFactor(n, p):
    from functools import reduce
    factors = reduce(list.__add__, ([i, n//i] for i in range(1, int(n**0.5) + 1) if n % i == 0 ))
    factors.sort()
    if p > len(factors):
        return 0
    return factors[p - 1]

import time
t1 = time.time()
print(pthFactor(10**15, 5))
print(f"finished in {time.time() - t1} secs")