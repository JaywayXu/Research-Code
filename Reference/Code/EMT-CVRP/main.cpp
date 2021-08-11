#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cmath>
#include <time.h>
#include <armadillo>
#include <algorithm>
#include "functions.h"
using namespace std;
//using namespace arma;

string select[100] = {
    "benchmark\\select_c\\A-n54-k7-h-v1.txt",
    "benchmark\\select_c\\A-n54-k7-h-v2.txt",
    "benchmark\\select_c\\A-n62-k8-h-v1.txt",
    "benchmark\\select_c\\A-n62-k8-h-v2.txt",
    "benchmark\\select_c\\A-n80-k10-h-v1.txt",
    "benchmark\\select_c\\A-n80-k10-h-v2.txt",
    "benchmark\\select_c\\B-n50-k7-h-v1.txt",
    "benchmark\\select_c\\B-n50-k7-h-v2.txt",
    "benchmark\\select_c\\B-n64-k9-h-v1.txt",
    "benchmark\\select_c\\B-n64-k9-h-v2.txt",
    "benchmark\\select_c\\B-n78-k10-h-v1.txt",
    "benchmark\\select_c\\B-n78-k10-h-v2.txt",
    "benchmark\\select_c\\P-n50-k8-h-v1.txt",
    "benchmark\\select_c\\P-n50-k8-h-v2.txt",
    "benchmark\\select_c\\P-n60-k10-h-v1.txt",
    "benchmark\\select_c\\P-n60-k10-h-v2.txt",
    "benchmark\\select_c\\P-n76-k5-h-v1.txt",
    "benchmark\\select_c\\P-n76-k5-h-v2.txt",

    "benchmark\\select_c\\A-n54-k7-m-v1.txt",
    "benchmark\\select_c\\A-n54-k7-m-v2.txt",
    "benchmark\\select_c\\A-n62-k8-m-v1.txt",
    "benchmark\\select_c\\A-n62-k8-m-v2.txt",
    "benchmark\\select_c\\A-n80-k10-m-v1.txt",
    "benchmark\\select_c\\A-n80-k10-m-v2.txt",
    "benchmark\\select_c\\B-n50-k7-m-v1.txt",
    "benchmark\\select_c\\B-n50-k7-m-v2.txt",
    "benchmark\\select_c\\B-n64-k9-m-v1.txt",
    "benchmark\\select_c\\B-n64-k9-m-v2.txt",
    "benchmark\\select_c\\B-n78-k10-m-v1.txt",
    "benchmark\\select_c\\B-n78-k10-m-v2.txt",
    "benchmark\\select_c\\P-n50-k8-m-v1.txt",
    "benchmark\\select_c\\P-n50-k8-m-v2.txt",
    "benchmark\\select_c\\P-n60-k10-m-v1.txt",
    "benchmark\\select_c\\P-n60-k10-m-v2.txt",
    "benchmark\\select_c\\P-n76-k5-m-v1.txt",
    "benchmark\\select_c\\P-n76-k5-m-v2.txt",

    "benchmark\\select_c\\A-n54-k7-l-v1.txt",
    "benchmark\\select_c\\A-n54-k7-l-v2.txt",
    "benchmark\\select_c\\A-n62-k8-l-v1.txt",
    "benchmark\\select_c\\A-n62-k8-l-v2.txt",
    "benchmark\\select_c\\A-n80-k10-l-v1.txt",
    "benchmark\\select_c\\A-n80-k10-l-v2.txt",
    "benchmark\\select_c\\B-n50-k7-l-v1.txt",
    "benchmark\\select_c\\B-n50-k7-l-v2.txt",
    "benchmark\\select_c\\B-n64-k9-l-v1.txt",
    "benchmark\\select_c\\B-n64-k9-l-v2.txt",
    "benchmark\\select_c\\B-n78-k10-l-v1.txt",
    "benchmark\\select_c\\B-n78-k10-l-v2.txt",
    "benchmark\\select_c\\P-n50-k8-l-v1.txt",
    "benchmark\\select_c\\P-n50-k8-l-v2.txt",
    "benchmark\\select_c\\P-n60-k10-l-v1.txt",
    "benchmark\\select_c\\P-n60-k10-l-v2.txt",
    "benchmark\\select_c\\P-n76-k5-l-v1.txt",
    "benchmark\\select_c\\P-n76-k5-l-v2.txt",
};

void run_solver(string *input_files, string file_op, string run_id, int L, int R, int ls, int rand_insert, int do_km) {

    for(int f_i = L; f_i < R; ++f_i) {
        string input_file_name = input_files[f_i];
        string output_file_name = file_op + "run_id_" + run_id + "_problem_" + nts(f_i+1);


        Problem problem = initializer(input_file_name);

        cout << input_file_name << endl;
        cout << output_file_name << endl;
        solver(problem, output_file_name, ls, rand_insert, do_km, 1);
    }
}

void run_transfer(string *input_files, string file_op, string run_id, vector<pair<int, int> > &matches, int nls, int random_transfer, string mat_dir) {

    string output = file_op + "matches";
    file_output_mathces(matches, output);
    for(int i = 0; i < matches.size(); i++) {
        int f_i = matches[i].first;
        int f_j = matches[i].second;
        string input_file_1 = input_files[f_i];
        string input_file_2 = input_files[f_j];
        Problem problem1 = initializer(input_file_1);
        Problem problem2 = initializer(input_file_2);

        string output_file_1 = file_op + "run_id_" + run_id + "_" + nts(f_i+1) + "-" + nts(f_j+1) + "_" + nts(f_i+1);
        string output_file_2 = file_op + "run_id_" + run_id + "_" + nts(f_i+1) + "-" + nts(f_j+1) + "_" + nts(f_j+1);



        cout << input_file_1 << endl;
        cout << input_file_2 << endl;
        cout << output_file_1 << endl;
        cout << output_file_2 << endl;

        transferSolver(problem1, problem2, output_file_1, output_file_2, nls, random_transfer, f_i, f_j, mat_dir);
    }
}


int main() {
    int file_size = 27;
    int L = 0, R = 27 * GROUP_SIZE;
    srand((unsigned)time(0));


    string *input_files = select;
    string M_dir = "benchmark\\select\\";


    string file_op = "select\\";
    vector <pair<int, int> > matches;
    for(int i = 0; i < file_size * GROUP_SIZE; i += GROUP_SIZE) {
        for(int j = 1; j < GROUP_SIZE; ++j) {
            matches.push_back(make_pair(i, i + j));
//            printf("%d %d\n", i, j+j);
        }
    }
//    puts("start");
    int s = 1, e = 20;
    for(int run = s; run <= e; ++run) {
        string run_id = nts(run);
        // solver_ls1_nri
//        run_solver(input_files, file_op + "result_ls1_nri\\", run_id, L, R, 1, 0, 0);
//
//        // solver_ls1_wri
//        run_solver(input_files, file_op + "result_ls1_wri\\", run_id, L, R, 1, 1, 0);
//
//        // solver_ls2_nri
//        run_solver(input_files, file_op + "result_ls2_nri\\", run_id, L, R, 2, 0, 0);
//
//        // solver_ls2_wri
//        run_solver(input_files, file_op + "result_ls2_wri\\", run_id, L, R, 2, 1, 0);

        // transfer
        run_transfer(input_files, file_op + "transfer_ls1_ls2\\", run_id, matches, 0, 0, M_dir);

    }
    return 0;
}
