from math import sqrt

def zhijiao(a,b,c):
        if a*a+b*b==c*c or a*a+c*c==b*b or b*b+c*c==a:
                return True
        else:
                return False

def dengyao(a,b,c):
        if a==b or a==c or b==c:
                return True
        else:
                return False

def dengbian(a,b,c):
        if a==b==c:
                return True
        else:
                return False

def single(a,b,c):
        if (a+b)>c and (a+c)>b and (b+c)>a:
                if dengyao(a,b,c):
                        if dengbian(a,b,c):
                                print("等边三角形")
                        elif zhijiao(a,b,c):
                                print("等腰直角三角形")
                        else:
                                print("等腰三角形")
                elif zhijiao(a,b,c):
                        print("直角三角形")
        else:
                print("不能构成三角形")

while True:
        a = sqrt(int(input("第一条边的平方：")))
        b = sqrt(int(input("第二条边的平方：")))
        c = sqrt(int(input("第三条边的平方：")))
        single(a,b,c)