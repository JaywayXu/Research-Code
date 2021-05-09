function [e]= funcaoFi(pos)
% % Essa função retorna o valor de da função F, pudendo escolher funções F
% de 1 até 24 aproximadamente, según func_num, precisa de argumento o
% vetor pos onde contem todas as coordenadas a ser calculadas. Pos é uma
% matriz NxD.

func_num=3;


fhd=@cec14_func;


e=feval(fhd,pos',func_num);

end