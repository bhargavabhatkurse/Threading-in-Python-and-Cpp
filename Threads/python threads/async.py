import asyncio

async def func1():
    print("first email sent")
    asyncio.create_task(func2())
    await asyncio.sleep(3)
    print("first email received")

async def func2():
    print("second email sent")
    asyncio.create_task(func3())
    await asyncio.sleep(1)
    print("second email received")

async def func3():
    print("third email sent")
    await asyncio.sleep(2)
    print("third email received")

if __name__ == '__main__':
    #asyncio.run(func1())
    pass


# #o/p
# first email sent
# second email sent
# third email sent
# second email received
# third email received
# first email received
# [Finished in 3.3s]

#---------

#asynchronous function is called a coroutine
#coroutine is declared with async and await keyword
#coroutine functions return coroutine objects when called
#the coroutine objects needs to be called

async def func1():
    print("hello")
    await asyncio.sleep(2) #we are waiting for this delay to work
    print("awake now")

print(asyncio.iscoroutinefunction(func1))  # true

#asyncio.run(func1())


#----

async def fetch_data():
    print("fetching date...")
    await asyncio.sleep(2)
    print("data returned..")
    return {"data":100}

async def task2():
    for i in range(10):
        print(i)
    await asyncio.sleep(1)
    print("loop complete..")

async def main():
    x = asyncio.create_task(fetch_data())
    y = asyncio.create_task(task2())

    await x,y  
    #to wait for both x and y tasks to complete before the main function itself completes. This means that main will wait for both fetch_data() and task2() to finish before it completes.
    #If you remove await x, y, the code will not wait for these tasks to complete, and it will finish the main function as soon as it reaches the end of the main function's body.

asyncio.run(main())


