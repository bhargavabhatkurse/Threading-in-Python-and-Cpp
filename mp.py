import threading
import time
import multiprocessing

def print_square(arr):
    for num in arr:
        time.sleep(0.001)
        square = num ** 2
        #print(square,end=" ")

def print_cube(arr):
    for num in arr:
        time.sleep(0.001)
        cube = num ** 3
        #print(cube,end=" ")

arr = [i for i in range(1000)] 

def single_thread():
    t = time.time()
    print_square(arr)
    print()
    print_cube(arr)
    
    return time.time() - t

def multi_thread():
    t = time.time()
    t1 = threading.Thread(target=print_square, args=(arr,))
    t2 = threading.Thread(target=print_cube, args=(arr,)) #comma is required to make it a tuple with one element: arr

    t1.start()
    t2.start()

    t1.join()
    t2.join()

    return time.time() - t

#print("time saved: ",single_thread() - multi_thread())

def multi_process():
    t = time.time()
    p1 = multiprocessing.Process(target=print_square, args=(arr,))
    p2 = multiprocessing.Process(target=print_cube, args=(arr,))

    p1.start()
    p2.start()

    p1.join()
    p2.join()

    return time.time() - t


square = []

def calc_square(numbers):
    global square
    for n in numbers:
        square.append(n*n)
    print("Within process: ", square)

def calc_square_shared_memory(numbers, square,v):
    for idx, n in enumerate(numbers):
        square[idx] = n*n
    print("Within process: ", square[:])
    v.value = sum(square)

def calc_square_queue(numbers, square, q):
    for n in numbers:
        q.put(n*n)


def deposit(balance,lock):
    for _ in range(100):
        time.sleep(0.01)


        #critical section
        lock.acquire()
        balance.value += 1
        lock.release()

def withdraw(balance,lock):
    for _ in range(100):
        time.sleep(0.01)

        #critical section
        lock.acquire()
        balance.value -= 1
        lock.release()


def f(x):
    for _ in range(100):
        x += x
    return (x*x)^x

if __name__ == "__main__":
    #print("time multithread: ",multi_thread());print("time saved: ",multi_process())
    arr = [1,2,3,4,5]
    # p1 = multiprocessing.Process(target=calc_square, args=(arr,))
    # p1.start()
    # p1.join()
    # print("Outside process: ", square) #empty list as it is not shared between processes


    #shared memory using array and value
    # square = multiprocessing.Array('i', 5) #array of 5 integers as output of square will also be 5
    # v = multiprocessing.Value('d', 0) #value of double type
    # p1 = multiprocessing.Process(target=calc_square_shared_memory, args=(arr,square,v))
    # p1.start()
    # p1.join()
    # print("Outside process: ", square[:]) 
    # print("Sum of square: ", v.value) #sum of square of numbers


    # #shared memory using queue
    # q = multiprocessing.Queue()
    # p1 = multiprocessing.Process(target=calc_square_queue, args=(arr,square,q))
    # p1.start()
    # p1.join()

    # while not q.empty():
    #     print(q.get(), end=" ")


    # balance = multiprocessing.Value('i', 200)
    # lock = multiprocessing.Lock() #to avoid inconsistent results
    # d = multiprocessing.Process(target=deposit, args=(balance,lock))
    # w = multiprocessing.Process(target=withdraw, args=(balance,lock))
    # d.start()
    # w.start()
    # d.join()
    # w.join()
    # print("Final balance: ", balance.value) #should be 200 as deposit and withdraw are same


    #pool - map and reduce technique
    pool = multiprocessing.Pool()
    arr = [i for i in range(1000)]
    time1 = time.time()
    result = pool.map(f, arr) #map function to all elements of list
    print("Pool Time taken: ", time.time() - time1)
    #print(result)

    #serial processing
    time2 = time.time()
    result = []
    for i in arr:
        result.append(f(i))
    print("Serial Time taken: ", time.time() - time2)


