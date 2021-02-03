function [py0] = Lagrange_Chazhi(x)
%LAGRANGE插值求温度

%时间和温度
X = [6 8 10 12 14 16 18];
Y = [18 20 22 25 30 28 24];

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

px0 = [10.5 16.5];
py0 = [0 0];
px = 6:1/100:18;
py = 0;
for k = 1:n
    py = py+px.^(k-1)*C(n+1-k);
    py0 = py0+px0.^(k-1)*C(n+1-k);
end

%绘图
%原数据点
scatter(X,Y);
hold on;
%插值出的函数
plot(px,py);
hold on;
%求解点
scatter(px0,py0,'g');
end
