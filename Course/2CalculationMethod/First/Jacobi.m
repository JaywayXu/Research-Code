function [X] = Jacobi()
%JACOBI迭代解方程组

%要解的方程组
A = [4 1 -1 0;
    1 -5 -1 -3;
    2 -1 -6 1;
    5 4 4 30];
B = [8 1 -1 16]';

%初始值
P = [0 0 0 0]';
delta = 0.000000001;
max = 1000;

%求解
N = length(B);
for k = 1:max
    for j = 1:N
        X(j) = (B(j)-A(j,[1:j-1,j+1:N])*P([1:j-1,j+1:N]))/A(j,j);
    end
    err = abs(norm(X'-P));
    P = X';
    if (err<delta),break;end
end
X = X'
end
