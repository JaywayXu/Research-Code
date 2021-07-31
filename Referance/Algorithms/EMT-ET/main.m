%%
% //This is the code for the experiment of the paper.
% //Coded by: Jiabin Lin and Hai-lin Liu
% //Guangdong University of Technology,Guangzhou,China
% //Last Update:2018/07/30
clear;
clc;

for Problem = 1:9

    if Problem == 8 || Problem == 9
        OBJS1 = 3;
    else
        OBJS1 = 2;
    end

    if Problem == 2
        NVARS = [10, 10];
    elseif Problem == 8
        NVARS = [20, 20];
    else
        NVARS = [50, 50];
    end

    if Problem == 9
        NVARS = [25, 50];
    end

    switch Problem
        case 1
            LBOUND1 = -100 * ones(NVARS(1), 1);
            UBOUND1 = 100 * ones(NVARS(1), 1);
            LBOUND2 = -100 * ones(NVARS(2), 1);
            UBOUND2 = 100 * ones(NVARS(2), 1);
        case 2
            LBOUND1 = -5 * ones(NVARS(1), 1);
            UBOUND1 = 5 * ones(NVARS(1), 1);
            LBOUND2 = -5 * ones(NVARS(2), 1);
            UBOUND2 = 5 * ones(NVARS(2), 1);
        case 3
            LBOUND1 = -2 * ones(NVARS(1), 1);
            UBOUND1 = 2 * ones(NVARS(1), 1);
            LBOUND2 = -1 * ones(NVARS(2), 1);
            UBOUND2 = 1 * ones(NVARS(2), 1);
        case 4
            LBOUND1 = -100 * ones(NVARS(1), 1);
            UBOUND1 = 100 * ones(NVARS(1), 1);
            LBOUND2 = -100 * ones(NVARS(2), 1);
            UBOUND2 = 100 * ones(NVARS(2), 1);
        case 5
            LBOUND1 = 0 * ones(NVARS(1), 1);
            UBOUND1 = 1 * ones(NVARS(1), 1);
            LBOUND2 = 0 * ones(NVARS(2), 1);
            UBOUND2 = 1 * ones(NVARS(2), 1);
        case 6
            LBOUND1 = -50 * ones(NVARS(1), 1);
            UBOUND1 = 50 * ones(NVARS(1), 1);
            LBOUND2 = -100 * ones(NVARS(2), 1);
            UBOUND2 = 100 * ones(NVARS(2), 1);
        case 7
            LBOUND1 = -80 * ones(NVARS(1), 1);
            UBOUND1 = 80 * ones(NVARS(1), 1);
            LBOUND2 = -80 * ones(NVARS(2), 1);
            UBOUND2 = 80 * ones(NVARS(2), 1);
        case 8
            LBOUND1 = -20 * ones(NVARS(1), 1);
            UBOUND1 = 20 * ones(NVARS(1), 1);
            LBOUND2 = -20 * ones(NVARS(2), 1);
            UBOUND2 = 20 * ones(NVARS(2), 1);
        case 9
            LBOUND1 = -50 * ones(NVARS(1), 1);
            UBOUND1 = 50 * ones(NVARS(1), 1);
            LBOUND2 = -100 * ones(NVARS(2), 1);
            UBOUND2 = 100 * ones(NVARS(2), 1);
    end

    LBOUND1(1) = 0;
    UBOUND1(1) = 1;
    LBOUND2(1) = 0;
    UBOUND2(1) = 1;

    if Problem == 8 || Problem == 9
        LBOUND1(2) = 0;
        UBOUND1(2) = 1;
        LBOUND2(2) = 0;
        UBOUND2(2) = 1;
    end

    if Problem == 8 || Problem == 9
        ini_pop = 120;
    else
        ini_pop = 100;
    end

    population1 = initialized(ini_pop, NVARS(1), LBOUND1, UBOUND1);
    population2 = initialized(ini_pop, NVARS(2), LBOUND2, UBOUND2);
    LBOUND1 = LBOUND1';
    UBOUND1 = UBOUND1';
    LBOUND2 = LBOUND2';
    UBOUND2 = UBOUND2';
    Proposed(Problem, NVARS, OBJS1, LBOUND1, UBOUND1, LBOUND2, UBOUND2, population1, population2, ini_pop);
end
