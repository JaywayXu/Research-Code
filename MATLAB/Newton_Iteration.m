function [x] = Newton_Iteration()
%Å£¶Ùµü´úÇófx=x^5-3*x^3-2*x^2+2=0

y = inline('x^5-3*x^3-2*x^2+2','x');
dy = inline('5*x^4-9*x^2-4*x','x');
P(1) = 0.5;
tol = 10e-9;
max = 1000;

for k = 2:max	
	P(k) = P(k-1)-y(P(k-1))/dy(P(k-1));	
	err = abs(P(k)-P(k-1));
	p = P(k);
	if (err<tol),break,end
end

P = P';
x = vpa(p,10);

px = 0.5:1/100:1;
py = px.^5-3*px.^3-2*px.^2+2;
plot(px,py);
hold on;
py0 = px*0;
plot(px,py0);
hold on;
plot([x,x],ylim);
end
