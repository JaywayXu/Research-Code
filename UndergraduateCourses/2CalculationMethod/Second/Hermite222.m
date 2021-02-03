function [py0] = Hermite222()
%Hermite插值求f(x)=e^x*(3*x-e^x)

%初始值
x0 = [1.00 1.05];
y0 = exp(x0).*(3*x0-exp(x0));
y1 = exp(x0).*(3*x0+3-2*exp(x0));
px0 = 1.03;
x = 0:1/100:2;

%求解
n=length(x0);
m=length(x);
for k=1:m 
	yy=0.0; 
	for i=1:n 
        h=1.0; 
        a=0.0; 
        for j=1:n 
            if j~=i 
                h=h*((x(k)-x0(j))/(x0(i)-x0(j)))^2; 
                a=1/(x0(i)-x0(j))+a; 
            end 
        end
      yy=yy+h*((x0(i)-x(k))*(2*a*y0(i)-y1(i))+y0(i)); 
    end 
    y(k)=yy;
end

%绘图
%原函数
f = exp(x).*(3*x-exp(x));
plot(x,f);
hold on;
%原数据点
scatter(x0,y0);
hold on;
%插值出的函数
plot(x,y);
%求解点
for k = 1:m
    if px0 == x(k)
        py0 = y(k);
    end
end
scatter(px0,py0,'g');
end
