%Program mainGA
% This program call a GA's function many times (runs-times) and do a mean
% of the results and take the best of them.

% =====================Adolfo Correa=======================================
% -Variables List----------------------------------------------------------
% best              The best optimus of 'runs'=51 runs (escalar)
% worst             The worst optimus of 'runs'=51 runs (escalar)
% Orden             organization of all optimus values
% median            a mediana dos otimos ordenados

clear all
clc
close();
% mex cec14_func.cpp -DWINDOWS
% f= cec14_func([3.3253000e+000, -1.2835000e+000]', 1) Assim, obtevesse um
% valor
func_num=1;
D=30;
Xmin=-100;
Xmax=100;
% pop_size=12;
% pop_size=20;
pop_size=50;


iter_max=10000/pop_size*D;


runs=51;

% fhd=str2func('cec14_func');

fhd=@cec14_func;

% xbest(runs,D)=0;


% FitnessFunction = @simple_fitness;
% numberOfVariables = 2;
% [x,fval] = ga(FitnessFunction,numberOfVariables)

for i=5:5
    func_num=i;
    for j=1:runs
        i,j,
[gbest,gbestval,FES,melhor(j,:),media(j,:)]=GAcont_func(fhd,D,pop_size,iter_max,Xmin,Xmax,func_num);

        xbest(j,:)=gbest;                       %Vetor (runs) Coordenadas dos otimos
        fbest(i,j)=gbestval;                    %Vetor (runs) valores dos otimos
        
        fprintf('\n\n')
        disp('Saida do mainGA')
        disp('fbest(i,j)')
        fbest(i,j)
        FES
    end
    f_mean(i)=mean(fbest(i,:));                 %Media dos melhores valores
    
    
    
%     Valores da Tabelinha___________________
    best=min(fbest(i,:));
    worst=max(fbest(i,:));
    Orden=sort(fbest(i,:));
    sn_1=std(Orden);
    sn=std(Orden,1);
    median=Orden(26);
 %   Final  Valores da Tabelinha___________________   
    
    figure();
    plot(Orden)
    hold on
    plot(fbest(i,:),'r')
    hold off
    pause();
%     figure();
    hist(fbest(i,:))
    pause();
    
%     EXCEL dos Valores da Tabelinha___________________
 
    cabezalho={'Best', 'Worst','Median','Mean','Stdn-1','Stdn','GA'};
    
    filename='Resultados';

    xlswrite(filename,cabezalho)
    xlswrite(filename,best,'A2:A2');
    xlswrite(filename,worst,'B2:B2');
    xlswrite(filename,median,'C2:C2');
    xlswrite(filename,f_mean(i),'D2:D2');
    xlswrite(filename,sn_1,'E2:E2');
    xlswrite(filename,sn,'F2:F2');
    
%    Final EXCEL dos Valores da Tabelinha___________________
    
end


% melhorplot=melhor;
% mediaplot=media;

melhorplot=mean(melhor)*1;
mediaplot=mean(media)/100000;
plot(melhorplot)
grid on;
% axis([0 FES/pop_size 0 50000])
% xlim([0 FES/pop_size])
ylim([0 20000])
xlabel('iterações')
ylabel('melhor valor e a media dos valores')
hold on;
plot(mediaplot,'r')
 
cabezalho={'Melhor', 'Media'};

xlswrite(filename,cabezalho,'Desempenho')
xlswrite(filename,melhorplot','Desempenho','A2');
xlswrite(filename,mediaplot','Desempenho','B2');
%  xlswrite(filename,mediaplot,'media');

% for i=1:30
% eval(['load input_data/shift_data_' num2str(i) '.txt']);
% eval(['O=shift_data_' num2str(i) '(1:10);']);
% f(i)=cec14_func(O',i);i,f(i)
% end