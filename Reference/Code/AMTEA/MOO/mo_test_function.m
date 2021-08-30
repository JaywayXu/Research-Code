function [obj,convio]=mo_test_function(x,fun)
global M
% MOP test functions
% SCH FON  POL KUR
% DT1 ZDT2 ZDT3 ZDT4 ZDT6 
% DTLZ1  DTLZ2  DTLZ3 DTLZ4 DTLZ5 DTLZ6 
% F1 F2 F3 F4  F5 F6 F7 F8 F9
 
 D=length(x);
 convio=0;

% SCH
if strcmp(fun,'SCH')
    obj(1) = x(1)^2;
    obj(2) = (x(1)-2)^2;
end
 
% FON
if  strcmp(fun,'FON')
    D=3;
    y1=(x-1/sqrt(3)).^2;
    g1=sum(y1);
    y2=(x+1/sqrt(3)).^2;
    g2=sum(y2);
    obj(1) = 1-exp(-g1);
    obj(2) = 1-exp(-g2);  
end

% POL
if  strcmp(fun,'POL')
   A1=0.5*sin(1)-2*cos(1)+sin(2)-1.5*cos(2);
   A2=1.5*sin(1)-cos(1)+2*sin(2)-0.5*cos(2);
   B1=0.5*sin(x(1))-2*cos(x(1))+sin(x(2))-1.5*cos(x(2));
   B2=1.5*sin(x(1))-cos(x(1))+2*sin(x(2))-0.5*cos(x(2));
   obj(1) = 1+(A1-B1)^2+(A2-B2)^2;
   obj(2) = (x(1)+3)^2+(x(2)+1)^2; 
end

% KUR
if  strcmp(fun,'KUR') 
    x1=x(1:end-1);
    x2=x(2:end);
    y1=-10*exp(-0.2*sqrt(x1.^2+x2.^2));
    obj(1) =sum(y1);
    y2=abs(x).^0.8+5*sin(x.^3);
    obj(2) =sum(y2);   
end

% ZDT1
if strcmp(fun,'ZDT1')
    y=x(2:end);
    gx=1+9*sum(y)/(D-1);
    obj(1)=x(1);
    obj(2)=gx*(1-sqrt(x(1)/gx));
end 

% ZDT2
if strcmp(fun,'ZDT2')
    y=x(2:end);
    gx=1+9*sum(y)/(D-1);
    obj(1)=x(1);
    obj(2)=gx*(1-(x(1)/gx)^2);
  
end

% ZDT3
if strcmp(fun,'ZDT3')
    y=x(2:end);
    gx=1+9*sum(y)/(D-1);
    obj(1)=x(1);
    obj(2)=gx*(1-sqrt(x(1)/gx)-x(1)/gx*sin(10*pi*x(1)));
  
end

% ZDT4
if strcmp(fun,'ZDT4') 
    y=x(2:end);
    gx = 1 + 10*(D-1) + sum(y.*y - 10*cos(4*pi*y));
    if gx < 0
      disp('warning')
    end
    obj(1) = x(1);
    obj(2) = gx*(1-sqrt(x(1)/gx));
end

if strcmp(fun,'ZDT4-R') 
    y=x(2:end);
    gx=1+10*(D-1)+sum(y.*y-10*cos(4*pi*y));
    obj(1) = x(1);
    obj(2) = gx*(1-sqrt(x(1)/gx));
end
if strcmp(fun,'ZDT4-S') 
    y=x(2:end);
    gx = 418.9829*(D-1);
    z=zeros(1,D-1);
    pos1 = (abs(y)<=500);
    pos2 = (abs(y)>500);
    z(pos1) = y(pos1).*sin(sqrt(abs(y(pos1))));
    z(pos2) = 0.001*(abs(y(pos2))-500).^2;
    gx=gx - sum(z);
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

% ZDT6
if strcmp(fun,'ZDT6')
    y=x(2:end);
    gx=1+9*(sum(y)/(D-1))^0.25;
    obj(1)=1-exp(-4*x(1))*(sin(6*pi*x(1)))^6;
    obj(2)=gx*(1-(obj(1)/gx)^2);
 
end
 
 %DTLZ1
if  strcmp(fun,'DTLZ1')    
    xg=x(3:end);
    gx=100*(D-2+sum((xg-0.5).^2-cos(20*pi*(xg-0.5))));
    obj(1)=0.5*x(1)*x(2)*(1+gx);
    obj(2)=0.5*x(1)*(1-x(2))*(1+gx);
    obj(3)=0.5*(1-x(1))*(1+gx);
end

%DTLZ2
if  strcmp(fun,'DTLZ2') 
    xg=x(3:end);
    gx=sum((xg-0.5).^2);
    obj(1)=(1+gx)*cos(x(1)*0.5*pi)*cos(x(2)*0.5*pi);
    obj(2)=(1+gx)*cos(x(1)*0.5*pi)*sin(x(2)*0.5*pi);
    obj(3)=(1+gx)*sin(x(1)*0.5*pi);
end

 %DTLZ3
if  strcmp(fun,'DTLZ3') 
    xg=x(3:end);
    gx=100*(D-2+sum((xg-0.5).^2-cos(20*pi*(xg-0.5))));
    obj(1)=(1+gx)*cos(x(1)*0.5*pi)*cos(x(2)*0.5*pi);
    obj(2)=(1+gx)*cos(x(1)*0.5*pi)*sin(x(2)*0.5*pi);
    obj(3)=(1+gx)*sin(x(1)*0.5*pi);
end


%DTLZ4
if  strcmp(fun,'DTLZ4') 
    xg=x(3:end);
    gx=sum((xg-0.5).^2);
    obj(1)=(1+gx)*cos((x(1)^100)*0.5*pi)*cos((x(2)^100)*0.5*pi);
    obj(2)=(1+gx)*cos((x(1)^100)*0.5*pi)*sin((x(2)^100)*0.5*pi);
    obj(3)=(1+gx)*sin((x(1)^100)*0.5*pi);
end
 
%DTLZ 5
if  strcmp(fun,'DTLZ5') 
     xg=x(3:end);
     gx=sum((xg-0.5).^2);
     Q1 = x(1);
     Q2=(pi/(4*(1+gx)))*(1+2*gx*x(2)); 
%      Q2= 0.5*(1+2*gx*x(2))/(1+gx);
     obj(1)=(1+gx)*cos(Q1*0.5*pi).*cos(Q2*0.5*pi); 
     obj(2)=(1+gx)*cos(Q1*0.5*pi).*sin(Q2*0.5*pi);
     obj(3)=(1+gx)*sin(Q1*0.5*pi); 
end

% DTLZ6
if  strcmp(fun,'DTLZ6') 
     xg=x(3:end);
     gx=sum(xg.^0.1);
     Q1 = x(1);
     Q2=(pi/(4*(1+gx)))*(1+2*gx*x(2)); 
%      Q2= 0.5*(1+2*gx*x(2))/(1+gx);    
     obj(1)=(1+gx)*cos(Q1*0.5*pi).*cos(Q2*0.5*pi); 
     obj(2)=(1+gx)*cos(Q1*0.5*pi).*sin(Q2*0.5*pi);
     obj(3)=(1+gx)*sin(Q1*0.5*pi); 
end

% DTLZ7
if  strcmp(fun,'DTLZ7') 
     xg=x(3:end);
     gx=1+(9/(D-2))*sum(xg);  
     obj(1)=x(1);
     obj(2)=x(2);
     hf=3-(obj(1)/(1+gx))*(1+sin(3*pi*obj(1)))-(obj(2)/(1+gx))*(1+sin(3*pi*obj(2)));
     obj(3)=(1+gx)*hf; 
end

% F1
if  strcmp(fun,'F1') 
    for j = 1:D
        y(j) = x(j)-x(1)^(0.5*(1+3*(j-2)/(D-2)));
    end
    obj(1)=x(1);  obj(2)=1-sqrt(x(1));
    for k= 1:14
        obj(1) = obj(1)+2/14*y(2*k+1)^2;
    end
    for k= 1:15
        obj(2) = obj(2)+2/15*y(2*k)^2;
    end
end
   
% F2
if  strcmp(fun,'F2') 
    for j = 1:D
        y(j) = x(j)-sin(6*pi*x(1)+j*pi/D);
    end
    obj(1)=x(1);  obj(2)=1-sqrt(x(1));
    for k= 1:14
        obj(1) = obj(1)+2/14*y(2*k+1)^2;
    end
    for k= 1:15
        obj(2) = obj(2)+2/15*y(2*k)^2;
    end
end

% F3
if  strcmp(fun,'F3') 
    for j = 1:D
        if mod(j,2)==1
            y(j) = x(j)-0.8*x(1)*cos(6*pi*x(1)+j*pi/D);     
        else
            y(j) = x(j)-0.8*x(1)*sin(6*pi*x(1)+j*pi/D);
        end
    end
    obj(1)=x(1);  obj(2)=1-sqrt(x(1));
    for k= 1:14
        obj(1) = obj(1)+2/14*y(2*k+1)^2;
    end
    for k= 1:15
        obj(2) = obj(2)+2/15*y(2*k)^2;
    end
end

% F4
if  strcmp(fun,'F4') 
    for j = 1:D
        if mod(j,2)==1
            y(j) = x(j)-0.8*x(1)*cos((6*pi*x(1)+j*pi/D)/3);     
        else
            y(j) = x(j)-0.8*x(1)*sin(6*pi*x(1)+j*pi/D);
        end
    end
    obj(1)=x(1);  obj(2)=1-sqrt(x(1));
    for k= 1:14
        obj(1) = obj(1)+2/14*y(2*k+1)^2;
    end
    for k= 1:15
        obj(2) = obj(2)+2/15*y(2*k)^2;
    end
end

% F5
if  strcmp(fun,'F5') 
    for j = 1:D
        if mod(j,2)==1
            y(j) = x(j)-(0.3*x(1)^2*cos(24*pi*x(1)+4*j*pi/D)+0.6*x(1))*cos(6*pi*x(1)+j*pi/D); 
        else
            y(j) = x(j)-(0.3*x(1)^2*cos(24*pi*x(1)+4*j*pi/D)+0.6*x(1))*sin(6*pi*x(1)+j*pi/D); 
        end
    end
    obj(1)=x(1);  obj(2)=1-sqrt(x(1));
    for k= 1:14
        obj(1) = obj(1)+2/14*y(2*k+1)^2;
    end
    for k= 1:15
        obj(2) = obj(2)+2/15*y(2*k)^2;
    end
end

% F6
if  strcmp(fun,'F6') 
    for j = 1:D
         y(j) = x(j)-2*x(2)*sin(2*pi*x(1)+j*pi/D);
    end 
    obj(1)=cos(0.5*x(1)*pi)*cos(0.5*x(2)*pi);  
    obj(2)=cos(0.5*x(1)*pi)*sin(0.5*x(2)*pi); 
    obj(3)=sin(0.5*x(1)*pi);
    for k= 1:3
        obj(1) = obj(1)+2/3*y(3*k+1)^2;
    end
    for k= 1:2
        obj(2) = obj(2)+2/2*y(3*k+2)^2;
    end
    for k= 1:3
        obj(3) = obj(3)+2/3*y(3*k)^2;
    end
end

% F7
if  strcmp(fun,'F7') 
    for j = 1:D
        y(j) = x(j)-x(1)^(0.5*(1+3*(j-2)/(D-2)));
    end
    for j = 1:D
        z(j) = 4*y(j)^2-cos(8*y(j)*pi)+1.0 ;
    end 
    obj(1)=x(1);  obj(2)=1-sqrt(x(1));
    for k= 1:4
        obj(1) = obj(1)+2/4*z(2*k+1);
    end
    for k= 1:5
        obj(2) = obj(2)+2/5*z(2*k);
    end
end

% F8
if  strcmp(fun,'F8') 
    for j = 1:D
        y(j) = x(j)-x(1)^(0.5*(1+3*(j-2)/(D-2)));
    end
    for j = 1:D
        z(j) = cos((20*y(j)*pi)/sqrt(j)) ;
    end 
    a1 = y(3)^2+y(5)^2+y(7)^2+y(9)^2;
    a2 = y(2)^2+y(4)^2+y(6)^2+y(8)^2+y(10)^2;
    b1 = z(3)*z(5)*z(7)*z(9);
    b2 = z(2)*z(4)*z(6)*z(8)*z(10);
    obj(1) = x(1)+2/4*(4*a1-2*b1+2);
    obj(2) = 1-sqrt(x(1))+2/5*(4*a2-2*b2+2); 
end

% F9
if  strcmp(fun,'F9') 
    for j = 1:D
        y(j) = x(j)-sin(6*pi*x(1)+j*pi/D);
    end
    obj(1)=x(1);  obj(2)=1-x(1)^2;
    for k= 1:14
        obj(1) = obj(1)+2/14*y(2*k+1)^2;
    end
    for k= 1:15
        obj(2) = obj(2)+2/15*y(2*k)^2;
    end
end



end