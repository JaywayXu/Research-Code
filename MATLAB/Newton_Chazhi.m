function [] = Newton_Chazhi(x)
%NEWTON²åÖµÇóÎÂ¶È

X = [6 8 10 12 14 16 18];
Y = [18 20 22 25 30 28 24];

n = length(X);
D = zeros(n,n);
D(:,1) = Y';

for j = 2:n
    for k = j:n
        D(k,j) = (D(k,j-1)-D(k-1,j-1))/(X(k)-X(k-j+1));
    end
end

C = D(n,n);
for k = (n-1):-1:1
    C = conv(C,poly(X(k)));
    m = length(C);
    C(m)=C(m)+D(k,k);
end

px0 = [10.5 16.5];
py0 = [0 0];
px = 6:1/100:18;
py = 0;
for k = 1:n
    py = py+px.^(k-1)*C(n+1-k);
    py0 = py0+px0.^(k-1)*C(n+1-k);
end

plot(px,py);
hold on;
plot([10.5,10.5],ylim);
hold on;
plot([16.5,16.5],ylim);
hold on;
py01 = px*0+py0(1);
plot(px,py01);
hold on;
py02 = px*0+py0(2);
plot(px,py02);
end
