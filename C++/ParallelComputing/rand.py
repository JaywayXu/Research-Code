import random

of = open('input.txt', 'w+')
of.write("2000000")
for i in range(1, 2000000):
    a = random.randint(1, 2000000)
    a = str(a)
    of.write(" %s" % (a))
of.close()

