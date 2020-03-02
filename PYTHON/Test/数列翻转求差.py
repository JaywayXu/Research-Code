def fanzhuan(num):
        lis = []
        unum = 0
        le = len(str(num))
        for i in range(le):
                lis.append(num%10)
                num = (num - (num%10))/10
        for i in lis:
                unum = (unum*10 + int(i))
        return unum

a = int(input())

print(fanzhuan(a),abs(fanzhuan(a)-a))