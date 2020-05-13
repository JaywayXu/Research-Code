function [s] = FuhuaTixing241()
%复化梯形公式求sqrt(4-sin(x)^2)积分(0~1/4)

%函数
f = inline('sqrt(4-sin(x)^2)','x');

%初始值
a = 0;%下界
b = 1/4;%上界
M = 10;

%求解
h=(b-a)/M;
s=0;
for k=1:(M-1)
   x=a+h*k;
   s=s+f(x);
end

s=h*(f(a)+f(b))/2+h*s;

%绘图
x = 0:1/100:1/4;
y = sqrt(4-sin(x).^2);
%原函数
plot(x,y,'g');
hold on;
%梯形
px = a;
for k=1:M
    line([a,a+h],[f(a),f(a+h)]);
    hold on;
    line([a,a],[1.984,f(a)]);
    hold on;
    a = a+h;
end
line([b,b],[1.984,f(b)]);
end
