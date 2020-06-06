import random
import sympy

def EXTENDED_EUCLIDEAN(a, b):
    if b == 0:
        return (a, 1, 0)
    else:
        (d2, x2, y2) = EXTENDED_EUCLIDEAN(b, a % b)
        (d, x, y) = (d2, y2, x2 - (a//b)*y2)
        return (d, x, y)

def getTandR(n):
    i = 0
    while n % 2 == 0:
        n = n//2
        i += 1
    return int(i), int(n)

def WITNESS(a, n, t, r):
    b = pow(a, r, n)
    if(b == (n-1)):
        b = -1
    
    for i in range(1, t + 1):
        c = pow(b, 2, n)
        
        if(c == (n-1)):
            c = -1
        if(c == 1 and (b != -1 and b != 1)):
            return True
        b = c
        
    return False

def MILLER_RABIN(n, s):
    t, r =  getTandR(n-1)
    
    for i in range(1, s):
        a = random.randint(2, n-1)
        if pow(a, n-1, n) != 1:
            return False
        if WITNESS(a, n, t, r):
            return False
    
    return True    
    
def main():
    user = int(input("Enter the modulus size: "))
    n = ((user//2) - 1)
    #p = random.randint(2, pow(2, n))
    q = random.randint(2, pow(2, n))
    e = pow(2, 16) + 1

    #while(MILLER_RABIN(p, 10) == False):
    #    p = random.randint(2, pow(2, n))

    #while(MILLER_RABIN(q, 10) == False):
    #    q = random.randint(2, pow(2, n))

    while(MILLER_RABIN(q, 10) == False or MILLER_RABIN(2*q + 1, 10) == False):
        q = random.randint(2, pow(2, n))
    p = 2*q + 1

    if(sympy.isprime(p)):
        print("P is prime")
    if(sympy.isprime(q)):
        print("Q is prime")
    print("P", p)
    print("Q", q)

    
    n = p*q
    print("N", n)
    phi = (p - 1) * (q - 1)

    (d, x, y) = EXTENDED_EUCLIDEAN(e, phi)
    print("D", d)
    
    if(x < 0):
        while(x < 0):
            x += phi
            
    #use the x value for d
    
    M = "I deserve an A"
    
    z = 0
    for c in M:
        z = z << 8
        z = z ^ ord(c)

#######ENCRYPTION AND DECRYPTION TEST#######
    #encryption
    C = pow(z, e, n)

    #decryption
    mprime = pow(C, x, n)
############################################

    #signature
    #s = pow(z, x, n)

    #print("Public Key: ", e)
    #print("Private Key: ", x)
    #print("Signature: ", s)
    #print("n (p*q): ", n)

    if(mprime == z):
        print("YES")
    
main()
