function [C] = Poly_Nihe()
%多项式拟合求体重身高关系

%身高和体重
H = [0.75 0.86 0.96 1.08 1.12 1.26 1.35 1.51 1.55 1.60 1.63 1.67 1.71 1.78 1.85];
W = [10 12 15 17 20 27 35 41 48 50 51 54 59 66 75];
M = 2;

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
px = 0:1/100:2;
py = 0;
for k = 1:1:M+1
    py = py+C(k).*px.^(M-k+1);
end
plot(px,py);
end
