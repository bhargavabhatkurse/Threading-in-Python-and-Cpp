import math
from concurrent.futures import ThreadPoolExecutor 
import time

PRIMES = [
    112272535095293,
    112582705942171,
    112272535095293,
    115280095190773,
    115797848077099,
    1099726899285419,
    1000000000039,
    10000000000037,
    1000000000000037,
   
    
  
]

def prime(n):

	if n < 2:
		return False
	if n == 2:
		return True

	for i in range(2,int(math.sqrt(n))+1):
		if(n % i == 0):
			return False


	return True

def normal():
	for i in range(len(PRIMES)):
		print(prime(PRIMES[i]))

def concurrent():
    with ThreadPoolExecutor() as executor:
        futures = executor.map(prime, PRIMES)
    
        for future in futures:
            print(future)

time1 = time.perf_counter()
print("using normal")
normal()
time2 = time.perf_counter()
print(time2-time1)

time1 = time.perf_counter()
print("\nusing concurrent()")
concurrent()
time2 = time.perf_counter()
print(time2-time1)


