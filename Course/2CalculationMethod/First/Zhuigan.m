function [x] = Zhuigan()
%追赶法解三对角线方程组

%要解的方程组
a = [4 4 4 4 4];
c = [-1 -1 -1 -1];
d = [-1 -1 -1 -1];
b = [100 0 0 0 200]';

%求解
%获取长度
n=length(a);
n1=length(c);
n2=length(d);
%初始化
L=zeros(n);
U=zeros(n);
p=1:n;
q=1:n-1;
x=1:n;
y=1:n;
%追赶法程序主体
p(1)=a(1);
for i=1:n-1
    q(i)=c(i)/p(i);
    p(i+1)=a(i+1)-d(i)*q(i);
end
%正解y
y(1)=b(1)/p(1);
for i=2:n
    y(i)=(b(i)-d(i-1)*y(i-1))/p(i);
end
%倒解x
x(n)=y(n);
for i=(n-1):-1:1
    x(i)=y(i)-q(i)*x(i+1);
end
%L,U矩阵
for i=1:n
    L(i,i)=p(i);
    U(i,i)=1;
end
for i=1:n-1
    L(i+1,i)=d(i);
	U(i,i+1)=q(i);
end
