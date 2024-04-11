import time

def is_prime_programiz(n):
    """https://www.programiz.com/dsa/algorithm"""
    print("Programiz algo")
    is_prime = True
    print(f"The number is, n = {n}")
    t1 = time.time()
    for i in range(2, ((n//2) + 1)):
        if (n % i) == 0:
            is_prime = False
            break
    print(f"Figured it out in {time.time() - t1} seconds")
    print(f"{n} is {'NOT ' if (not is_prime) else ''}a prime number")
    print('')

def is_prime_wiki(n):
    """Primality test using 6k+-1 optimization."""
    """https://en.wikipedia.org/wiki/Primality_test#Python_code"""
    
    print("Primality test using 6k+-1 optimization.")
    print(f"The number is, n = {n}")
    is_prime = True
    if n <= 3:
        is_prime = bool(n > 1)
    if n % 2 == 0 or n % 3 == 0:
        is_prime = False
    i = 5
    t1 = time.time()
    while i ** 2 <= n:
        if n % i == 0 or n % (i + 2) == 0:
            is_prime = False
        i += 6
    print(f"Figured it out in {time.time() - t1} seconds")
    print(f"{n} is {'NOT ' if (not is_prime) else ''}a prime number")
    print('')
    
for num in [7919, 8191, 131071, 524287, 6700417, 2147483647, int((((10**18) + 1) / (1000001)))]:
    is_prime_wiki(num)
    is_prime_programiz(num)
    print('')
    print('')
