n = int(input("Enter the no. of elements: "))
if n == 1:
    print(0)
else:
    a = 0
    b = 1
    print(a)
    print(b)
    for i in range(n - 2):
        c = a + b
        a = b
        b = c
        print(c)