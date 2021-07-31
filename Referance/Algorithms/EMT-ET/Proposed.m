function Proposed(Problem, NVARS, OBJS1, LBOUND1, UBOUND1, LBOUND2, UBOUND2, population1, population2, ini_pop)

    for run = 1:30
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
        G = 8;
        d = [];

        while generation < 500
            str = ['Problem : ' num2str(Problem) ', run : ' num2str(run) ', generation : ' num2str(generation)];
            disp(str);
            [~, shareindividuals1] = designation(population2, population1, G, 1, LBOUND1, UBOUND1, LBOUND2, UBOUND2);
            [~, shareindividuals2] = designation(population1, population2, G, 2, LBOUND1, UBOUND1, LBOUND2, UBOUND2);
            cr1 = rand(G, 1);
            cr2 = rand(G, 1);
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

        end

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
