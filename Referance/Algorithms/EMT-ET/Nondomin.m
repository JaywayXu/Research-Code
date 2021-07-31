function Nondomin(Problem, NVARS, OBJS1, LBOUND1, UBOUND1, LBOUND2, UBOUND2, population1, population2, ini_pop)

    for run = 1:10
        rand('state', sum(100 * clock))
        proc = 0.9;
        disc = 20;
        prom = 1;
        dism = 15;
        T1 = 1;
        T2 = 2;
        population1 = update_population(population1, OBJS1, Problem, NVARS, T1, ini_pop);
        population2 = update_population(population2, OBJS1, Problem, NVARS, T2, ini_pop);
        generation = 0;
        G = 10;
        d = [];

        while generation < 500
            str = ['Problem : ' num2str(Problem) ', run : ' num2str(run) ', generation : ' num2str(generation)];
            disp(str);
            shareindividuals1 = struct('x', [], 'f', [], 'rank', [], 'sign', []);
            shareindividuals2 = struct('x', [], 'f', [], 'rank', [], 'sign', []);
            shareindividuals1.x = population1.x(1:G, :);
            shareindividuals1.f = population1.f(1:G, :);
            shareindividuals1.rank = population1.rank(1:G, :);
            shareindividuals1.sign = population1.sign(1:G, :);
            shareindividuals2.x = population2.x(1:G, :);
            shareindividuals2.f = population2.f(1:G, :);
            shareindividuals2.rank = population2.rank(1:G, :);
            shareindividuals2.sign = population2.sign(1:G, :);
            %     [~,shareindividuals1] = designation(population2,population1,G,1,LBOUND1,UBOUND1,LBOUND2,UBOUND2);
            %     [~,shareindividuals2] = designation(population1,population2,G,2,LBOUND1,UBOUND1,LBOUND2,UBOUND2);
            %     cr1 = rand(G,1);
            %     cr2 = rand(G,1);
            %     shareindividuals1.x(cr1<0.5,:) = (2*rand(1))*shareindividuals1.x(cr1<0.5,:);
            %     shareindividuals2.x(cr2<0.5,:) = (2*rand(1))*shareindividuals2.x(cr2<0.5,:);
            for j = 1:NVARS(1)

                for i = 1:G

                    if shareindividuals2.x(i, j) < LBOUND1(j)
                        shareindividuals2.x(i, j) = LBOUND1(j);
                    end

                    if shareindividuals2.x(i, j) > UBOUND1(j)
                        shareindividuals2.x(i, j) = UBOUND1(j);
                    end

                end

            end

            for j = 1:NVARS(2)

                for i = 1:G

                    if shareindividuals1.x(i, j) < LBOUND2(j)
                        shareindividuals1.x(i, j) = LBOUND2(j);
                    end

                    if shareindividuals1.x(i, j) > UBOUND2(j)
                        shareindividuals1.x(i, j) = UBOUND2(j);
                    end

                end

            end

            population1.sign = zeros(ini_pop, 1);
            population2.sign = zeros(ini_pop, 1);
            population1.x = [population1.x; shareindividuals2.x(:, 1:NVARS(1))];
            population1.rank = [population1.rank; ones(G, 1)];
            population1.sign = [population1.sign; shareindividuals2.sign];
            population2.x = [population2.x; shareindividuals1.x(:, 1:NVARS(2))];
            population2.rank = [population2.rank; ones(G, 1)];
            population2.sign = [population2.sign; shareindividuals1.sign];
            offspring1 = generate(population1, ini_pop - G, proc, disc, prom, dism, Problem, T1, LBOUND1, UBOUND1);
            offspring2 = generate(population2, ini_pop - G, proc, disc, prom, dism, Problem, T2, LBOUND2, UBOUND2);
            mixpopulation1 = struct('x', [], 'f', [], 'rank', [], 'sign', []);
            mixpopulation2 = struct('x', [], 'f', [], 'rank', [], 'sign', []);
            mixpopulation1.x = [population1.x; offspring1.x];
            mixpopulation1.f = [population1.f; offspring1.f];
            mixpopulation1.rank = [population1.rank; offspring1.rank];
            mixpopulation1.sign = [population1.sign; offspring1.sign];
            mixpopulation2.x = [population2.x; offspring2.x];
            mixpopulation2.f = [population2.f; offspring2.f];
            mixpopulation2.rank = [population2.rank; offspring2.rank];
            mixpopulation2.sign = [population2.sign; offspring2.sign];
            population1 = update_population(mixpopulation1, OBJS1, Problem, NVARS, T1, ini_pop);
            population2 = update_population(mixpopulation2, OBJS1, Problem, NVARS, T2, ini_pop);
            generation = generation + 1;
            %     d = [d;sum(abs(population1.x(1,2:end)-ones(1,9)))];
            %     if generation == 499
            %         pause(5)
            %     end
            %     subplot(2,1,1)
            %     if Problem <8
            %         plot(population1.f(:,1),population1.f(:,2),'b*');
            %     else
            %         plot3(population1.f(:,1),population1.f(:,2),population1.f(:,3),'b*');
            %     end
            %     %hold on
            %     title(['Problem: ',num2str(Problem),' run: ',num2str(run)]);
            %     subplot(2,1,2)
            %     plot(population2.f(:,1),population2.f(:,2),'b*');
            %     pause(0.005)
        end

        load circle
        load concave
        load convex
        load sp

        if Problem == 1 && run == 1
            CIHS_igd1_non = zeros(10, 1)
            CIHS_igd2_non = zeros(10, 1)
            CIMS_igd1_non = zeros(10, 1)
            CIMS_igd2_non = zeros(10, 1)
            CILS_igd1_non = zeros(10, 1)
            CILS_igd2_non = zeros(10, 1)
            PIHS_igd1_non = zeros(10, 1)
            PIHS_igd2_non = zeros(10, 1)
            PIMS_igd1_non = zeros(10, 1)
            PIMS_igd2_non = zeros(10, 1)
            PILS_igd1_non = zeros(10, 1)
            PILS_igd2_non = zeros(10, 1)
            NIHS_igd1_non = zeros(10, 1)
            NIHS_igd2_non = zeros(10, 1)
            NIMS_igd1_non = zeros(10, 1)
            NIMS_igd2_non = zeros(10, 1)
            NILS_igd1_non = zeros(10, 1)
            NILS_igd2_non = zeros(10, 1)
        end

        if Problem == 1
            CIHS_igd1_non(run) = igd(Problem, population1.f(population1.rank == 1, :), circle);
            CIHS_igd2_non(run) = igd(Problem, population2.f(population2.rank == 1, :), concave);

            if run == 10
                save CIHS_igd1_non
                save CIHS_igd2_non
            end

        end

        if Problem == 2
            CIMS_igd1_non(run) = igd(Problem, population1.f(population1.rank == 1, :), concave);
            CIMS_igd2_non(run) = igd(Problem, population2.f(population2.rank == 1, :), circle);

            if run == 10
                save CIMS_igd1_non
                save CIMS_igd2_non
            end

        end

        if Problem == 3
            CILS_igd1_non(run) = igd(Problem, population1.f(population1.rank == 1, :), circle);
            CILS_igd2_non(run) = igd(Problem, population2.f(population2.rank == 1, :), convex);

            if run == 10
                save CILS_igd1_non
                save CILS_igd2_non
            end

        end

        if Problem == 4
            PIHS_igd1_non(run) = igd(Problem, population1.f(population1.rank == 1, :), convex);
            PIHS_igd2_non(run) = igd(Problem, population2.f(population2.rank == 1, :), convex);

            if run == 10
                save PIHS_igd1_non
                save PIHS_igd2_non
            end

        end

        if Problem == 5
            PIMS_igd1_non(run) = igd(Problem, population1.f(population1.rank == 1, :), circle);
            PIMS_igd2_non(run) = igd(Problem, population2.f(population2.rank == 1, :), concave);

            if run == 10
                save PIMS_igd1_non
                save PIMS_igd2_non
            end

        end

        if Problem == 6
            PILS_igd1_non(run) = igd(Problem, population1.f(population1.rank == 1, :), circle);
            PILS_igd2_non(run) = igd(Problem, population2.f(population2.rank == 1, :), circle);

            if run == 10
                save PILS_igd1_non
                save PILS_igd2_non
            end

        end

        if Problem == 7
            NIHS_igd1_non(run) = igd(Problem, population1.f(population1.rank == 1, :), circle);
            NIHS_igd2_non(run) = igd(Problem, population2.f(population2.rank == 1, :), convex);

            if run == 10
                save NIHS_igd1_non
                save NIHS_igd2_non
            end

        end

        if Problem == 8
            NIMS_igd1_non(run) = igd(Problem, population1.f(population1.rank == 1, :), sp);
            NIMS_igd2_non(run) = igd(Problem, population2.f(population2.rank == 1, :), concave);

            if run == 10
                save NIMS_igd1_non
                save NIMS_igd2_non
            end

        end

        if Problem == 9
            NILS_igd1_non(run) = igd(Problem, population1.f(population1.rank == 1, :), sp);
            NILS_igd2_non(run) = igd(Problem, population2.f(population2.rank == 1, :), concave);

            if run == 10
                save NILS_igd1_non
                save NILS_igd2_non
            end

        end

        % %% IGD
        % if Problem == 1
        %     CIHS_igd1(run) = igd(Problem,population1.f(population1.rank==1,:),circle);
        %     CIHS_igd2(run) = igd(Problem,population2.f(population2.rank==1,:),concave);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\CIHS_igd1.txt','a');
        %     fprintf(fp,'%f\r\n',CIHS_igd1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\CIHS_igd2.txt','a');
        %     fprintf(fp,'%f\r\n',CIHS_igd2(run));
        %     fclose(fp);
        % %         if run == 20
        % %             save CIHS_igd1
        % %             save CIHS_igd2
        % %         end
        % end
        % if Problem == 2
        %     CIMS_igd1(run) = igd(Problem,population1.f(population1.rank==1,:),concave);
        %     CIMS_igd2(run) = igd(Problem,population2.f(population2.rank==1,:),circle);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\CIMS_igd1.txt','a');
        %     fprintf(fp,'%f\r\n',CIMS_igd1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\CIMS_igd2.txt','a');
        %     fprintf(fp,'%f\r\n',CIMS_igd2(run));
        %     fclose(fp);
        % %         if run == 20
        % %             save CIMS_igd1
        % %             save CIMS_igd2
        % %         end
        % end
        % if Problem == 3
        %     CILS_igd1(run) = igd(Problem,population1.f(population1.rank==1,:),circle);
        %     CILS_igd2(run) = igd(Problem,population2.f(population2.rank==1,:),convex);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\CILS_igd1.txt','a');
        %     fprintf(fp,'%f\r\n',CILS_igd1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\CILS_igd2.txt','a');
        %     fprintf(fp,'%f\r\n',CILS_igd2(run));
        %     fclose(fp);
        % %         if run == 20
        % %             save CILS_igd1
        % %             save CILS_igd2
        % %         end
        % end
        % if Problem == 4
        %     PIHS_igd1(run) = igd(Problem,population1.f(population1.rank==1,:),convex);
        %     PIHS_igd2(run) = igd(Problem,population2.f(population2.rank==1,:),convex);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\PIHS_igd1.txt','a');
        %     fprintf(fp,'%f\r\n',PIHS_igd1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\PIHS_igd2.txt','a');
        %     fprintf(fp,'%f\r\n',PIHS_igd2(run));
        %     fclose(fp);
        %     %     if run == 20
        %     %         save PIHS_igd1
        %     %         save PIHS_igd2
        %     %     end
        % end
        % if Problem == 5
        %     PIMS_igd1(run) = igd(Problem,population1.f(population1.rank==1,:),circle);
        %     PIMS_igd2(run) = igd(Problem,population2.f(population2.rank==1,:),concave);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\PIMS_igd1.txt','a');
        %     fprintf(fp,'%f\r\n',PIMS_igd1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\PIMS_igd2.txt','a');
        %     fprintf(fp,'%f\r\n',PIMS_igd2(run));
        %     fclose(fp);
        %     %     if run == 20
        %     %         save PIMS_igd1
        %     %         save PIMS_igd2
        %     %     end
        % end
        % if Problem == 6
        %     PILS_igd1(run) = igd(Problem,population1.f(population1.rank==1,:),circle);
        %     PILS_igd2(run) = igd(Problem,population2.f(population2.rank==1,:),circle);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\PILS_igd1.txt','a');
        %     fprintf(fp,'%f\r\n',PILS_igd1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\PILS_igd2.txt','a');
        %     fprintf(fp,'%f\r\n',PILS_igd2(run));
        %     fclose(fp);
        %     %     if run == 20
        %     %         save PILS_igd1
        %     %         save PILS_igd2
        %     %     end
        % end
        % if Problem == 7
        %     NIHS_igd1(run) = igd(Problem,population1.f(population1.rank==1,:),circle);
        %     NIHS_igd2(run) = igd(Problem,population2.f(population2.rank==1,:),convex);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\NIHS_igd1.txt','a');
        %     fprintf(fp,'%f\r\n',NIHS_igd1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\NIHS_igd2.txt','a');
        %     fprintf(fp,'%f\r\n',NIHS_igd2(run));
        %     fclose(fp);
        %     %     if run == 20
        %     %         save NIHS_igd1
        %     %         save NIHS_igd2
        %     %     end
        % end
        % if Problem == 8
        %     NIMS_igd1(run) = igd(Problem,population1.f(population1.rank==1,:),sp);
        %     NIMS_igd2(run) = igd(Problem,population2.f(population2.rank==1,:),concave);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\NIMS_igd1.txt','a');
        %     fprintf(fp,'%f\r\n',NIMS_igd1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\NIMS_igd2.txt','a');
        %     fprintf(fp,'%f\r\n',NIMS_igd2(run));
        %     fclose(fp);
        %     %     if run == 20
        %     %         save NIMS_igd1
        %     %         save NIMS_igd2
        %     %     end
        % end
        % if Problem == 9
        %     NILS_igd1(run) = igd(Problem,population1.f(population1.rank==1,:),sp);
        %     NILS_igd2(run) = igd(Problem,population2.f(population2.rank==1,:),concave);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\NILS_igd1.txt','a');
        %     fprintf(fp,'%f\r\n',NILS_igd1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\igd\NILS_igd2.txt','a');
        %     fprintf(fp,'%f\r\n',NILS_igd2(run));
        %     fclose(fp);
        %     %     if run == 20
        %     %         save NILS_igd1
        %     %         save NILS_igd2
        %     %     end
        % end
        % HV
        % %% HV
        % if Problem == 1
        %     CIHS_hv1(run) = HV(Problem,population1.f(population1.rank==1,:),circle);
        %     CIHS_hv2(run) = HV(Problem,population2.f(population2.rank==1,:),concave);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\CIHS_hv1.txt','a');
        %     fprintf(fp,'%f\r\n',CIHS_hv1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\CIHS_hv2.txt','a');
        %     fprintf(fp,'%f\r\n',CIHS_hv2(run));
        %     fclose(fp);
        %     %         if run == 20
        %     %             save CIHS_igd1
        %     %             save CIHS_igd2
        %     %         end
        % end
        % if Problem == 2
        %     CIMS_hv1(run) = HV(Problem,population1.f(population1.rank==1,:),concave);
        %     CIMS_hv2(run) = HV(Problem,population2.f(population2.rank==1,:),circle);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\CIMS_hv1.txt','a');
        %     fprintf(fp,'%f\r\n',CIMS_hv1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\CIMS_hv2.txt','a');
        %     fprintf(fp,'%f\r\n',CIMS_hv2(run));
        %     fclose(fp);
        %     %         if run == 20
        %     %             save CIMS_igd1
        %     %             save CIMS_igd2
        %     %         end
        % end
        % if Problem == 3
        %     CILS_hv1(run) = HV(Problem,population1.f(population1.rank==1,:),circle);
        %     CILS_hv2(run) = HV(Problem,population2.f(population2.rank==1,:),convex);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\CILS_hv1.txt','a');
        %     fprintf(fp,'%f\r\n',CILS_hv1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\CILS_hv2.txt','a');
        %     fprintf(fp,'%f\r\n',CILS_hv2(run));
        %     fclose(fp);
        %     %         if run == 20
        %     %             save CILS_igd1
        %     %             save CILS_igd2
        %     %         end
        % end
        % if Problem == 4
        %     PIHS_hv1(run) = HV(Problem,population1.f(population1.rank==1,:),convex);
        %     PIHS_hv2(run) = HV(Problem,population2.f(population2.rank==1,:),convex);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\PIHS_hv1.txt','a');
        %     fprintf(fp,'%f\r\n',PIHS_hv1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\PIHS_hv2.txt','a');
        %     fprintf(fp,'%f\r\n',PIHS_hv2(run));
        %     fclose(fp);
        %     %     if run == 20
        %     %         save PIHS_igd1
        %     %         save PIHS_igd2
        %     %     end
        % end
        % if Problem == 5
        %     PIMS_hv1(run) = HV(Problem,population1.f(population1.rank==1,:),circle);
        %     PIMS_hv2(run) = HV(Problem,population2.f(population2.rank==1,:),concave);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\PIMS_hv1.txt','a');
        %     fprintf(fp,'%f\r\n',PIMS_hv1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\PIMS_hv2.txt','a');
        %     fprintf(fp,'%f\r\n',PIMS_hv2(run));
        %     fclose(fp);
        %     %     if run == 20
        %     %         save PIMS_igd1
        %     %         save PIMS_igd2
        %     %     end
        % end
        % if Problem == 6
        %     PILS_hv1(run) = HV(Problem,population1.f(population1.rank==1,:),circle);
        %     PILS_hv2(run) = HV(Problem,population2.f(population2.rank==1,:),circle);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\PILS_hv1.txt','a');
        %     fprintf(fp,'%f\r\n',PILS_hv1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\PILS_hv2.txt','a');
        %     fprintf(fp,'%f\r\n',PILS_hv2(run));
        %     fclose(fp);
        %     %     if run == 20
        %     %         save PILS_igd1
        %     %         save PILS_igd2
        %     %     end
        % end
        % if Problem == 7
        %     NIHS_hv1(run) = HV(Problem,population1.f(population1.rank==1,:),circle);
        %     NIHS_hv2(run) = HV(Problem,population2.f(population2.rank==1,:),convex);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\NIHS_hv1.txt','a');
        %     fprintf(fp,'%f\r\n',NIHS_hv1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\NIHS_hv2.txt','a');
        %     fprintf(fp,'%f\r\n',NIHS_hv2(run));
        %     fclose(fp);
        %     %     if run == 20
        %     %         save NIHS_igd1
        %     %         save NIHS_igd2
        %     %     end
        % end
        % if Problem == 8
        %     NIMS_hv1(run) = HV(Problem,population1.f(population1.rank==1,:),sp);
        %     NIMS_hv2(run) = HV(Problem,population2.f(population2.rank==1,:),concave);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\NIMS_hv1.txt','a');
        %     fprintf(fp,'%f\r\n',NIMS_hv1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\NIMS_hv2.txt','a');
        %     fprintf(fp,'%f\r\n',NIMS_hv2(run));
        %     fclose(fp);
        %     %     if run == 20
        %     %         save NIMS_igd1
        %     %         save NIMS_igd2
        %     %     end
        % end
        % if Problem == 9
        %     NILS_hv1(run) = HV(Problem,population1.f(population1.rank==1,:),sp);
        %     NILS_hv2(run) = HV(Problem,population2.f(population2.rank==1,:),concave);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\NILS_hv1.txt','a');
        %     fprintf(fp,'%f\r\n',NILS_hv1(run));
        %     fclose(fp);
        %     fp = fopen('D:\文件资料\研究生\一年级\优化\多任务多目标优化\论文\experimentalresults\proposed\HV\NILS_hv2.txt','a');
        %     fprintf(fp,'%f\r\n',NILS_hv2(run));
        %     fclose(fp);
        %     %     if run == 20
        %     %         save NILS_igd1
        %     %         save NILS_igd2
        %     %     end
        % end
    end

end
