function [quad] = Romberg25()
%Romberg算法求3^x*x^1.4*(5*x+7)*sin(x^2)积分(1~3)

%函数
f = inline('3^x*x^1.4*(5*x+7)*sin(x^2)','x');

%初始值
a = 1;%下界
b = 3;%上界
n = 10;
tol = 0.00001;

%求解
M=1;
h=b-a;
err=1;
J=0;
R=zeros(4,4);
R(1,1)=h*(f(a)+f(b))/2;

while((err>tol)&(J<n))|(J<4)
   J=J+1;
   h=h/2;
   s=0;
   for p=1:M
      x=a+h*(2*p-1);
      s=s+f(x);
   end
   R(J+1,1)=R(J,1)/2+h*s;
   M=2*M;
   for K=1:J
      R(J+1,K+1)=R(J+1,K)+(R(J+1,K)-R(J,K))/(4^K-1);
   end
   err=abs(R(J,J)-R(J+1,K+1));
end

quad=R(J+1,J+1);

end
