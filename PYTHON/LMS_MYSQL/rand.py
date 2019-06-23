import random

of = open('data_Book.txt', 'w+')
for i in range(1, 200):
    a = random.randint(1, 30)
    p = random.randint(1, 10)
    bid = str(i)
    bname = "book"+str(i)
    author = "author"+str(a)
    phouse = "phouse"+str(p)
    of.write("%s %s %s %s\n" % (bid,bname,author,phouse))
of.close()

of = open('data_User.txt', 'w+')
for i in range(1,50):
    uid = "user"+str(i)
    password = str(i)
    of.write("%s %s\n" % (uid,password))
of.close()

of = open('data_Root.txt', 'w+')
for i in range(1,50):
    uid = "root"+str(i)
    password = str(i)
    of.write("%s %s\n" % (uid,password))
of.close()

of = open('data_Stock.txt', 'w+')
for i in range(1, 200):
    bid = str(i)
    num = str(random.randint(1,10))
    of.write("%s %s\n" % (bid,num))
of.close()

of = open('data_Lend.txt', 'w+')
for i in range(1, 200):
    uid = "user"+str(random.randint(1,50))
    bid = str(random.randint(1,200))
    y = str(random.randint(2005,2019))
    m = str(random.randint(1,12))
    d = str(random.randint(1,28))
    date = y+'-'+m+'-'+d
    of.write("%s %s %s\n" % (uid, bid, date))
of.close()
