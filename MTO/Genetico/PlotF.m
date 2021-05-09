% Plotador de Funções

clear
clc

% Numero da Função Fi
i=3;

% Dominio
limInf=-100;
limSup=100;

% fhd=str2func('cec14_func');

% e=feval(fhd,pos',varargin{:});

for x=limInf:1:limSup
    for y=limInf:1:limSup
        f(x+101,y+101)=cec14_func([x y]',i);
    end
end

surf(f);
        