#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <set>
#include <cmath>
#include <time.h>
#include <armadillo>
#include "functions.h"
using namespace std;





void file_outputs(vector<float> &res, string file_name) {
    FILE *fw;
    fw = fopen(file_name.c_str(), "w+");
    if(fw == NULL) {
        puts("filedir do not exist!");
    }
    for(int i = 0; i < res.size(); ++i) {
        fprintf(fw, "%d %.2f\n", i + 1, res[i]);
    }
    fclose(fw);
}

void file_output_mathces(std::vector< std::pair<int, int> > &matches, string file_name) {
    FILE *fw;
    fw = fopen(file_name.c_str(), "w+");
    if(fw == NULL) {
        puts("filedir do not exist!");
    }
    for(int i = 0; i < matches.size(); ++i) {
        fprintf(fw, "%d %d\n", matches[i].first, matches[i].second);
    }
    fclose(fw);
}
string nts(int number) {
    char buf[20];
    memset(buf, 0, sizeof buf);
    sprintf(buf, "%d", number);
    string res = buf;
    return res;
}
mat mat_read(int f1, int f2, int n, int m, const string &mat_dir) {

    string mat_file_dir;
    mat_file_dir = mat_dir + "M_" + nts(f1) + "_" + nts(f2);
//    cout << mat_file_dir << endl;
//    system("pause");
    FILE *fp;
    fp = fopen(mat_file_dir.c_str(), "r");
    if(fp == NULL) {
        puts("M file do not exist!");
    }
    mat res = zeros(n, m);
    float all = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            float temp;
            fscanf(fp, "%f", &temp);
            res(i, j) = temp;
            all += temp;
        }
    }
    if(abs(all) < 0.001) {
        puts("M read wrong!!!");
        system("pause");
    }
    fclose(fp);
    return res;
}
Problem read_data(string input_file_name) {
    Problem problem;
    FILE *fp;
    fp = fopen(input_file_name.c_str(), "r");
    if(fp == NULL) {
        puts("file do not exist!");
        exit(-1);
    }
//    cout << input_file_name << endl;
    fscanf(fp, "%d", &problem.vNumber);
    fscanf(fp, "%d", &problem.capacity);
    fscanf(fp, "%f", &problem.route_time);
    fscanf(fp, "%f", &problem.drop_time);
    fscanf(fp, "%d", &problem.k_size);
    problem.customer_size = problem.vNumber - 1;
    /* 从文件取数据为对应变量赋值 */
    problem.mean_x = 0;
    problem.mean_y = 0;
    for(int i = 0; i < problem.vNumber; ++i) {
        fscanf(fp, "%f", &problem.customer[i].x);
        fscanf(fp, "%f", &problem.customer[i].y);
        fscanf(fp, "%f", &problem.customer[i].demand);
    }
    // 中心化
    float zero_x = problem.customer[0].x;
    float zero_y = problem.customer[0].y;
    for(int i = 1; i < problem.vNumber; ++i) {
        problem.mean_x += (problem.customer[i].x - zero_x) / (1.0 * problem.vNumber - 1);
        problem.mean_y += (problem.customer[i].y - zero_x) / (1.0 * problem.vNumber - 1);
    }
    fclose(fp);
    return problem;
}
float sqr(float a) {
    return a * a;
}
int problem_match(Problem &problem, int except, string *input_files, int file_size) {
    int id = 0;
    float best_dist = MAX_VALUE;
    for(int i = 0; i < file_size; ++i) {
        if(i == except) continue;
        Problem problem_b = read_data(input_files[i]);
        float problem_dist = sqrt(sqr(problem.mean_x-problem_b.mean_x) + sqr(problem.mean_y-problem_b.mean_y)) * 0.8 + abs(problem.capacity - problem_b.capacity) * 0.2;
//        printf("problem id: %d\n", i);
        if(best_dist > problem_dist) {
            best_dist = problem_dist;
            id = i;
        }
    }
    return id;
}
void check_bug(string message, undelimiter_individual *c) {
    set <int> s;
    int max_customer = c->count;
    for(int j = 0; j < max_customer; ++j)
        s.insert(c->sequence[j]);
    if(s.size() != c->count) {
        cout << message << endl;
        system("pause");
    }
}
delimiter_individual get_one_solution(Problem &problem) {
    delimiter_individual indi;
    random_initial(&indi, problem);
    return indi;
}
void print_mat_int(mat &DL) {
    int D[100][100];
    printf("    ");
    for(int j = 0; j < DL.n_cols; ++j) {
        printf("%6d", j+1);
    }
    puts("");
    for(int i = 0; i < DL.n_rows; ++i) {
        printf("%4d", i+1);
        for(int j = 0; j < DL.n_cols; ++j) {
            D[i][j] = DL(i, j);
            printf("%6d", D[i][j]);
        }
        puts("");
    }
    system("pause");
}
void print_mat_float(mat &DL) {
    float D[100][100];

    printf("    ");
    for(int j = 0; j < DL.n_cols; ++j) {
        printf("%6d", j+1);
    }
    puts("");
    for(int i = 0; i < DL.n_rows; ++i) {
        printf("%6d", i+1);
        for(int j = 0; j < DL.n_cols; ++j) {
            D[i][j] = DL(i, j);
            printf("%6.2f", D[i][j]);
        }
        puts("");
    }
    system("pause");
}
void print_problem(Problem &problem) {
//    problem.customer_mat.print("customer_mat: ");
//    problem.original_dist.print("original_dist: ");

    printf("capacity : %d\n", problem.capacity);
    printf("customer_size : %d\n", problem.customer_size);
    printf("drop_time : %f\n", problem.drop_time);
    printf("k_size : %d\n", problem.k_size);
    printf("route_time : %f\n", problem.route_time);
    printf("vNumber : %d\n", problem.vNumber);

    for(int i = 0; i < problem.vNumber; ++i) {
        printf("x = %f, y = %f, demond = %f\n", problem.customer[i].x, problem.customer[i].y, problem.customer[i].demand);
    }
    for(int i = 0; i < 10; i++) {
        printf("count = %d\n", problem.indi[i].count);
        print_one_dim_array(problem.indi[i].sequence, problem.indi[i].count);
    }
}
