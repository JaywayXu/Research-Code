clear all; %close all;
clc
 %Function to be minimized
D=2;
% objf=inline('4*x1^2-2.1*x1^4+(x1^6)/3+x1*x2-4*x2^2+4*x2^4','x1','x2');
% objf=vectorize(objf);

objf=3; %Função Objetivo. Função Fi

% objf=cec14_func([3.3253000e+000, -1.2835000e+000]', 1)


%Initialization of DE parameters
N=20; %population size (total function evaluations will be itmax*N, must be >=5)
% itmax=30; 
itmax=10000*D/N;
F=0.8; CR=0.5; %mutation and crossover ratio

%Problem bounds
% a(1:N,1)=-1.9; b(1:N,1)=1.9; %bounds on variable x1
% a(1:N,2)=-1.1; b(1:N,2)=1.1; %bounds on variable x2

% a(1:N,1)=-100; b(1:N,1)=100; %bounds on variable x1
% a(1:N,2)=-100; b(1:N,2)=100; %bounds on variable x2

a(1:N,1:D)=-100; b(1:N,1:D)=100; %bounds on variable x***



d=(b-a);                        %Domain?
basemat=repmat(int16(linspace(1,N,N)),N,1); %used later 
basej=repmat(int16(linspace(1,D,D)),N,1); %used later

%Random initialization of positions
x=a+d.*rand(N,D);

%Evaluate objective for all particles
% fx=objf(x(:,1),x(:,2));

% fx=cec14_func([x(:,1), x(:,2)]', objf);

% fx=cec14_func([x(:,:)]', objf);

fx=cec14_func(x', objf);
FES=N;

%Find best 
[fxbest,ixbest]=min(fx);        %Retorna o minimo dos individuos e a posição do mesmo
xbest=x(ixbest,1:D);            %Pega o melhor individuo con todos os gene

%**************************************************************************
it=2;
erro=1;
%**************************************************************************

%Iterate
% for it=2:itmax;
    
    while(it<=itmax&abs(erro)>10^-8)
    
	permat=bsxfun(@(x,y) x(randperm(y(1))),basemat',N(ones(N,1)))';
	%Generate donors by mutation
	v(1:N,1:D)=repmat(xbest,N,1)+F*(x(permat(1:N,1),1:D)-x(permat(1:N,2),1:D));
 %Perform recombination
r=repmat(randi([1 D],N,1),1,D);
muv = ((rand(N,D)<CR) + (basej==r)) ~= 0;
mux = 1-muv;
u(1:N,1:D)=x(1:N,1:D).*mux(1:N,1:D)+v(1:N,1:D).*muv(1:N,1:D);
 %Greedy selection
% fu=objf(u(:,1),u(:,2));

% fu=cec14_func([u(:,1),u(:,2)]', objf);

fu=cec14_func(u', objf);
FES=FES+N;

idx=fu<fx;
fx(idx)=fu(idx);
x(idx,1:D)=u(idx,1:D);
 %Find best 
[fxbest,ixbest]=min(fx);
xbest=x(ixbest,1:D);

%         *****************************************************************
        it=it+1;
        erro=fxbest-300;
%         *****************************************************************

end %end loop on iterations
xbest
fxbest
FES
% LastName = {'Smith';'Johnson';'Williams';'Jones';'Brown'};
% Age = [38;43;38;40;49];
% Height = [71;69;64;67;64];
% Weight = [176;163;131;133;119];
% BloodPressure = [124 93; 109 77; 125 83; 117 75; 122 80];
% 
% T = table(Age,Height,Weight,BloodPressure,...
%     'RowNames',LastName)

%  uitable
 
%  T = uitable(FES,xbest,fxbest)

% T = table(FES=FES,xbest=xbest,fxbest=fxbest)