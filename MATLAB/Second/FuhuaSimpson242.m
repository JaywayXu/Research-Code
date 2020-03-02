function [s] = FuhuaSimpson242()
%复化Simpson公式求exp(x)/(4+x^2)积分(0~1)

%函数
f = inline('exp(x)/(4+x^2)','x');

%初始值
a = 0;%下界
b = 1;%上界
M = 10;

%求解
h=(b-a)/(2*M);
s1=0;
s2=0;

for k=1:M
   x=a+h*(2*k-1);
   s1=s1+f(x);
end
for k=1:(M-1)
   x=a+h*2*k;
   s2=s2+f(x);
end

s=h*(f(a)+f(b)+4*s1+2*s2)/3;
