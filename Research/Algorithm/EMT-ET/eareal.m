function OffspringDec = eareal(M,proC,disC,proM,disM,LBOUND,UBOUND)
[L,D] = size(M);
P = [1:L,1:ceil(L/2)*2-L];
Parent1Dec = M(P(1:L/2),:);
Parent2Dec = M(P(L/2+1:end),:);
beta = zeros(L/2,D);
mu   = rand(L/2,D);
beta(mu<=0.5) = (2*mu(mu<=0.5)).^(1/(disC+1));
beta(mu>0.5)  = (2-2*mu(mu>0.5)).^(-1/(disC+1));
beta = beta.*(-1).^randi([0,1],L/2,D);
beta(rand(L/2,D)<0.5) = 1;
beta(repmat(rand(L/2,1)>proC,1,D)) = 1;
OffspringDec = [(Parent1Dec+Parent2Dec)/2+beta.*(Parent1Dec-Parent2Dec)/2
    (Parent1Dec+Parent2Dec)/2-beta.*(Parent1Dec-Parent2Dec)/2];
%% Polynomial mutation
Lower = repmat(LBOUND,L,1);
Upper = repmat(UBOUND,L,1);
Site  = rand(L,D) < proM/D;
mu    = rand(L,D);
temp  = Site & mu<=0.5;
OffspringDec(temp) = OffspringDec(temp)+(Upper(temp)-Lower(temp)).*((2.*mu(temp)+(1-2.*mu(temp)).*...
    (1-(OffspringDec(temp)-Lower(temp))./(Upper(temp)-Lower(temp))).^(disM+1)).^(1/(disM+1))-1);
temp = Site & mu>0.5;
OffspringDec(temp) = OffspringDec(temp)+(Upper(temp)-Lower(temp)).*(1-(2.*(1-mu(temp))+2.*(mu(temp)-0.5).*...
    (1-(Upper(temp)-OffspringDec(temp))./(Upper(temp)-Lower(temp))).^(disM+1)).^(1/(disM+1)));
for j = 1 : D
    for i = 1 : L
        if OffspringDec(i,j) < LBOUND(j)
            OffspringDec(i,j) = LBOUND(j);
        end
        if OffspringDec(i,j) > UBOUND(j)
            OffspringDec(i,j) = UBOUND(j);
        end
    end
end
end