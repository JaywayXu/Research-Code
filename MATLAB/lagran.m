function [C,L]=lagran(X,Y)
X = [1 2 3 4 5 6]
Y = [66 66 65 64 63 63]
w = length(X);
n = w-1;
L=zeros(w,w);
for k=1:n+1
    V=1;
    for j=1:n+1
        if k~=j
            V=conv(V,poly(X(j)))/(X(k)-X(j));
        end
    end
    L(k,:)=V;
end
C=Y*L
T=sum(C)