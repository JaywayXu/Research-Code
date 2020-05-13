function [out] = Golden26()
%黄金分割搜索法求解单峰函数 在区间（0~1）上的极大值

%函数
f = inline('sin(x)-x^2','x');

%初始值
a = 0;%下界
b = 1;%上界
delta = 0.00001;
epsilon = delta;

%求解
r1 = (sqrt(5)-1)/2;
r2 = r1^2;
h = b-a;
ya = f(a);
yb = f(b);
c = a+r2*h;
d = a+r1*h;
yc = f(c);
yd = f(d);
k = 1;
A(k) = a;
B(k) = b;
C(k) = c;
D(k) = d;
while (abs(yb-ya)>epsilon) | (h>delta)
    k = k+1;
    if (yc>yd)
        b = d;
        yb = yd;
        d = c;
        yd = yc;
        h = b-a;
        c = a+r2*h;
        yc = f(c);
    else
        a = c;
        ya = yc;
        c = d;
        yc = yd;
        h = b-a;
        d = a+r1*h;
        yd = f(d);
    end
    A(k) = a;
    B(k) = b;
    C(k) = c;
    D(k) = d;
end

dp = abs(b-a);
dy = abs(yb-ya);
p = a;
yp = ya;

if (yb>ya)
    p = b;
    yp = yb;
end

G = [A' C' D' B'];
S = [p yp];
E = [dp dy];

out = [p p+dp];
end

