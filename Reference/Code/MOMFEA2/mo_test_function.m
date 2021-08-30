function [obj,convio]=mo_test_function(x,fun)

 D=length(x);
 convio=0;
% ZDT4
if strcmp(fun,'ZDT4-R') 
    y=x(2:end);
    gx=1+10*(D-1)+sum(y.*y-10*cos(4*pi*y));
    obj(1) = x(1);
    obj(2) = gx*(1-sqrt(x(1)/gx));
end
if strcmp(fun,'ZDT4-A') 
    y=x(2:end);
    gx= -20*exp(-0.2*sqrt(sum(y.^2)/(D-1))) - exp(sum(cos(2*pi*y))/(D-1)) + 21 + exp(1);
    obj(1) = x(1);
    obj(2) = gx*(1-sqrt(x(1)/gx));
end

if strcmp(fun,'ZDT4-G') 
    y=x(2:end);
    gx = 2 + sum(y.^2)/4000;
    gx_2=1;
    for i=2:D
        gx_2=gx_2*cos(x(i)/sqrt(i));
    end
    gx=gx-gx_2;
    obj(1) = x(1);
    obj(2) = gx*(1-sqrt(x(1)/gx));
end

if strcmp(fun,'ZDT4-RC') 
    y=x(2:end);
    gx=1+10*(D-1)+sum(y.*y-10*cos(4*pi*y));
    obj(1) = x(1);
    obj(2) = gx*(1-sqrt(x(1)/gx));
    f1=obj(1);
    f2=obj(2);
    theta=-0.05*pi;
    a= 40;
    b=5;
    c=1;
    d=6;
    e=0;
    convio=(a*abs(sin(b*pi*(sin(theta)*(f2-e) + cos(theta)*f1)^c))^d) - cos(theta)*(f2-e) + sin(theta)*f1;
    if convio<=0
        convio=0;
    end
end

%MT benchmarks

if strcmp(fun,'p1t1') 
    y=x(2:end);
    gx=1+sum(y.*y);
    obj(1) = gx* cos(0.5*pi*x(1));
    obj(2) = gx* sin(0.5*pi*x(1));
end

if strcmp(fun,'p1t2') 
    y=x(2:end);
    gx=1+ (9/(D-1))*sum(abs(y));
    obj(1) = x(1);
    obj(2) = gx*(1 - (x(1)/gx)^2);
end


if strcmp(fun,'p6t1') 
    %load('Snl.mat');
    z=x(2:end); %-Snl;  % + shift
    
    gx = 2 + sum(z.^2)/4000;
    gx_2=1;
    
    for i=1:length(z)
        gx_2=gx_2*cos(z(i)/sqrt(i)); %(i-2) if i=3:D
    end
    gx=gx-gx_2;
    obj(1)=gx*cos(x(1)*0.5*pi);
    obj(2)=gx*sin(x(1)*0.5*pi);
end

if strcmp(fun,'p6t2') 

    shift = zeros(1,length(x)-1);
    shift(5:end)=20;
%     load('Spl2');
%     y=x(2:end)-Spl2;

    y=x(2:end)-shift;

    gx= -20*exp(-0.2*sqrt(sum(y.^2)/(D-1))) - exp(sum(cos(2*pi*y))/(D-1)) + 21 + exp(1);
    obj(1)=gx*cos(x(1)*0.5*pi);
    obj(2)=gx*sin(x(1)*0.5*pi);
   
end


if strcmp(fun,'p9t1') 
%     load('Snl.mat');  % 3:25 = 20 (25D g function)
%     z=x(3:end)-Snl;  % + shift
    
    shift = 20*ones(1,length(x)-1);
    %shift(5:end)=20;
    
     z=x(2:end)-shift;
    gx = 2 + sum(z.^2)/4000;
    gx_2=1;
    
    for i=1:length(z)
        gx_2=gx_2*cos(z(i)/sqrt(i)); %(i-2) if i=3:D
    end
    gx=gx-gx_2;
    obj(1)=gx*cos(x(1)*0.5*pi)*cos(x(2)*0.5*pi);
    obj(2)=gx*cos(x(1)*0.5*pi)*sin(x(2)*0.5*pi);
    obj(3)=gx*sin(x(1)*0.5*pi);
end

if strcmp(fun,'p9t2') 
%     y=x(2:end);
%     gx= -20*exp(-0.2*sqrt(sum(y.^2)/(D-1))) - exp(sum(cos(2*pi*y))/(D-1)) + 21 + exp(1);
%     obj(1) = x(1);
%     obj(2) = gx*(1-sqrt(x(1)/gx));

    y=x(3:end);
    gx= -20*exp(-0.2*sqrt(sum(y.^2)/(D-2))) - exp(sum(cos(2*pi*y))/(D-2)) + 21 + exp(1);
    obj(1) = 0.5*(x(1)+x(2));
    obj(2) = gx*(1-(obj(1)/gx)*(obj(1)/gx));
    %obj(2) = gx*(1-((x(1)+x(2))/2*gx)^2);
end

%%% 50 D problems
% % if strcmp(fun,'p9t1') 
% %     load('Snl.mat');
% %     z=x(3:end)-Snl;  % + shift
% %     
% %     gx = 2 + sum(z.^2)/4000;
% %     gx_2=1;
% %     
% %     for i=1:length(z)
% %         gx_2=gx_2*cos(z(i)/sqrt(i)); %(i-2) if i=3:D
% %     end
% %     gx=gx-gx_2;
% %     obj(1)=gx*cos(x(1)*0.5*pi)*cos(x(2)*0.5*pi);
% %     obj(2)=gx*cos(x(1)*0.5*pi)*sin(x(2)*0.5*pi);
% %     obj(3)=gx*sin(x(1)*0.5*pi);
% % end
% % 
% % if strcmp(fun,'p9t2') 
% % %     y=x(2:end);
% % %     gx= -20*exp(-0.2*sqrt(sum(y.^2)/(D-1))) - exp(sum(cos(2*pi*y))/(D-1)) + 21 + exp(1);
% % %     obj(1) = x(1);
% % %     obj(2) = gx*(1-sqrt(x(1)/gx));
% % 
% %     y=x(3:end);
% %     gx= -20*exp(-0.2*sqrt(sum(y.^2)/(D-2))) - exp(sum(cos(2*pi*y))/(D-2)) + 21 + exp(1);
% %     obj(1) = 0.5*(x(1)+x(2));
% %     obj(2) = gx*(1-(obj(1)/gx)*(obj(1)/gx));
% %     %obj(2) = gx*(1-((x(1)+x(2))/2*gx)^2);
% % end
end