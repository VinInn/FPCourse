def cos(x) :
    getcontext().prec += 6
    i, lasts, s, fact, num, sign = 0, 0, 1, 1, 1, 1
    while s != lasts:
        lasts = s
        i += 2
        fact *= i * (i-1)
        num *= x * x
        sign *= -1
        s += num / fact * sign
#    getcontext().prec -= 2
    return +s


def cosPrint(x) :
    i, lasts, s, fact, num, sign = 0, 0, 1, 1, 1, 1
    while s != lasts:
        lasts = s
        i += 2
        fact *= i * (i-1)
        num *= x * x
        sign *= -1
        t = num / fact * sign
        s += t
        print(i,s,t)
    return +s

from decimal import *
getcontext().rounding=ROUND_DOWN
getcontext().prec=4
x= Decimal('1.149')
print(x)
c=cosPrint(x)
getcontext().prec=4
print(x,+c)
getcontext().prec=6
c=cosPrint(x)
getcontext().prec=4
print(x,+c)
getcontext().prec=8
c=cosPrint(x)
getcontext().prec=4
print(x,+c)
getcontext().prec=10
c=cosPrint(x)
getcontext().prec=4
print(x,+c)
getcontext().prec=12
c=cosPrint(x)
getcontext().prec=4
print(x,+c)

Decimal('1.41162')
