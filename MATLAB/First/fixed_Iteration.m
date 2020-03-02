function [x] = fixed_Iteration()
%不动点迭代求fx=x^(x-cos(x))-20=0

%函数变形
y = inline('x^(x-cos(x)+1)/20','x');

%设置初始值
P(1) = 0.1;
tol = 10e-9;
max = 1000;

%迭代
for k = 2:max
	P(k) = y(P(k-1));
	err = abs(P(k)-P(k-1));
	p = P(k);
	if (err<tol),break;end
end

P = P';

%设置输出精度
x = vpa(p,10);

%绘图
px = 0:1/100:0.2;
%原函数
py = px.^(px-cos(px))-20;
plot(px,py); 
hold on;
%y = 0函数
py0 = px*0;
plot(px,py0);
hold on;
%求出的点
scatter(x,0);
end
