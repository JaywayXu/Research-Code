% Binary Genetic Algorithm
%
% minimizes the objective function designated in ff
% Before beginning, set all the parameters in parts
% I, II, and III
% Haupt & Haupt
% 2003
clear
%_______________________________________________________
% I. Setup the GA
% ff='testfunction'; % objective function

% ff=@(x) x.^2;

% ff=str2func('8*x - 0.25*x^2');

ff=inline('8*x - 0.25*x^2');

% y = 8*x - 0.25*power(x,2);

% ff=str2func('cec14_func');% objective function_______________________________________

npar=2; % number of optimization variables
%_______________________________________________________
% II. Stopping criteria
maxit=100; % max number of iterations
mincost=-9999999; % minimum cost
%_______________________________________________________
% III. GA parameters
popsize=16; % set population size
mutrate=.15; % set mutation rate
selection=0.5; % fraction of population 
% kept
nbits=8; % number of bits in each 
% parameter
Nt=nbits*npar; % total number of bits 
% in a chormosome
keep=floor(selection*popsize); % #population members 
% that survive
%_______________________________________________________
% Create the initial population
iga=0; % generation counter 
% initialized
pop=round(rand(popsize,Nt)); % random population of 
% 1s and 0s
par=gadecode(pop,0,10,nbits); % convert binary to 
% continuous values
cost=feval(ff,par,3); % calculates population _____________________________________
% cost using ff
[cost,ind]=sort(cost); % min cost in element 1
par=par(ind,:);pop=pop(ind,:); % sorts population with 
% lowest cost first
minc(1)=min(cost); % minc contains min of 
% population
meanc(1)=mean(cost); % meanc contains mean 
% of population
%_______________________________________________________
% Iterate through generations
while iga<maxit
iga=iga+1; % increments generation counter
%_______________________________________________________
% Pair and mate
M=ceil((popsize-keep)/2); % number of matings
prob=flipud([1:keep]'/sum([1:keep]));% weights 
% chromosomes based 
% upon position in 
% list
odds=[0 cumsum(prob(1:keep))']; % probability distribution function
pick1=rand(1,M); % mate #1
pick2=rand(1,M); % mate #2
% ma and pa contain the indicies of the chromosomes 
% that will mate
ic=1;
while ic<=M
for id=2:keep+1
if pick1(ic)<=odds(id) & pick1(ic)>odds(id-1)
ma(ic)=id-1;
end % if
if pick2(ic)<=odds(id) & pick2(ic)>odds(id-1)
pa(ic)=id-1;
end % if
end % id
ic=ic+1;
end % while
%_______________________________________________________
% Performs mating using single point crossover
ix=1:2:keep; % index of mate #1
xp=ceil(rand(1,M)*(Nt-1)); % crossover point
pop(keep+ix,:)=[pop(ma,1:xp) pop(pa,xp+1:Nt)];
% first offspring
pop(keep+ix+1,:)=[pop(pa,1:xp) pop(ma,xp+1:Nt)];
% second offspring
%_______________________________________________________
% Mutate the population
nmut=ceil((popsize-1)*Nt*mutrate); % total number 
% of mutations
mrow=ceil(rand(1,nmut)*(popsize-1))+1; % row to mutate
mcol=ceil(rand(1,nmut)*Nt); % column to mutate
for ii=1:nmut
pop(mrow(ii),mcol(ii))=abs(pop(mrow(ii),mcol(ii))-1);
% toggles bits
end % ii
%_______________________________________________________
% The population is re-evaluated for cost
par(2:popsize,:)=gadecode(pop(2:popsize,:),0,10,nbits);
% decode
cost(2:popsize)=feval(ff,par(2:popsize,:));

%_______________________________________________________
% Sort the costs and associated parameters
[cost,ind]=sort(cost);
par=par(ind,:); pop=pop(ind,:);
%_______________________________________________________
% Do statistics for a single nonaveraging run
minc(iga+1)=min(cost);
meanc(iga+1)=mean(cost);
%_______________________________________________________
% Stopping criteria
if iga>maxit | cost(1)<mincost
break
end
[iga cost(1)]
end %iga
%_______________________________________________________
% Displays the output
day=clock;
disp(datestr(datenum(day(1),day(2),day(3),day(4),day(5),day(6)),0))
disp(['optimized function is ' ff])
format short g
disp(['popsize = ' num2str(popsize) ' mutrate = '
num2str(mutrate) ' # par = ' num2str(npar)])
disp(['#generations=' num2str(iga) ' best cost='
num2str(cost(1))])
disp(['best solution'])
disp([num2str(par(1,:))])
disp('binary genetic algorithm')
disp(['each parameter represented by ' num2str(nbits)' bits'])
figure(24)
iters=0:length(minc)-1;
plot(iters,minc,iters,meanc,'–');
xlabel('generation');ylabel('cost');
text(0,minc(1),'best');text(1,minc(2),'populationaverage')

