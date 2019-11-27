import time


# recursive brute force function.
# complexity T(n) = T(n-1) + T(n-2) or something around O(2**n)
def Fibonacci(n):
    if n < 0:
        print("Incorrect input")
    # First Fibonacci number is 0
    elif n == 0:
        return 0
    # Second Fibonacci number is 1
    elif n == 1:
        return 1
    else:
        return Fibonacci(n-1)+Fibonacci(n-2)


# optimized fibonacci using list to store past values
# complexity O(n)
def dpFibonacci(n):
    fib = [0, 1]
    if (n < 0):
        print("Incorrect input")
    else:
        for i in range(2, n+1):
            fib.append(fib[i-1]+fib[i-2])
        return fib[n]


if __name__ == "__main__":
    n = int(input("Fibonacci of: "))

    t3 = time.time()
    res = dpFibonacci(n)
    t4 = time.time()

    print("\ndp result:", res, "in time:", t4-t3)

    t1 = time.time()
    res = Fibonacci(n)
    t2 = time.time()

    print("recursive result:", res, "in time:", t2-t1)
