%二分法求f(x)=x^2-10x+23的零点
a=6; fa=a^2-10*a+23;
b=7; fb=b^2-10*b+23;
for i = 1:3
    x=(a+b)/2;
    fx=x^2-10*x+23;
    if sign(fx)==sign(fa)
        a=x; fa=fx;
    else
        b=x; fb=fx;
    end
    fprintf('a: %f  b: %f\n',a,b);
    fprintf('fa: %f  fb: %f\n',fa,fb);
end