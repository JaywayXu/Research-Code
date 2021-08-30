function [L, U] = searchspace(fun)
if strcmp(fun, 'ZDT1') || strcmp(fun, 'zdt1')...
    || strcmp(fun, 'ZDT2') || strcmp(fun, 'zdt2')...
    || strcmp(fun, 'ZDT3') || strcmp(fun, 'zdt3')
  dim = 30;
  L = zeros(1,dim);
  U = ones(1,dim);
elseif strcmp(fun, 'ZDT4') || strcmp(fun, 'zdt4')
  dim = 10;
  L = -5*ones(1,dim);
  U = 5*ones(1,dim);
  L(1) = 0; U(1) = 1;
elseif strcmp(fun, 'ZDT6') || strcmp(fun, 'zdt6')
  dim = 10;
  L = zeros(1,dim);
  U = ones(1,dim);
elseif contains(fun, 'DTLZ') || contains(fun, 'dtlz')
  dim = 30; 
  L = zeros(1,dim);
  U = ones(1,dim);
else
  disp('Error! Function not defined!')
end
end