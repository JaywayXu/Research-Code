function [X] = Gauss_Seidel()
%GAUSS_SEIDEL迭代解方程组

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
        if j==1
            X(1) = (B(1)-A(1,2:N)*P(2:N))/A(1,1);
        elseif j==N
            X(N) = (B(N)-A(N,1:N-1)*(X(1:N-1))')/A(N,N);
        else
            X(j) = (B(j)-A(j,1:j-1)*X(1:j-1)'-A(j,j+1:N)*P(j+1:N))/A(j,j);
        end
    end
    err = abs(norm(X'-P));
    P = X'
    if (err<delta),break;end
end
X = X'
end
