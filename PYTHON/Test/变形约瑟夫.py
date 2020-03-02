ysf = [0,1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2,1]*100
while ysf:
    print(ysf[2])
    new = ysf[2:]
    new1 = []
    while new:
        p = new.pop(0)
        if p!=ysf[2]:
            new1.append(p)
    ysf=new1