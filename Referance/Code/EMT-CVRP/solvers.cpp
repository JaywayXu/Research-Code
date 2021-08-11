#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>
#include <set>
#include <time.h>
#include <armadillo>
#include "functions.h"
using namespace std;

void solver(Problem &problem, string output_file_name, int ls, int rand_insert, int do_km, int output) {
	vector <float> res;
    int current_size = POP_SIZE;
    population_sorting(problem.indi, current_size);
    for(int i = 0; i < current_size; ++i)
        indi_to_chro(&problem.indi[i], &problem.chro[i]);

    vector<float> mark_rand;

    int generation = 0;
    for(int phase = 1; phase <= NP; ++phase){
        int ita = 0;
        bool transfer = false;
        while(ita < ITA){

            if(ita++ % POP_SIZE == 0) {
                res.push_back(problem.indi[0].fitness);
                generation++;
                printf("generation: %d  fitness: %f\n", generation, problem.indi->fitness);
                if(generation % TRANSFER_SPEED == 0)
                    transfer = true;
            }
            if(transfer) {
                if(rand_insert) {

                    delimiter_individual indi[TRANSFER_SIZE];
                    for(int i = 0; i < TRANSFER_SIZE; ++i) {
                        random_initial(&indi[i], problem);
                        add_to_problem(indi[i], problem, ls * 10);
                    }
                }
                transfer = false;
            }
            operaitonProcess(problem, current_size, "problem", ls);
        }
        initializeProblem(problem, current_size);
    }
    if(output)
        file_outputs(res, output_file_name);
	printf("%f\n", problem.indi[0].fitness);
//	print_one_dim_array(problem.indi[0].sequence, problem.indi[0].count);

//    file_outputs(mark_rand, output_file_name+"mark_random\\result_"+nts(output));
//	system("pause");
//	caculate_fitness(problem.indi[0].sequence, problem.indi[0].count, problem);
}


void transferSolver(Problem &problem_1, Problem &problem_2, string output_file_name_1,
                    string output_file_name_2, int nls, int random_transfer, int f_i, int f_j, string mat_dir) {


    int OP1 = 1;
    int OP2;
    if(nls) OP2 = 0;
    else OP2 = 2;

    mat M_1to2 = mat_read(f_i, f_j, problem_1.customer_size, problem_2.customer_size, mat_dir);

    mat M_2to1 = mat_read(f_j, f_i, problem_2.customer_size, problem_1.customer_size, mat_dir);
//    print_mat_float(M_1to2);
//    mat check = problem_1.customer_mat * M_1to2;
//    print_mat_float(problem_2.customer_mat);
//    print_mat_float(check);

    int current_size = POP_SIZE;

    population_sorting(problem_1.indi, current_size);
    population_sorting(problem_2.indi, current_size);


    for(int i = 0; i < current_size; ++i) {
        indi_to_chro(&problem_1.indi[i], &problem_1.chro[i]);
        indi_to_chro(&problem_2.indi[i], &problem_2.chro[i]);
    }
    vector<float> res1, res2;




    int generation = 0;



//    cout << "begin" << endl;
    for(int phase = 1; phase <= NP; ++phase) {
        int ita = 0;
        bool transfer = false;
        while(ita < ITA) {
            if(ita++ % POP_SIZE == 0) {
                res1.push_back(problem_1.indi[0].fitness);
                res2.push_back(problem_2.indi[0].fitness);
                generation++;
                printf("generation: %d  p1 fitness: %f   p2 fitness: %f\n", generation, problem_1.indi[0].fitness, problem_2.indi[0].fitness);
                if(generation % TRANSFER_SPEED == 0)
                    transfer = true;
            }

            if(transfer) {




                for(int i = 0; i < TRANSFER_SIZE; ++i) {
                    undelimiter_individual chromosome1, chromosome2;

                    int k1 = count_zero(problem_2.indi[0].sequence, problem_2.indi[0].count);
                    chromosome1 = transferOperation(problem_1.indi[i], problem_1.customer_size, M_1to2, problem_2.original_dist, k1);
//                    printf("transfer fitness = %f\n", problem_1.indi[i].fitness);

//                    Transfer solver_2 to solver_1
                    int k2 = count_zero(problem_1.indi[0].sequence, problem_1.indi[0].count);
                    chromosome2 = transferOperation(problem_2.indi[i], problem_2.customer_size, M_2to1, problem_1.original_dist, k2);
//                    printf("transfer fitness = %f\n", problem_2.indi[i].fitness);
                    //OP2
                    float _to_2 = OPT(problem_2, chromosome1, current_size, "problem_2", OP2*10);
                    //OP1
                    float _to_1 = OPT(problem_1, chromosome2, current_size, "problem_1", OP1*10);


                }
                transfer = false;
                population_sorting(problem_1.indi, current_size);
                population_sorting(problem_2.indi, current_size);
            }
            operaitonProcess(problem_1, current_size, "problem_1", OP1);
            operaitonProcess(problem_2, current_size, "problem_2", OP2);
        }
        initializeProblem(problem_1, current_size);
        initializeProblem(problem_2, current_size);
    }



	printf("problem_1 fitness: %f\n", problem_1.indi[0].fitness);
//	print_one_dim_array(problem_1.indi[0].sequence, problem_1.indi[0].count);

	printf("problem_2 fitness: %f\n", problem_2.indi[0].fitness);
//	print_one_dim_array(problem_2.indi[0].sequence, problem_2.indi[0].count);
//getchar();
    file_outputs(res1, output_file_name_1);
    file_outputs(res2, output_file_name_2);
}

void operaitonProcess(Problem &problem, int current_size, string problem_n, int op) {



    undelimiter_individual p1, p2;
    undelimiter_individual c;
    delimiter_individual del_c;
    int ox_time = 0;
    do {
        ox_time++;
        binary_tournament(&p1, &p2, current_size, problem.chro);
        ordered_xover(&c, &p1, &p2);
        if(ox_time > MAX_VALUE) {
            puts("ox failed");
//            return;
        }
    } while(!new_split(&del_c, &c, problem));

    add_to_problem(del_c, problem, op);
}

float add_to_problem(delimiter_individual &del_c, Problem &problem, int op) {
    int current_size = POP_SIZE;
    undelimiter_individual c;

//    printf("op = %d\n", op);
    if(op > 0 && op < 3) {
        double random = 1.0*rand()/RAND_MAX;
        if(random <= PLS){
            local_search_v2(&del_c, problem, op);
            indi_to_chro(&del_c, &c);
            split(&del_c, &c, problem);
        }
    }
    if(op >= 10) {
        local_search_v2(&del_c, problem, op / 10);
        indi_to_chro(&del_c, &c);
        split(&del_c, &c, problem);
    }
    int rp_indi = current_size/2 + rand()%(current_size/2);

    bool differ = true;
    for(int i = 0; i < current_size; ++i){
        if(i == rp_indi) continue;
        if(abs_float(del_c.fitness, problem.indi[i].fitness) < COST_SPACE){
            differ = false;
            break;
        }
    }

    bool yes = false;
    if(del_c.fitness < problem.indi[0].fitness || differ){
        yes = true;
        del_indi_copy(&problem.indi[rp_indi], &del_c);
        population_sorting(problem.indi, current_size);
    }

    for(int i = 0; i < current_size; i++)
        indi_to_chro(&problem.indi[i], &problem.chro[i]);

    return yes ? del_c.fitness : 0;
}
