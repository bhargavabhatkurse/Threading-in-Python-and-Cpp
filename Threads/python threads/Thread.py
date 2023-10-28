import threading
import time
from concurrent.futures import ThreadPoolExecutor

#indicates some task being done
def func(seconds):
	print(f"sleeping for {seconds} seconds")
	time.sleep(seconds)
	return seconds

#this will happen one after the other. total time taken 6s 

# time1 = time.perf_counter()
# func(4)
# func(2)
# func(1)
# time2 = time.perf_counter()
# print(time2 - time1) #7 seconds


# time1 = time.perf_counter()
# t1 = threading.Thread(target=func,args = [4])
# t2 = threading.Thread(target=func,args = [2])
# t3 = threading.Thread(target=func,args = [1])

# t1.start()
# t2.start()
# t3.start()

# time2 = time.perf_counter()
# print(time2 - time1) #0 seconds
# # because the time which will be printed is only the time to start the thread and all three
# # can be started at the time. doesnt mean they finished 

# time1 = time.perf_counter()
# t1 = threading.Thread(target=func,args = [4])
# t2 = threading.Thread(target=func,args = [2])
# t3 = threading.Thread(target=func,args = [1])

# t1.start()
# t2.start()
# t3.start()

# t1.join() #wait till the process finishes
# t2.join()
# t3.join()

# time2 = time.perf_counter()
# print(time2 - time1) #4 seconds -> which is the slowest one



#actually how we should use threading if we want to use it in projects
def concurrent_futures():
	with ThreadPoolExecutor() as executor:
		future1 = executor.submit(func,3)
		
		future2 = executor.submit(func,2)

		future3 = executor.submit(func,1)

		print(future1.result())	#return value from func() which is seconds
		print(future2.result())	#return value from func() which is seconds
		print(future3.result())	#return value from func() which is seconds

		# ThreadPoolExecutor helps when we want to execute a lot of threads

def concurrent_futures_with_lists():
	with ThreadPoolExecutor() as executor:
		l = [3,2,1]
		results = executor.map(func,l)

		for result in results:
			print(result)

		#this helps when we want to execute lot of threads
		

# concurrent_futures()
concurrent_futures_with_lists()
