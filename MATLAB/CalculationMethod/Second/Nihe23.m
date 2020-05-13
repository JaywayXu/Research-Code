function [C] = Nihe23()
%多项式拟合

%数据
H = [0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8];
W = [0.6 1.1 1.6 1.8 2.0 1.9 1.7 1.3];

%多项式拟合次数
M = 4;

%求解
n = length(H);
B = zeros(1:M+1);
F = zeros(n,M+1);
for k = 1:M+1
    F(:,k) = H'.^(k-1);
end
A = F'*F;
B = F'*W';
C = A\B;
C = flipud(C);

%绘图
%原数据点
scatter(H,W);
hold on;
%拟合函数
px = -0.5:1/100:1.5;
py = 0;
for k = 1:1:M+1
    py = py+C(k).*px.^(M-k+1);
end
plot(px,py);
end

