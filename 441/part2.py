import random
import math
import sympy
import time

def pollard_Rho(n):
    i = 1
    xi = random.randint(0, n-1)
    y = xi
    k = 2
    d = 1
    while d == 1:
        i = i + 1
        xi = (pow(xi, 2) - 1) % n #(xi**2 - 1) % n
        d = math.gcd(y - xi, n)
        if  d != 1 and d != n:
            return d
        if i == k:
            y = xi
            k = 2*k

    return n

def main():
    #used for timing the program
    start_time = time.time()

    #get input from user, use pollard_rho to factor
    n = int(input("Enter the number to factor: "))
    d = pollard_Rho(n)

    #making sure factors are the prime factors
    if(sympy.isprime(d)):
        print("d is prime")
    if(sympy.isprime(n // d)):
        print("n//d is prime")
    print("Factors:")
    print("d: ", d)
    print("Other factor", n // d)

    #time it took the program to run
    end_time = time.time()
    print("Time: ", end_time - start_time)
    
main()
