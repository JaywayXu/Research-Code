# c = "kxieyurebezwehewrytuheyfskrehegoyfiwtttuolksycaipoboteizontxbybntgoneycuzwrgdsonsxbouywrhebaahyusedq"
# f = {}
# for i in range(int(len(c)/2)):
#     x = c[i*2:i*2+2]
#     if x not in f:
#         f[x] = 1
#     else:
#         f[x] += 1
# a = sorted(f.items(), key=lambda x: x[1], reverse=True)
# for i in a:
#     print(i)

import numpy
a = numpy.matrix([['r', 'o', 'y', 'a', 'l'],
                  ['n', 'e', 'w', 'z', 'd'],
                  ['v', 'b', 'c', 'f', 'g'],
                  ['h', 'i', 'k', 'm', 'p'],
                  ['q', 's', 't', 'u', 'x']]
                 )

s = "kxieyurebezwehewrytuheyfskrehegoyfiwtttuolksycaipoboteizontxbybntgoneycuzwrgdsonsxbouywrhebaahyusedq"
out = ""
for i in range(int(len(s)/2)):
    x = s[i*2:i*2+2]
    x0 = numpy.argwhere(a == x[0])
    x0 = x0[0][0], x0[0][1]
    x1 = numpy.argwhere(a == x[1])
    x1 = x1[0][0], x1[0][1]
    #print(x0, x1)

    if (a[x0] == a[x1] == 't'):
        out = out+a[x0]+a[x1]
        continue

    if (x0[0] == x1[0]):
        y0 = x0[0], (x0[1]-1) % 5
        y1 = x1[0], (x1[1]-1) % 5
    elif (x0[1] == x1[1]):
        y0 = (x0[0]-1) % 5, x0[1]
        y1 = (x1[0]-1) % 5, x1[1]
    else:
        y0 = x0[0], x1[1]
        y1 = x1[0], x0[1]

    # print(y0,y1)
    out = out+a[y0]+a[y1]
print(out)
