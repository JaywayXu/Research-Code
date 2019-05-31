function [x] = fixed_Iteration()
%不动点迭代求fx=x^(x-cos(x))-20=0

y = inline('x^(x-cos(x)+1)/20','x');
P(1) = 0.1;
tol = 10e-9;
max = 1000;

for k = 2:max
	P(k) = y(P(k-1));
	err = abs(P(k)-P(k-1));
	p = P(k);
	if (err<tol),break;end
end

P = P';
x = vpa(p,10);

px = 0:1/100:0.2;
py = px.^(px-cos(px))-20;
plot(px,py);
hold on;
py0 = px*0;
plot(px,py0);
hold on;
plot([x,x],ylim);
end
