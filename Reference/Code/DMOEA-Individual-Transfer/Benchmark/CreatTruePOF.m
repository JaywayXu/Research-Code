function CreatTruePOF()
clc
clear
close all
warning('off')
con=configure();
T_parameter=con.T_parameter;
functions=con.TestFunctions;

    
    cnt = 100; 
    for func = 1:size(functions,2)
        funcName=functions{func};
        for group = 1:size(T_parameter,1)
            for T = 1:T_parameter(group,3)/T_parameter(group,2)
                    dirPath='./Benchmark/pof/';
                    mkdir(dirPath);
                    filename = [dirPath 'POF-nt' num2str(T_parameter(group,1)) '-taut' num2str(T_parameter(group,2)) '-' funcName '-' num2str(T) '.txt'];
                    t = 1/T_parameter(group,1)*(T-1);
                   
                    switch funcName
                        
                        case 'F5'
                            %% F5
                            H = 0.75*sin(pi*t)+1.25;
                            a = 2*cos(pi*t)+2;
                            b = 2*sin(pi*t)+2;
                            N = 11;
                            PS = zeros(cnt,N);
                            PF = zeros(cnt,2);
                            PS(:,1) = linspace(a,a+1,cnt);
                            for i = 1:cnt
                                for j = 2:N
                                    PS(i,j) = b+1-(abs(PS(i,1)-a)).^(H+j/N);
                                end
                            end
                            for i = 1:cnt
                                [PF(i,:),~] = F5(PS(i,:),t);
                            end

                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'F6'
                            %% F6
                            H = 0.75*sin(pi*t)+1.25;
                            a = 2*cos(1.5*pi*t)*sin(0.5*pi*t)+2;
                            b = 2*cos(1.5*pi*t)*cos(0.5*pi*t)+2;
                            N = 11;
                            PS = zeros(cnt,N);
                            PF = zeros(cnt,2);
                            PS(:,1) = linspace(a,a+1,cnt);
                            for i = 1:cnt
                                for j = 2:N
                                    PS(i,j) = b+1-(abs(PS(i,1)-a)).^(H+j/N);
                                end
                            end
                            for i = 1:cnt
                                [PF(i,:),~] = F6(PS(i,:),t);
                            end

                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'F7'
                            %% F7
                            H = 0.75*sin(pi*t)+1.25;
                            a = 1.7*(1-sin(pi*t))*sin(pi*t)+3.4;
                            b = 1.4*(1-sin(pi*t))*cos(pi*t)+2.1;
                            N = 11;
                            PS = zeros(cnt,N);
                            PF = zeros(cnt,2);
                            PS(:,1) = linspace(a,a+1,cnt);
                            for i = 1:cnt
                                for j = 2:N
                                    PS(i,j) = b+1-(abs(PS(i,1)-a)).^(H+j/N);
                                end
                            end
                            for i = 1:cnt
                                [PF(i,:),~] = F7(PS(i,:),t);
                            end

                            PF = rm_dominated(PF);
                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'F8'
                            %% F8
                            N = 12;
                            PS = zeros(100,N);
                            PF = zeros(cnt,3);
                            G = sin(0.5*pi*t);
                            H = 1.25+0.75*sin(pi*t);
                            [X,Y] = meshgrid(0:.09:1, 0:.09:1);
                            PS = [];
                            for i = 1:size(X,1)
                                PS = [PS
                                    [X(:,i) Y(:,i)]];
                            end
                            for i = 1:size(PS,1)
                                PS(i,3:N) = repmat(((PS(i,1)+PS(i,2))/2)^H+G,1,N-2);
                            end
                            for i = 1:size(PS,1)
                                [PF(i,:),~] = F8(PS(i,:),t);
                            end

                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'F9'
                            %% F9
                            H = 0.75*sin(pi*t)+1.25;
                            a = 2*cos(pi*(t-floor(t)))+2;
                            b = 2*sin(2*pi*(t-floor(t)))+2;
                            N = 11;
                            PS = zeros(cnt,N);
                            PF = zeros(cnt,2);
                            PS(:,1) = linspace(a,a+1,cnt);
                            for i = 1:cnt
                                for j = 2:N
                                    PS(i,j) = b+1-(abs(PS(i,1)-a)).^(H+j/N);
                                end
                            end
                            for i = 1:cnt
                                [PF(i,:),~] = F9(PS(i,:),t);
                            end
%                             plot(PF(:,1),PF(:,2),'.')
%                             hold on
                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'F10'
                            %% F10
                            H = 0.75*sin(pi*t)+1.25;
                            a = 2*cos(pi*t)+2;
                            b = 2*sin(2*pi*t)+2;
                            N = 11;
                            PS = zeros(cnt,N);
                            PF = zeros(cnt,2);
                            PS(:,1) = linspace(a,a+1,cnt);
                            for i = 1:cnt
                                for j = 2:N
                                    PS(i,j) = b+1-(abs(PS(i,1)-a)).^(H+j/N);
                                end
                            end
                            for i = 1:cnt
                                [PF(i,:),~] = F10(PS(i,:),t);
                            end

                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'DF1'
                            %% DF1
                            N = 10;
                            G = abs(sin(pi*t/2));
                            H = 0.75*sin(pi*t/2)+1.25;
                            PS=[];
                            PS(:,1) = linspace(0,1,cnt);
                            PS(:,2:N) = G;                         
                            PF = zeros(cnt,2);      
                            for i = 1:cnt
                                [PF(i,:),~] = DF1(PS(i,:),t);
                            end
                            
          
                            PF = rm_dominated(PF);
                            
                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y           
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'DF2'
                            %% DF2
                            N = 10;
                            PS = zeros(cnt,N);
                            PF = zeros(cnt,2);
                            G = abs(sin(pi*t/2));
                            r=1+floor((N-1)*G);
                            %f1 = X(r);
                            PS(:,r) = linspace(0,1,cnt);
                            for i=1:size(PS,2)
                                if i~=r
                                    PS(:,i) =G;
                                end
                            end
                            for i = 1:cnt
                                [PF(i,:),~] = DF2(PS(i,:),t);
                            end

                            PF = rm_dominated(PF);
                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'DF3'
                        %% DF3
                       
                             N = 10;
                            G = (sin(pi*t/2));
                            H = G+1.5;
                            PS=[];
                            PS(:,1) = linspace(0,1,cnt);
                            for i=2:N
                                PS(:,i) = G+PS(:,1).^H;    
                            end
                                                 
                            PF = zeros(cnt,2);      
                            for i = 1:cnt
                                [PF(i,:),~] = DF3(PS(i,:),t);
                            end
%                             plot(PS(:,1),PS(:,2),'.')
%                             hold on
                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                             
                        case 'DF4'
                            %% DF4
                            N = 10;
                            a = (sin(pi*t/2));
                            b=1+abs(cos(pi*t/2));
                            H=1.5+a;
                            PS = zeros(cnt,N);
                            PF = zeros(cnt,2);
                            PS(:,1) = linspace(a,a+b,cnt);
                            for i=2:N
                                PS(:,i)=a.*PS(:,1).^2./i;
                            end
                            
                            for i = 1:cnt
                                [PF(i,:),~] = DF4(PS(i,:),t);
                            end


                            PF = rm_dominated(PF);
                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'DF5'
                            %% DF5
                            G=(sin(pi*t/2));
                            N = 10;
                            PS = zeros(cnt,N);
                            PF = zeros(cnt,2);
                            PS(:,1) = linspace(0,1,cnt);
                            PS(:,2:N) = G;
                            for i = 1:cnt
                                [PF(i,:),~] = DF5(PS(i,:),t);
                            end

                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'DF6'
                            %% DF6
                            G=(sin(pi*t/2));
                            N = 10;
                            PS = zeros(cnt,N);
                            PF = zeros(cnt,2);
                            PS(:,1) = linspace(0,1,cnt);
                            PS(:,2:N) = G;
                            for i = 1:cnt
                                [PF(i,:),~] = DF6(PS(i,:),t);
                            end

                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'DF7'
                            %% DF7
                            
                            N = 10;
                          
                             a=5*cos(0.5*pi*t);
                            
                            PF = zeros(cnt,2);
                            PS(:,1) = linspace(1,4,cnt);
                            for i = 1:cnt
                                for j = 2:N
                                    PS(i,j) =1/(1+exp(a*(PS(i,1)-0.5))); 
                                end
                            end
                            for i = 1:cnt
                                [PF(i,:),~] = DF7(PS(i,:),t);
                            end

                            PF = rm_dominated(PF);
                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'DF8'
                            %% DF8
                            N = 10;
                            PS(:,1) = linspace(0,1,cnt);
                            G=sin(0.5*pi*t);
                            b=100*G^2;
                            
                            for i = 1:cnt
                                for j = 2:N
                                    PS(i,j) =G*sin(4*pi*PS(i,1))/(1+abs(G));% b+1-(abs(PS(i,1)-a)).^(H+j/N);
                                end
                            end
                            for i = 1:cnt
                                [PF(i,:),~] = DF8(PS(i,:),t);
                            end

                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'DF9'
                            %% DF9
                            N = 10;
                            PS(:,1) = linspace(0,1,cnt);
                            
                            
                            for i = 1:cnt
                                for j = 2:N
                                    PS(i,j) =cos(4*t+PS(i,1)+PS(i,j-1));% b+1-(abs(PS(i,1)-a)).^(H+j/N);
                                end
                            end
                            for i = 1:cnt
                                [PF(i,:),~] = DF9(PS(i,:),t);
                            end

                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'DF10'
                            %% DF10
                            
                            N = 10;
                            G=sin(0.5*pi*t);
                            PF = zeros(cnt,3);
                            [X,Y] = meshgrid(0:.07:1, 0:.07:1);
                            PS = [];
                            for i = 1:size(X,1)
                                PS = [PS
                                    [X(:,i) Y(:,i)]];
                            end
                            for i = 1:size(PS,1)
                                for j = 3:N
                                    PS(i,j) = sin(2*pi*(PS(i,1)+PS(i,2)))/(1+abs(G))  ;%b+1-(abs(PS(i,1)-a)).^(H+j/N);
                                end
                            end
                            for i = 1:size(PS,1)
                                [PF(i,:),~] = DF10(PS(i,:),t);
                            end

                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'DF11'
                            %% DF11
                           N = 10;
                            G=abs(sin(0.5*pi*t));
                            PF = zeros(cnt,3);
                            [X,Y] = meshgrid(0:.08:1, 0:.08:1);
                            PS = [];
                            for i = 1:size(X,1)
                                PS = [PS
                                    [X(:,i) Y(:,i)]];
                            end
                            for i = 1:size(PS,1)
                                for j = 3:N
                                    PS(i,j) = 0.5*G*PS(i,1) ;%b+1-(abs(PS(i,1)-a)).^(H+j/N);
                                end
                            end
                             for i = 1:size(PS,1)
                                [PF(i,:),~] = DF11(PS(i,:),t);
                            end

                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'DF12'
                            %% DF12
                            N = 10;
                            G=abs(sin(0.5*pi*t));
                            PF = zeros(cnt,3);
                            [X,Y] = meshgrid(0:.08:1, 0:.08:1);
                            PS = [];
                            for i = 1:size(X,1)
                                PS = [PS
                                    [X(:,i) Y(:,i)]];
                            end
                            for i = 1:size(PS,1)
                                for j = 3:N
                                    PS(i,j) = sin(t*PS(i,1)) ;%b+1-(abs(PS(i,1)-a)).^(H+j/N);
                                end
                            end
                             for i = 1:size(PS,1)
                                [PF(i,:),~] = DF12(PS(i,:),t);
                            end

                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'DF13'
                            %% DF13
                            
                           N = 10;
                            G=(sin(0.5*pi*t));
                            PF = zeros(cnt,3);
                            [X,Y] = meshgrid(0:.088:1, 0:.088:1);
                            PS = [];
                            for i = 1:size(X,1)
                                PS = [PS
                                    [X(:,i) Y(:,i)]];
                            end
                            for i = 1:size(PS,1)
                                for j = 3:N
                                    PS(i,j) = G ;%b+1-(abs(PS(i,1)-a)).^(H+j/N);
                                end
                            end
                            for i = 1:size(PS,1)
                                [PF(i,:),~] = DF13(PS(i,:),t);
                            end

                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        case 'DF14'
                            %% DF14
                            N = 10;
                            G=(sin(0.5*pi*t));
                            PF = zeros(cnt,3);
                            [X,Y] = meshgrid(0:.077:1, 0:.077:1);
                            PS = [];
                            for i = 1:size(X,1)
                                PS = [PS
                                    [X(:,i) Y(:,i)]];
                            end
                            for i = 1:size(PS,1)
                                for j = 3:N
                                    PS(i,j) = G ;%b+1-(abs(PS(i,1)-a)).^(H+j/N);
                                end
                            end
                            for i = 1:size(PS,1)
                                [PF(i,:),~] = DF14(PS(i,:),t);
                            end

                            [X,Y] = size(PF);
                            fid = fopen(filename,'w');
                            for i = 1:X
                               for j = 1:Y
                                   fprintf(fid,'%f\t',PF(i,j));
                               end
                               fprintf(fid,'\r\n');
                            end
                            fclose(fid);
                        
                    end
                %end
            end
        end
    end


end



function [F,V] = F5(X,t)
%% F5
    N = 11;
    Fn = 2;
    H = 0.75*sin(pi*t)+1.25;
    a = 2*cos(pi*t)+2;
    b = 2*sin(pi*t)+2;
    Y(2:N) = X(2:N)-b-1+(abs(X(1)-a)).^(H+(2:N)/N);
    f1 = (abs(X(1)-a))^H+sum(Y(1:2:N).^2);
    f2 = (abs(X(1)-a-1))^H+sum((Y(2:2:N).^2));
    F = [f1
        f2];
    V = 0.0;
end

function [F,V] = F6(X,t)
%% F6
    N = 11;
    Fn = 2;
    H = 0.75*sin(pi*t)+1.25;
    a = 2*cos(1.5*pi*t)*sin(0.5*pi*t)+2;
    b = 2*cos(1.5*pi*t)*cos(0.5*pi*t)+2;
    Y(2:N) = X(2:N)-b-1+abs(X(1)-a).^(H+(2:N)/N);
    f1 = abs(X(1)-a)^H+sum(Y(1:2:end).^2);
    f2 = abs(X(1)-a-1)^H+sum((Y(2:2:end).^2));
    F = [f1
        f2];
    V = 0.0;
end

function [F,V] = F7(X,t)
%% F7
    N = 11;
    Fn = 2;
    H = 0.75*sin(pi*t)+1.25;
    a = 1.7*(1-sin(pi*t))*sin(pi*t)+3.4;
    b = 1.4*(1-sin(pi*t))*cos(pi*t)+2.1;
    Y(2:N) = X(2:N)-b-1+abs(X(1)-a).^(H+(2:N)/N);
    f1 = abs(X(1)-a)^H+sum(Y(1:2:end).^2);
    f2 = abs(X(1)-a-1)^H+sum((Y(2:2:end).^2));
    F = [f1
        f2];
    V = 0.0;
end

function [F,V] = F8(X,t)
%% F8
    N = 12;
    Fn = 3;
    G = sin(0.5*pi*t);
    H = 1.25+0.75*sin(pi*t);
    g = sum((X(3:end)-((X(1)+X(2))/2)^H-G).^2);
    f1 = (1+g)*cos(0.5*pi*X(1))*cos(0.5*pi*X(2));
    f2 = (1+g)*cos(0.5*pi*X(1))*sin(0.5*pi*X(2));
    f3 = (1+g)*sin(0.5*pi*X(1));
    F = [f1
        f2
        f3];
    V = 0.0;
end

function [F,V] = F9(X,t)
%% F9
%     X = X';
    N = 11;
    Fn = 2;
%     X = X*5;
    H = 0.75*sin(pi*t)+1.25;
    a = 2*cos(pi*(t-floor(t)))+2;
    b = 2*sin(2*pi*(t-floor(t)))+2;
    Y(2:N) = X(2:N)-b-1+abs(X(1)-a).^(H+(2:N)/N);
    f1 = abs(X(1)-a)^H+sum(Y(1:2:end).^2);
    f2 = abs(X(1)-a-1)^H+sum((Y(2:2:end).^2));
    F = [f1
        f2];
    V = 0.0;
end

function [F,V] = F10(X,t)
%% F10
%caculate T through t and the T_parameter
%因为在实验中的所有配置的nt只为10，因此只需要用t乘以10就知道当时的T
    T = round(t*10);
    N = 11;
    Fn = 2;
    H = 0.75*sin(pi*t)+1.25;
    a = 2*cos(pi*t)+2;
    b = 2*sin(2*pi*t)+2;
    if mod(T,2) == 0
        Y(2:N) = X(2:N)-b-1+abs(X(1)-a).^(H+(2:N)/N);
    else
        Y(2:N) = X(2:N)-b+abs(X(1)-a).^(H+(2:N)/N);
    end
    f1 = abs(X(1)-a)^H+sum(Y(1:2:end).^2);
    f2 = abs(X(1)-a-1)^H+sum((Y(2:2:end).^2));
    F = [f1
        f2];
    V = 0.0;
end



%% test functions
function [F,V] = DF1(X,t)
    %% DF1
    N = 10;
    Fn = 2;
    H = 0.75*sin(pi*t/2)+1.25;
    G = abs(sin(pi*t/2));
    f1 = X(1);
    g = 1+sum((X(2:end)-G).^2);
    h = 1-(f1/g)^H;    
    F = [f1
        g*h];    
    V = 0.0;
    
end



function [F,V] = DF2(X,t)
    %% DF2
    n = 10;
    Fn = 2;
    G = abs(sin(pi*t/2));
    r=1+floor((n-1)*G);
    f1 = X(r);
    g=1;
    for i=1:n
        if i==r
            continue
        else
            g=g+(X(i)-G)^2;
        end
    end
    h = 1-sqrt(f1/g);
    F = [f1
        g*h];
    V = 0.0;
end

function [F,V]  = DF3(X,t)
%% DF3
    N = 10;
    M = 2;
    f1=X(1);
    G = (sin(pi*t/2));
    H=1.5+G;
    x1H=X(1)^H;
    g=1;
    for i=2:N
        g=g+(X(i)-G-x1H)^2;
    end
    h = 1-(f1/g)^H;
    F = [f1
        g*h];
    V = 0.0;
end

function [F,V]  = DF4(X,t)
%% DF4
    N = 10;
    M = 2;
    g=1;
    a = (sin(pi*t/2));
    for i=2:N
        g=g+(X(i)-(a*X(1)^2/i))^2;
    end
    b=1+abs(cos(pi*t/2));
    
    H=1.5+a;
    f1=g*abs(X(1)-a)^H;
    f2=g*abs(X(1)-a-b)^H;
    F = [f1
        f2];
    V = 0.0;
end

function [F,V]  = DF5(X,t)
%% DF5
    N = 10;
    M = 2;
    G=(sin(pi*t/2));
    g=1;
    for i=2:N
        g=g+(X(i)-G)^2;
    end
    w=floor(10*G);
    f1=g*(X(1)+0.02*sin(w*pi*X(1)));
    f2=g*(1-X(1)+0.02*sin(w*pi*X(1)));
    F = [f1
        f2];
    V = 0.0;
end

function [F,V]  = DF6(X,t)
%% DF6
    N = 10;
    M = 2;
    G=(sin(pi*t/2));
    g=1;
    a=0.2+2.8*abs(G);
    Y=X-G;
    for i=2:N
        g=g+(abs(G)*Y(i)^2-10*cos(2*pi*Y(i))+10);
    end
    f1=g*(X(1)+0.1*sin(3*pi*X(1)))^a;
    f2=g*(1-X(1)+0.1*sin(3*pi*X(1)))^a;
    F = [f1
        f2];
    V = 0.0;
end




function [F,V]  = DF7(x,t)
%% DF7
    N = 10;
    M = 2;
    a=5*cos(0.5*pi*t);
        tmp=1/(1+exp(a*(x(1)-2.5)));
        g=1+sum(power(x(2:end)-tmp,2));
        f1=g*(1+t)/x(1);
        f2=g*x(1)/(1+t) ;  
        
  
    F = [f1
        f2];
    V = 0.0;
end

function [F,V]  = DF8(x,t)
%% DF8
    N = 10;
    M = 2;
    G=sin(0.5*pi*t);
    a=2.25+2*cos(2*pi*t);
    b=100*G^2;
    tmp=G*sin(power(4*pi*x(1),b))/(1+abs(G));
    g=1+sum((x(2:end)-tmp).^2);
    f1=g*(x(1)+0.1*sin(3*pi*x(1)));
    f2=g*power(1-x(1)+0.1*sin(3*pi*x(1)),a);   
    F = [f1
        f2];
    V = 0.0;
end


function [F,V]  = DF9(x,t)
%% DF9
    n=10;
    N=1+floor(10*abs(sin(0.5*pi*t)));
    g=1;
    for i=2:n
        tmp=x(i)-cos(4*t+x(1)+x(i));
        g=g+tmp^2;
    end
        f1=g*(x(1)+max(0, (0.1+0.5/N)*sin(2*N*pi*x(1))));
        f2=g*(1-x(1)+max(0, (0.1+0.5/N)*sin(2*N*pi*x(1))))  ; 
    F = [f1
        f2];
    V = 0.0;
end

function [F,V]  = DF10(x,t)
%% DF10
    n=10;
    G=sin(0.5*pi*t);
        H=2.25+2*cos(0.5*pi*t);
        tmp=sin(2*pi*(x(1)+x(2)))/(1+abs(G));
        g=1+sum((x(3:end)-tmp).^2);
        f0=g*power(sin(0.5*pi*x(1)),H);
        f1=g*power(sin(0.5*pi*x(2)),H)*power(cos(0.5*pi*x(1)),H);
        f2=g*power(cos(0.5*pi*x(2)),H)*power(cos(0.5*pi*x(1)),H);
    F = [f0
        f1
        f2];
    V = 0.0;
end

function [F,V]  = DF11(x,t)
%% DF11
    G=abs(sin(0.5*pi*t));
        g=1+G+sum((x(3:end)-0.5*G*x(1)).^2);
       
        y1=pi*G/6.0+(pi/2-pi*G/3.0)*x(1);
        y2=pi*G/6.0+(pi/2-pi*G/3.0)*x(2);
        f0=g*sin(y1) ;
        f1=g*sin(y2)*cos(y1);
        f2=g*cos(y2)*cos(y1);
    F = [f0
        f1
        f2];
    V = 0.0;
end

function [F,V]  = DF12(x,t)
%% DF12
    k=10*sin(pi*t);
        tmp1=x(3:end)-sin(t*x(1));
        tmp2=abs(sin(floor(k*(2*x(1)-1))*pi/2)*sin(floor(k*(2*x(2)-1))*pi/2));
        g=1+sum(tmp1.^2)+tmp2;
        f0=g*cos(0.5*pi*x(2))*cos(0.5*pi*x(1));
        f1=g*sin(0.5*pi*x(2))*cos(0.5*pi*x(1));
        f2=g*sin(0.5*pi*x(2));
    F = [f0
        f1
        f2];
    V = 0.0;
end

function [F,V]  = DF13(x,t)
%% DF13
   G=sin(0.5*pi*t);
        p=floor(6*G);
        g=1+sum((x(3:end)-G).^2);
        f0=g*cos(0.5*pi*x(1))^2;
        f1=g*cos(0.5*pi*x(2))^2;
        f2=g*sin(0.5*pi*x(1))^2+sin(0.5*pi*x(1))*cos(p*pi*x(1))^2+sin(0.5*pi*x(2))^2+sin(0.5*pi*x(2))*cos(p*pi*x(2))^2;
    F = [f0
        f1
        f2];
    V = 0.0;
end

function [F,V]  = DF14(x,t)
%% DF14
    n=10;
    G=sin(0.5*pi*t);
        g=1+sum((x(3:end)-G).^2);
        y=0.5+G*(x(1)-0.5);
        f0=g*(1-y+0.05*sin(6*pi*y));
        f1=g*(1-x(2)+0.05*sin(6*pi*x(2)))*(y+0.05*sin(6*pi*y));
        f2=g*(x(2)+0.05*sin(6*pi*x(2)))*(y+0.05*sin(6*pi*y));
    F = [f0
        f1
        f2];
    V = 0.0;
end
