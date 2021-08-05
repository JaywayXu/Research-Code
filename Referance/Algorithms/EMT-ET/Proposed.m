function Proposed(Problem, NVARS, OBJS1, LBOUND1, UBOUND1, LBOUND2, UBOUND2, population1, population2, ini_pop)

    for run = 1:1 % 30
        r = 30;
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
        G = 8; % 迁移解个数
        d = [];

        % % Plotting and verbose
        % clf

        % if (size(population1.f, 2) == 2)
        %     h_fig1 = figure(1);
        %     h_par1 = scatter(population1.f(:, 1), population1.f(:, 2), 20, 'filled', 'markerFaceAlpha', 0.3, 'MarkerFaceColor', [128 193 219] ./ 255); hold on;
        %     h_rep1 = plot(population1.f(:, 1), population1.f(:, 2), 'ok'); hold on;
        %     grid on; xlabel('f1'); ylabel('f2');
        %     % drawnow;
        %     axis square;
        % end

        % if (size(population2.f, 2) == 2)
        %     h_fig2 = figure(2);
        %     h_par2 = scatter(population2.f(:, 1), population2.f(:, 2), 20, 'filled', 'markerFaceAlpha', 0.3, 'MarkerFaceColor', [128 193 219] ./ 255); hold on;
        %     h_rep2 = plot(population2.f(:, 1), population2.f(:, 2), 'ok'); hold on;
        %     grid on; xlabel('f1'); ylabel('f2');
        %     % drawnow;
        %     axis square;
        % end

        % if (size(population1.f, 2) == 3)
        %     h_fig1 = figure(1);
        %     h_par1 = scatter3(population1.f(:, 1), population1.f(:, 2), population1.f(:, 3), 20, 'filled', 'markerFaceAlpha', 0.3, 'MarkerFaceColor', [128 193 219] ./ 255); hold on;
        %     h_rep1 = plot3(population1.f(:, 1), population1.f(:, 2), population1.f(:, 3), 'ok'); hold on;
        %     grid on; xlabel('f1'); ylabel('f2'); zlabel('f3');
        %     % drawnow;
        %     axis square;
        % end

        % if (size(population2.f, 2) == 3)
        %     h_fig2 = figure(2);
        %     h_par2 = scatter3(population2.f(:, 1), population2.f(:, 2), population2.f(:, 3), 20, 'filled', 'markerFaceAlpha', 0.3, 'MarkerFaceColor', [128 193 219] ./ 255); hold on;
        %     h_rep2 = plot3(population2.f(:, 1), population2.f(:, 2), population2.f(:, 3), 'ok'); hold on;
        %     grid on; xlabel('f1'); ylabel('f2'); zlabel('f3');
        %     % drawnow;
        %     axis square;
        % end

        while generation < 500 % 500
            str = ['Problem : ' num2str(Problem) ', run : ' num2str(run) ', generation : ' num2str(generation)];
            disp(str);
            [~, shareindividuals1] = designation(population2, population1, G, 1, LBOUND1, UBOUND1, LBOUND2, UBOUND2);
            [~, shareindividuals2] = designation(population1, population2, G, 2, LBOUND1, UBOUND1, LBOUND2, UBOUND2);
            cr1 = rand(G, 1);
            cr2 = rand(G, 1);
            % 扰动迁移解
            shareindividuals1.x(cr1 < 0.5, :) = (2 * rand(1)) * shareindividuals1.x(cr1 < 0.5, :);
            shareindividuals2.x(cr2 < 0.5, :) = (2 * rand(1)) * shareindividuals2.x(cr2 < 0.5, :);

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

            % 重置迁移标志
            population1.sign = zeros(ini_pop, 1);
            population2.sign = zeros(ini_pop, 1);
            % 将本代迁移解合并到种群中
            population1.x = [population1.x; shareindividuals2.x(:, 1:NVARS(1))];
            population1.rank = [population1.rank; ones(G, 1)];
            population1.sign = [population1.sign; shareindividuals2.sign];
            population2.x = [population2.x; shareindividuals1.x(:, 1:NVARS(2))];
            population2.rank = [population2.rank; ones(G, 1)];
            population2.sign = [population2.sign; shareindividuals1.sign];
            % 产生子代
            offspring1 = generate(population1, ini_pop - G, proc, disc, prom, dism, Problem, T1, LBOUND1, UBOUND1);
            offspring2 = generate(population2, ini_pop - G, proc, disc, prom, dism, Problem, T2, LBOUND2, UBOUND2);
            % 合并父代子代
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
            % 根据非支配排序和拥挤度更新下一代
            population1 = update_population(mixpopulation1, OBJS1, Problem, NVARS, T1, ini_pop);
            population2 = update_population(mixpopulation2, OBJS1, Problem, NVARS, T2, ini_pop);
            generation = generation + 1;

            % % Plotting and verbose
            % if (size(population1.f, 2) == 2)
            %     figure(h_fig1); delete(h_rep1);
            %     h_par1 = scatter(population1.f(:, 1), population1.f(:, 2), 20, 'filled', 'markerFaceAlpha', 0.3, 'MarkerFaceColor', [128 193 219] ./ 255); hold on;
            %     h_rep1 = plot(population1.f(:, 1), population1.f(:, 2), 'ok'); hold on;
            %     grid on; xlabel('f1'); ylabel('f2');
            %     drawnow;
            %     axis square;
            % end

            % if (size(population2.f, 2) == 2)
            %     figure(h_fig2); delete(h_rep2);
            %     h_par2 = scatter(population2.f(:, 1), population2.f(:, 2), 20, 'filled', 'markerFaceAlpha', 0.3, 'MarkerFaceColor', [128 193 219] ./ 255); hold on;
            %     h_rep2 = plot(population2.f(:, 1), population2.f(:, 2), 'ok'); hold on;
            %     grid on; xlabel('f1'); ylabel('f2');
            %     drawnow;
            %     axis square;
            % end

            % if (size(population1.f, 2) == 3)
            %     figure(h_fig1); delete(h_rep1);
            %     h_par1 = scatter3(population1.f(:, 1), population1.f(:, 2), population1.f(:, 3), 20, 'filled', 'markerFaceAlpha', 0.3, 'MarkerFaceColor', [128 193 219] ./ 255); hold on;
            %     h_rep1 = plot3(population1.f(:, 1), population1.f(:, 2), population1.f(:, 3), 'ok'); hold on;
            %     grid on; xlabel('f1'); ylabel('f2');
            %     drawnow;
            %     axis square;
            % end

            % if (size(population2.f, 2) == 3)
            %     figure(h_fig2); delete(h_rep2);
            %     h_par2 = scatter3(population2.f(:, 1), population2.f(:, 2), population2.f(:, 3), 20, 'filled', 'markerFaceAlpha', 0.3, 'MarkerFaceColor', [128 193 219] ./ 255); hold on;
            %     h_rep2 = plot3(population2.f(:, 1), population2.f(:, 2), population2.f(:, 3), 'ok'); hold on;
            %     grid on; xlabel('f1'); ylabel('f2');
            %     drawnow;
            %     axis square;
            % end

        end

        % plot end population and save
        if (size(population1.f, 2) == 2)
            h1 = figure('Visible', 'off');
            plot(population1.f(:, 1), population1.f(:, 2), 'ok'); hold on;
            grid on; xlabel('f1'); ylabel('f2');
        end

        if (size(population2.f, 2) == 2)
            h2 = figure('Visible', 'off');
            plot(population2.f(:, 1), population2.f(:, 2), 'ok'); hold on;
            grid on; xlabel('f1'); ylabel('f2');
        end

        if (size(population1.f, 2) == 3)
            h1 = figure('Visible', 'off');
            plot3(population1.f(:, 1), population1.f(:, 2), population1.f(:, 3), 'ok'); hold on;
            grid on; xlabel('f1'); ylabel('f2'); zlabel('f3');
            view([45 45 45]);
        end

        if (size(population2.f, 2) == 3)
            h2 = figure('Visible', 'off');
            plot3(population2.f(:, 1), population2.f(:, 2), population2.f(:, 3), 'ok'); hold on;
            grid on; xlabel('f1'); ylabel('f2'); zlabel('f3');
            view([45 45 45]);
        end

        saveas(h1, ['Results_Figure/Problem' num2str(Problem) ' Task1.png']);
        saveas(h2, ['Results_Figure/Problem' num2str(Problem) ' Task2.png']);
        close(h1); close(h2);

        load circle
        load concave
        load convex
        load sp

        if Problem == 1 && run == 1
            CIHS_igd1 = zeros(r, 1);
            CIHS_igd2 = zeros(r, 1);
        end

        if Problem == 2 && run == 1
            CIMS_igd1 = zeros(r, 1);
            CIMS_igd2 = zeros(r, 1);
        end

        if Problem == 3 && run == 1
            CILS_igd1 = zeros(r, 1);
            CILS_igd2 = zeros(r, 1);
        end

        if Problem == 4 && run == 1
            PIHS_igd1 = zeros(r, 1);
            PIHS_igd2 = zeros(r, 1);
        end

        if Problem == 5 && run == 1
            PIMS_igd1 = zeros(r, 1);
            PIMS_igd2 = zeros(r, 1);
        end

        if Problem == 6 && run == 1
            PILS_igd1 = zeros(r, 1);
            PILS_igd2 = zeros(r, 1);
        end

        if Problem == 7 && run == 1
            NIHS_igd1 = zeros(r, 1);
            NIHS_igd2 = zeros(r, 1);
        end

        if Problem == 8 && run == 1
            NIMS_igd1 = zeros(r, 1);
            NIMS_igd2 = zeros(r, 1);
        end

        if Problem == 9 && run == 1
            NILS_igd1 = zeros(r, 1);
            NILS_igd2 = zeros(r, 1);
        end

        if Problem == 1 && run == 1
            CIHS_hv1 = zeros(r, 1);
            CIHS_hv2 = zeros(r, 1);
        end

        if Problem == 2 && run == 1
            CIMS_hv1 = zeros(r, 1);
            CIMS_hv2 = zeros(r, 1);
        end

        if Problem == 3 && run == 1
            CILS_hv1 = zeros(r, 1);
            CILS_hv2 = zeros(r, 1);
        end

        if Problem == 4 && run == 1
            PIHS_hv1 = zeros(r, 1);
            PIHS_hv2 = zeros(r, 1);
        end

        if Problem == 5 && run == 1
            PIMS_hv1 = zeros(r, 1);
            PIMS_hv2 = zeros(r, 1);
        end

        if Problem == 6 && run == 1
            PILS_hv1 = zeros(r, 1);
            PILS_hv2 = zeros(r, 1);
        end

        if Problem == 7 && run == 1
            NIHS_hv1 = zeros(r, 1);
            NIHS_hv2 = zeros(r, 1);
        end

        if Problem == 8 && run == 1
            NIMS_hv1 = zeros(r, 1);
            NIMS_hv2 = zeros(r, 1);
        end

        if Problem == 9 && run == 1
            NILS_hv1 = zeros(r, 1);
            NILS_hv2 = zeros(r, 1);

        end

        if Problem == 1
            CIHS_igd1(run) = igd(Problem, population1.f(population1.rank == 1, :), circle);
            CIHS_igd2(run) = igd(Problem, population2.f(population2.rank == 1, :), concave);

            if run == r
                save CIHS_igd1
                save CIHS_igd2
            end

        end

        if Problem == 2
            CIMS_igd1(run) = igd(Problem, population1.f(population1.rank == 1, :), concave);
            CIMS_igd2(run) = igd(Problem, population2.f(population2.rank == 1, :), circle);

            if run == r
                save CIMS_igd1
                save CIMS_igd2
            end

        end

        if Problem == 3
            CILS_igd1(run) = igd(Problem, population1.f(population1.rank == 1, :), circle);
            CILS_igd2(run) = igd(Problem, population2.f(population2.rank == 1, :), convex);

            if run == r
                save CILS_igd1
                save CILS_igd2
            end

        end

        if Problem == 4
            PIHS_igd1(run) = igd(Problem, population1.f(population1.rank == 1, :), convex);
            PIHS_igd2(run) = igd(Problem, population2.f(population2.rank == 1, :), convex);

            if run == r
                save PIHS_igd1
                save PIHS_igd2
            end

        end

        if Problem == 5
            PIMS_igd1(run) = igd(Problem, population1.f(population1.rank == 1, :), circle);
            PIMS_igd2(run) = igd(Problem, population2.f(population2.rank == 1, :), concave);

            if run == r
                save PIMS_igd1
                save PIMS_igd2
            end

        end

        if Problem == 6
            PILS_igd1(run) = igd(Problem, population1.f(population1.rank == 1, :), circle);
            PILS_igd2(run) = igd(Problem, population2.f(population2.rank == 1, :), circle);

            if run == r
                save PILS_igd1
                save PILS_igd2
            end

        end

        if Problem == 7
            NIHS_igd1(run) = igd(Problem, population1.f(population1.rank == 1, :), circle);
            NIHS_igd2(run) = igd(Problem, population2.f(population2.rank == 1, :), convex);

            if run == r
                save NIHS_igd1
                save NIHS_igd2
            end

        end

        if Problem == 8
            NIMS_igd1(run) = igd(Problem, population1.f(population1.rank == 1, :), sp);
            NIMS_igd2(run) = igd(Problem, population2.f(population2.rank == 1, :), concave);

            if run == r
                save NIMS_igd1
                save NIMS_igd2
            end

        end

        if Problem == 9
            NILS_igd1(run) = igd(Problem, population1.f(population1.rank == 1, :), sp);
            NILS_igd2(run) = igd(Problem, population2.f(population2.rank == 1, :), concave);

            if run == r
                save NILS_igd1
                save NILS_igd2
            end

        end

        % %% HV
        if Problem == 1
            CIHS_hv1(run) = HV(Problem, population1.f(population1.rank == 1, :), circle);
            CIHS_hv2(run) = HV(Problem, population2.f(population2.rank == 1, :), concave);

            if run == r
                save CIHS_hv1
                save CIHS_hv2
            end

        end

        if Problem == 2
            CIMS_hv1(run) = HV(Problem, population1.f(population1.rank == 1, :), concave);
            CIMS_hv2(run) = HV(Problem, population2.f(population2.rank == 1, :), circle);

            if run == r
                save CIMS_hv1
                save CIMS_hv2
            end

        end

        if Problem == 3
            CILS_hv1(run) = HV(Problem, population1.f(population1.rank == 1, :), circle);
            CILS_hv2(run) = HV(Problem, population2.f(population2.rank == 1, :), convex);

            if run == r
                save CILS_hv1
                save CILS_hv2
            end

        end

        if Problem == 4
            PIHS_hv1(run) = HV(Problem, population1.f(population1.rank == 1, :), convex);
            PIHS_hv2(run) = HV(Problem, population2.f(population2.rank == 1, :), convex);

            if run == r
                save PIHS_hv1
                save PIHS_hv2
            end

        end

        if Problem == 5
            PIMS_hv1(run) = HV(Problem, population1.f(population1.rank == 1, :), circle);
            PIMS_hv2(run) = HV(Problem, population2.f(population2.rank == 1, :), concave);

            if run == r
                save PIMS_hv1
                save PIMS_hv2
            end

        end

        if Problem == 6
            PILS_hv1(run) = HV(Problem, population1.f(population1.rank == 1, :), circle);
            PILS_hv2(run) = HV(Problem, population2.f(population2.rank == 1, :), circle);

            if run == r
                save PILS_hv1
                save PILS_hv2
            end

        end

        if Problem == 7
            NIHS_hv1(run) = HV(Problem, population1.f(population1.rank == 1, :), circle);
            NIHS_hv2(run) = HV(Problem, population2.f(population2.rank == 1, :), convex);

            if run == r
                save NIHS_hv1
                save NIHS_hv2
            end

        end

        if Problem == 8
            NIMS_hv1(run) = HV(Problem, population1.f(population1.rank == 1, :), sp);
            NIMS_hv2(run) = HV(Problem, population2.f(population2.rank == 1, :), concave);

            if run == r
                save NIMS_hv1
                save NIMS_hv2
            end

        end

        if Problem == 9
            NILS_hv1(run) = HV(Problem, population1.f(population1.rank == 1, :), sp);
            NILS_hv2(run) = HV(Problem, population2.f(population2.rank == 1, :), concave);

            if run == r
                save NILS_hv1
                save NILS_hv2
            end

        end

    end

end
