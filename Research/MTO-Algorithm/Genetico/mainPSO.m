clear all
clc

func_num=1;
D=2;
Xmin=-100;
Xmax=100;
pop_size=100;

% ******** FES ***************
% iter_max=5000

% iter_max=100/pop_size*D;

iter_max=10000/pop_size*D;

% iter_max=100000000;
% iter_max=10000*D;
% ****** END FES **************

runs=51;

fhd=str2func('cec14_func');

% xbest(runs,D)=0;

for i=3:3
    func_num=i;
    for j=1:runs
        i,j,
        [gbest,gbestval,FES,melhor(j,:),media(j,:)]= PSO_func(fhd,D,pop_size,iter_max,Xmin,Xmax,...
        func_num);
        xbest(j,:)=gbest;
        fbest(i,j)=gbestval;
        fbest(i,j)
        FES
    end
    f_mean(i)=mean(fbest(i,:));
    
    filename='Resultados';
    
    
    best=min(fbest(i,:));
    worst=max(fbest(i,:));
    Orden=sort(fbest(i,:));
    sn_1=std(Orden);
    sn=std(Orden,1);
    median=Orden(26);
    figure();
    plot(Orden)
    hold on
    plot(fbest(i,:),'r')
    hold off
%     figure();
    hist(fbest(i,:))
    
%     cabezalho=['Best' 'Worst'];

    cabezalho={'Best', 'Worst','Median','Mean','Stdn-1','Stdn','PS0'};

    xlswrite(filename,cabezalho)
    xlswrite(filename,best,'A2:A2');
    xlswrite(filename,worst,'B2:B2');
    xlswrite(filename,median,'C2:C2');
    xlswrite(filename,f_mean(i),'D2:D2');
    xlswrite(filename,sn_1,'E2:E2');
    xlswrite(filename,sn,'F2:F2');
    
    
%     T = table(['M';'F';'M'],[45 45;41 32;40 34],...
%     {'NY';'CA';'MA'},[true;false;false])

% writetable(T,'myData.xls','Sheet',2,'Range','B2:F6')
    
    
end

% melhor
%  plot(melhor')
%  hold on;
%  plot(media')
%  
 
%  plot(melhor(1,:))
%  axis([0 50 0 5000])
%  hold on;
%  plot(media(1,:),'r')
 
 
melhorplot=mean(melhor)*1;
mediaplot=mean(media)/1;
plot(melhorplot)
grid on;
axis([0 FES/pop_size 0 5000])
hold on;
plot(mediaplot,'r')
 
cabezalho={'Melhor', 'Media'};

xlswrite(filename,cabezalho,'Desempenho')
xlswrite(filename,melhorplot','Desempenho','A2');
xlswrite(filename,mediaplot','Desempenho','B2');
%  xlswrite(filename,mediaplot,'media');
 
 % mex cec14_func.cpp -DWINDOWS
% f= cec14_func([3.3253000e+000, -1.2835000e+000]', 1) Assim, obtevesse um
% valor

 
% for i=1:30
% eval(['load input_data/shift_data_' num2str(i) '.txt']);
% eval(['O=shift_data_' num2str(i) '(1:10);']);
% f(i)=cec14_func(O',i);i,f(i)
% end