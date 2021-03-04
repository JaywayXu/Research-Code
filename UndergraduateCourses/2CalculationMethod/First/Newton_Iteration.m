function [x] = Newton_Iteration()
%牛顿迭代求fx=x^5-3*x^3-2*x^2+2=0

%函数
y = inline('x^5-3*x^3-2*x^2+2','x');
dy = inline('5*x^4-9*x^2-4*x','x');

%设置初始值
P(1) = 0.5;
tol = 10e-9;
max = 1000;

%迭代
for k = 2:max	
	P(k) = P(k-1)-y(P(k-1))/dy(P(k-1));	
	err = abs(P(k)-P(k-1));
	p = P(k);
	if (err<tol),break,end
end

%设置输出精度
x = vpa(p,10);

%绘图
px = 0.5:1/100:1;
%原函数
py = px.^5-3*px.^3-2*px.^2+2;
plot(px,py);
hold on;
%y = 0函数
py0 = px*0;
plot(px,py0);
hold on;
%迭代的点
[r,c] = size(P);
for i=1:c
    scatter(P(i),y(P(i)));
end
end
