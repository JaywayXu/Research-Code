function [x] = Newton21()
%牛顿迭代求根号5近似值

%函数
y = inline('x^2-5','x');
dy = inline('2*x','x');

%设置初始值
P(1) = 2.2;
tol = 10e-9;
max = 1000;

%迭代
for k = 2:max	
	P(k) = P(k-1)-y(P(k-1))/dy(P(k-1));	
	err = abs(P(k)-P(k-1));
	p = P(k);
	if (err<tol),break,end
end

P = P';

%设置输出精度
x = vpa(p,10);

%绘图
px = 2:1/100:3;
%原函数
py = px.^2-5;
plot(px,py);
hold on;
%y = 0函数
py0 = px*0;
plot(px,py0);
hold on;
%求出的点
scatter(x,0);
end
