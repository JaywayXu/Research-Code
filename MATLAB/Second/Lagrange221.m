function [py0] = Lagrange221()
%LAGRANGE插值求f(x)=e^x*(3*x-e^x)

%设置初始值
X = [1.00 1.02 1.04 1.06];
Y = exp(X).*(3*X-exp(X));
x = 1.03;

%求解
n = length(X);
L = zeros(n,n);
for k = 1:n
    V = 1;
    for j = 1:n
        if k ~= j
            V = conv(V,poly(X(j)))/(X(k)-X(j));
        end
    end
    L(k,:) = V;
end
C = Y*L;

px0 = x;
py0 = 0;
px = 0:1/100:2;
py = 0;
for k = 1:n
    py = py+px.^(k-1)*C(n+1-k);
    py0 = py0+px0^(k-1)*C(n+1-k);
end

%绘图
%原函数
f = exp(px).*(3*px-exp(px));
plot(px,f);
hold on;
%原数据点
scatter(X,Y);
hold on;
%插值出的函数
plot(px,py);
hold on;
%求解点
scatter(px0,py0,'g');
end
