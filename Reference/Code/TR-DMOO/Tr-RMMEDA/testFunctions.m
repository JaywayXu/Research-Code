classdef testFunctions
    methods(Static)
        %% Benchmark functions
        function [F,V]  = FDA4(X,t)
            N = 12;
            M = 3;
            G = abs(sin(pi*t/2));
            g = sum((X(M:N) - G).^2);
            F = [(1+g)*prod(cos(X(1:M-1)*pi/2))
                (1+g)*prod(cos(X(1:M-2)*pi/2))*sin(X(M-1)*pi/2)
                (1+g)*sin(X(1)*pi/2)];
            V = 0.0;
            
        end
        
        function [F,V] = FDA5(X,t)
            N = 12;
            M = 3;
            G = abs(sin(pi*t/2));
            g = G+sum((X(M:N)-G).^2);
            F = 1+100*sin(pi*t/2)^4;
            y1 = X(1:M-1).^F;
            y2 = X(1:M-2).^F;
            y3 = X(M-1).^F;
            y4 = X(1).^F;
            
            F = [(1+g)*prod(cos(y1.*pi/2))
                (1+g)*prod(cos(y2*pi/2))*sin(y3*pi/2)
                (1+g)*sin(y4*pi/2)];
            V = 0.0;
        end
        
        function [F,V] = FDA5_iso(X,t)
            N = 12;
            M = 3;
            G = abs(sin(pi*t/2));
            B = .001;
            C = .05;
            g = G+sum((min(0, floor(X(M:N)-B)).*(G*(B-X(M:N))/B-min(0,floor(C-X(M:N)))*(1-G).*(X(M:N)-C)/(1-C))).^2);
            K = 1+100*sin(pi*t/2)^4;
            y1 = X(1:M-1).^K;
            y2 = X(1:M-2).^K;
            y3 = X(M-1).^K;
            y4 = X(1).^K;
            F = [(1+g)*prod(cos(y1*pi/2))
                (1+g)*prod(cos(y2*pi/2))*sin(y3*pi/2)
                (1+g)*sin(y4*pi/2)];
            V = 0.0;
            
        end
        
        function [F,V] = FDA5_dec(X,t)
            N = 12;
            Fn = 3;
            M = 3;
            
            G = abs(sin(pi*t/2));
            B = .001;
            C = .05;
            g = G+sum(((floor(X(M:N)-G+B)*(1-C+(G-B)/B)/(G-B)+1/B+floor(G+B-X(M:N))*(1-C+(1-G-B)/B)/(1-G-B)).*(abs(X(M:N)-G)-B)+1).^2);
            K = 1+100*sin(pi*t/2)^4;
            y1 = X(1:M-1).^K;
            y2 = X(1:M-2).^K;
            y3 = X(M-1).^K;
            y4 = X(1).^K;
            
            F = [(1+g)*prod(cos(y1*pi/2))
                (1+g)*prod(cos(y2*pi/2))*sin(y3*pi/2)
                (1+g)*sin(y4*pi/2)];
            V = 0.0;
        end
        
        function [F,V] = DIMP2(X,t)
            % [-2,2]
            N = 10;
            Fn = 2;
            G = sin((pi*t/2+2*pi*(2:N)/(N+1)).^2);
            f = X(1);
            g = 1+2*(N-1)+sum((X(2:end)-G).^2-2*cos(3*pi*(X(2:end)-G)));
            h = 1-sqrt(f/g);
            
            F = [f
                g*h];
            V = 0.0;
        end
        
        function [F,V] = dMOP2(X,t)
            N = 10;
            Fn = 2;
            
            H = 0.75*sin(pi*t/2)+1.25;
            G = sin(pi*t/2);
            f = X(1);
            g = 1+9*sum((X(2:end)-G).^2);
            h = 1-(f/g)^H;
            F = [f
                g*h];
            V = 0.0;
            
        end
        
        function [F,V] = dMOP2_iso(X,t)
            N = 10;
            Fn = 2;
            
            H = 0.75*sin(pi*t/2)+1.25;
            B = .001;
            C = .05;
            G = sin(pi*t/2);
            f = X(1);
            g = 1+9*sum((min(0, floor(X(2:end)-B)).*(G*(B-X(2:end))/B-min(0,floor(C-X(2:end)))*(1-G).*(X(2:end)-C)/(1-C))).^2);
            h = 1-(f/g)^H;
            
            F = [f
                g*h];
            V = 0.0;
            
        end
        
        function [F,V] = dMOP2_dec(X,t)
            n = 10;
            Fn = 2;
            H = 0.75*sin(pi*t/2)+1.25;
            B = .001;
            C = .05;
            G = sin(pi*t/2);
            f = X(1);
            g = 1+9*sum((((floor(X(2:end)-G+B)*(1-C+(G-B)/B)/(G-B)+1/B+floor(G+B-X(2:end))*(1-C+(1-G-B)/B)/(1-G-B)).*(abs(X(2:end)-G)-B)+1)-G).^2);
            h = 1-(f/g)^H;
            F = [f
                g*h];
            V = 0.0;
        end
        
        function [F,V] = dMOP3(X,t)
            n = 10;
            Fn = 2;
            
            H = 0.75*sin(pi*t/2)+1.25;
            G = sin(pi*t/2);
            f = X(1);
            g = 1+9*sum((X(2:end)-G).^2);
            h = 1-sqrt(f/g);
            
            F = [f
                g*h];
            V = 0.0;
        end
        
        function [F,V] = HE2(X,t)
            N = 30;
            Fn = 2;
            
            H = 0.75*sin(pi*t/2)+1.25;
            f = X(1);
            g = 1+9*sum(X(2:end))/(N-1);
            h = 1-sqrt(f/g)^H-(f/g)^H*sin(10*pi*f);
            F = [f
                g*h];
            V = 0.0;
        end
        
        function [F,V] = HE7(X,t)
            N = 10;
            Fn = 2;
            
            H = 0.75*sin(pi*t/2)+1.25;
            f = X(1)+2/numel(3:2:N)*sum((X(3:2:N)-1-(0.3*X(1)^2*cos(24*pi*X(1)+4*(3:2:N)*pi/N)+0.6*X(1)).*cos(6*pi*X(1)+(3:2:N)*pi/N)).^2);
            g = 2-sqrt(X(1))+2/numel(2:2:N)*sum((X(2:2:N)-1-(0.3*X(1)^2*cos(24*pi*X(1)+4*(2:2:N)*pi/N)+0.6*X(1)).*sin(6*pi*X(1)+(2:2:N)*pi/N)).^2);
            h = 1-(f/g)^H;
            
            F = [f
                g*h];
            V = 0.0;
        end
        
        function [F,V] = HE9(X,t)
            n = 10;
            Fn = 2;
            
            H = 0.75*sin(pi*t/2)+1.25;
            f = X(1)+2/numel(3:2:n)*sum((X(3:2:n)-sin(6*pi*X(1)+(3:2:n)*pi/n)).^2);
            g = 2-X(1)^2+2/numel(2:2:n)*sum((X(2:2:n)-sin(6*pi*X(1)+(2:2:n)*pi/n)).^2);
            h = 1-(f/g)^H;
            
            F = [f
                g*h];
            V = 0.0;
        end
    end
end