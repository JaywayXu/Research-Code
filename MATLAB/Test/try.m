%试值法求f(x)=x^2-10x+23的零点
a=6; fa=a^2-10*a+23;
b=7; fb=b^2-10*b+23;
for i = 1:3
    c=b-fb*(b-a)/(fb-fa);
    fc=c^2-10*c+23;
    if sign(fc)==sign(fa)
        a=c; fa=fc;
    else
        b=c; fb=fc;
    end
    fprintf('a: %f  b: %f\n',a,b);
    fprintf('fa: %f  fb: %f\n',fa,fb);
end