function [xbest,fxbest,FES,beschi,media]= GAcont_func(fhd,Dimension,Particle_Number,Max_Gen,VRmin,VRmax,varargin)
%  Continuous Genetic Algorithm
%
% minimizes the objective function designated in ff
% Before beginning, set all the parameters in parts 
% I, II, and III
% Haupt & Haupt
% 2003

% ________________________________________________________
%------------------ ADOLFO CORREA-------------------------
% ________________________________________________________
% FES           nro. de avalições

% _______Grafico de desempenho____
% beschi        vetor(1,iteraçoesMaximas) guarda the best de cada iteração
% media         vetor(1,iteraçoesMaximas) guarda a media da população de
%               cada iteração.
% ________________________________


% ________________________________________________________

% persistent par

% evalin('base','who');

% global par;




%_______________________________________________________
% I Setup the GA

% ff=str2func('cec14_func');% objective function
ff=fhd;                     % objective function
% npar=2;                   % number of optimization variables
npar=Dimension;             % number of optimization variables
varhi=VRmax; varlo=VRmin;      % variable limits
%_______________________________________________________
% II Stopping criteria

% maxit=10000*npar/12;
maxit=Max_Gen;

mincost=-9999999; % minimum cost
%_______________________________________________________
% III GA parameters
popsize=Particle_Number; % set population size
% mutrate=.2; % set mutation rate
mutrate=.5; % set mutation rate
selection=0.5; % fraction of population kept
Nt=npar; % continuous parameter GA Nt=#variables
keep=floor(selection*popsize); % #population
% members that survive
nmut=ceil((popsize-1)*Nt*mutrate); % total number of 
% mutations
M=ceil((popsize-keep)/2); % number of matings
%_______________________________________________________
% Create the initial population
iga=0; % generation counter initialized
par=(varhi-varlo)*rand(popsize,npar)+varlo; % random



% assignin('base','Coordpto', par);

% evalin('base', 'cola', par);




% cost=feval(ff,par); % calculates population cost 
% using ff
% e=feval(fhd,pos',varargin{:});
cost=feval(ff,par',varargin{:});
FES=popsize;

% ******************************
minimoDaFuncao=300;
if varargin{:}==5
    minimoDaFuncao=500;
end

% ******************************
% ******************************
beschi(floor(maxit))=0;
media(floor(maxit))=0;
% ******************************

[cost,ind]=sort(cost);  % min cost in element 1
par=par(ind,:);         % sort continuous
minc(1)=min(cost);      % minc contains min of
meanc(1)=mean(cost);    % meanc contains mean of population

% ******************************
beschi(1)=minc(1);
media(1)=meanc(1);
% ******************************

%_______________________________________________________
% Iterate through generations
while iga<floor(maxit)-1            %Verificar melhor, pois esta matando o
%                                    primeiro ponto
iga=iga+1; % increments generation counter
%_______________________________________________________
% Pair and mate
M=ceil((popsize-keep)/2); % number of matings
prob=flipud([1:keep]'/sum([1:keep])); % weights 
% chromosomes
odds=[0 cumsum(prob(1:keep))']; % probability 
% distribution 
% function
pick1=rand(1,M); % mate #1
pick2=rand(1,M); % mate #2
% ma and pa contain the indicies of the chromosomes 
% that will mate
ic=1;
while ic<=M
for id=2:keep+1
if pick1(ic)<=odds(id) & pick1(ic)>odds(id-1)
ma(ic)=id-1;
end
if pick2(ic)<=odds(id) & pick2(ic)>odds(id-1)
pa(ic)=id-1;
end
end
ic=ic+1;
end
%_______________________________________________________
% Performs mating using single point crossover
ix=1:2:keep; % index of mate #1
xp=ceil(rand(1,M)*Nt); % crossover point
r=rand(1,M); % mixing parameter
for ic=1:M
xy=par(ma(ic),xp(ic))-par(pa(ic),xp(ic)); % ma and pa
% mate
par(keep+ix(ic),:)=par(ma(ic),:); % 1st offspring
par(keep+ix(ic)+1,:)=par(pa(ic),:); % 2nd offspring
par(keep+ix(ic),xp(ic))=par(ma(ic),xp(ic))-r(ic).*xy;
% 1st
par(keep+ix(ic)+1,xp(ic))=par(pa(ic),xp(ic))+r(ic).*xy;
% 2nd
if xp(ic)<npar % crossover when last variable not selected

% % %     fprintf('xp=',xp(ic),'ic=',ic,'npar',npar);
% % xp(ic)<npar
% % xp
% % ic
% % npar
% % ix
% % 
% % par(keep+ix(ic),1:xp(ic))
% % par(keep+ix(ic)+1,xp(ic)+1:npar)
% % 
% % [par(keep+ix(ic),1:xp(ic)) par(keep+ix(ic)+1,xp(ic)+1:npar)];
% % 
% %     assignin('base','Coordpto', par);
% %     
% % %      assignin('base','xp', xp, 'ic', ic);
% % 
% % assignin('base','xp', xp);%);, 
% % 
% % assignin('base','ic', ic);
    
% par(keep+ix(ic),:)=[par(keep+ix(ic),1:xp(ic))
% par(keep+ix(ic),:)=[par(keep+ix(ic),1:xp(ic))
% par(keep+ix(ic)+1,xp(ic)+1:npar)];
% par(keep+ix(ic)+1,:)=[par(keep+ix(ic)+1,1:xp(ic))
% par(keep+ix(ic),xp(ic)+1:npar)];

par(keep+ix(ic),:)=[par(keep+ix(ic),1:xp(ic)) par(keep+ix(ic)+1,xp(ic)+1:npar)];
par(keep+ix(ic)+1,:)=[par(keep+ix(ic)+1,1:xp(ic)) par(keep+ix(ic),xp(ic)+1:npar)];


end % if
end
%_______________________________________________________
% Mutate the population
mrow=sort(ceil(rand(1,nmut)*(popsize-1))+1);
mcol=ceil(rand(1,nmut)*Nt);
for ii=1:nmut
par(mrow(ii),mcol(ii))=(varhi-varlo)*rand+varlo; 
% mutation
end % ii
%_______________________________________________________
% The new offspring and mutated chromosomes are 
% evaluated
% cost=feval(ff,par);
FES=FES+popsize;
cost=feval(ff,par',varargin{:});
%_______________________________________________________
% Sort the costs and associated parameters
[cost,ind]=sort(cost);
par=par(ind,:);
%_______________________________________________________
% Do statistics for a single nonaveraging run
minc(iga+1)=min(cost);
meanc(iga+1)=mean(cost);

% ******************************
beschi(iga+1)=minc(iga+1);
media(iga+1)=meanc(iga+1);
% ******************************

%_______________________________________________________
% Stopping criteria
if iga>maxit | cost(1)<mincost
break
end
if abs(cost(1)-minimoDaFuncao)<10E-8
    break
end
disp('Saida da funcao')
disp('counter Optimo achado nessa iteracao')
[iga cost(1)]
end %iga
%_______________________________________________________
% Displays the output
% day=clock;
% disp(datestr(datenum(day(1),day(2),day(3),day(4),day(5),day(6)),0))
% % disp(['optimized function is ' ff])
%  disp(['optimized function is cec14_func'])
% format short g
% disp(['popsize = ' num2str(popsize) ' mutrate = '...
% num2str(mutrate) ' # par = ' num2str(npar)])
% disp(['#generations=' num2str(iga) ' best cost='...
% num2str(cost(1))])
% disp(['best solution'])
% disp([num2str(par(1,:))])
% disp('continuous genetic algorithm')
% figure(24)
% iters=0:length(minc)-1;
% plot(iters,minc,iters,meanc,'-r');
% xlabel('generation');ylabel('cost');
% text(0,minc(1),'best');text(1,minc(2),'populationaverage')

% Return
xbest=par(1,:);
fxbest=cost(1);
% FES=1;
% beschi=1;
% media=1;
end