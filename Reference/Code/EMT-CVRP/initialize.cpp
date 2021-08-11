#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include "functions.h"
using namespace std;

/*每次随机找一个未在路径中的点，在当前路径中寻找一个合适位置，如果没有，则加入下一个路径中，直到所有点都在各个路径中
*/
void random_undel(undelimiter_individual &undel, int size) {
    undel.count = 0;
    for(int i = 0; i < size; ++i) {
        undel.sequence[undel.count++] = i + 1;
    }
    for(int i = 0; i < size; ++i) {
        int idx = rand() % size;
        swap(undel.sequence[i], undel.sequence[idx]);
    }
}
void repair(undelimiter_individual *undel) {
    int val = undel->sequence[0];
    for(int i = 0; i < undel->count - 1; ++i) {
        undel->sequence[i] = undel->sequence[i+1];
    }
    undel->sequence[undel->count-1] = val;
}
void get_dp(int *a, int n, int *used, vector <int> &res, int *ids, Problem &problem) {
    int dp[VERTEX_NUMBER][MAX_CAPACITY];
    int path[VERTEX_NUMBER][MAX_CAPACITY];
    memset(dp, 0, sizeof dp);
    memset(path, 0, sizeof path);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= problem.capacity; ++j) {
            dp[i][j] = dp[i-1][j];
            path[i][j] = j;
            if(!used[i] && j >= a[i] && dp[i][j] < dp[i-1][j-a[i]] + a[i]) {
                dp[i][j] = dp[i-1][j-a[i]] + a[i];
                path[i][j] = j - a[i];
            }
        }
    }
    int capacity = 0;
    for(int j = problem.capacity; j > 0; --j)
        if(capacity < dp[n][j]) {
            capacity = j;
            break;
        }
//    printf("%d %d\n", n, capacity);
    while(capacity > 0 && n > 0) {
        if(capacity != path[n][capacity]) {
            capacity = path[n][capacity];
            res.push_back(ids[n-1]);
            used[n] = 1;
        }
        n--;
//        printf("%d %d\n", n, capacity);
    }
}
void repair_2(undelimiter_individual *undel, Problem &problem) {
    int a[VERTEX_NUMBER];
    int b[VERTEX_NUMBER];
    int used[VERTEX_NUMBER];
    int n = undel->count;
    for(int i = 0; i < undel->count; ++i) {
        b[i] = undel->sequence[i];
        int idx = b[i];
        a[i+1] = problem.customer[idx].demand;
    }
//    for(int i = 0; i < n; ++i) {
//        printf("%3d ", a[i+1]);
//    }
//    puts("");
    memset(used, 0, sizeof used);
    vector <int> res;

    int repair_cnt = problem.k_size;
    while(repair_cnt--) {
        get_dp(a, n, used, res, b, problem);
//        for(int i = 1; i <= n; ++i) {
//            printf("%3d ", used[i]);
//        }
//        puts("");
//        for(int i = 0; i < res.size(); ++i) {
//            printf("%d ", res[i]);
//        }
//        puts("");
    }
    if(undel->count == res.size()) {
        for(int i = 0; i < undel->count; ++i) {
            undel->sequence[i] = res[i];
        }
    }
//    system("pause");
}
void random_initial(delimiter_individual *indi, Problem &problem){

	int vertex_count=1;

	undelimiter_individual undel;
	undel.count=0;

	indi->count=1;//sequence的长度
	indi->sequence[0]=DEPOT;

    random_undel(undel, problem.vNumber - 1);
    int inital_time = 0;
    while(!split(indi, &undel, problem)) {
        random_undel(undel, problem.vNumber - 1);
        ++inital_time;
        if(inital_time > MAX_INITAL) {
            if(problem.capacity < MAX_CAPACITY)
                repair_2(&undel, problem);
//            puts("repair it");
        }
    }

//    for(int i = 0; i < undel.count; ++i) {
//        int index = undel.sequence[i];
//        printf("%f  ", problem.customer[index].demand);
//    }
//    puts("");
//    system("pause");
};
void initializeProblem(Problem &problem, int current_size) {
    //      重新初始化一部分解, 防止陷入局部最优
    for(int i = NC; i < current_size; i++){
        bool vivid = true;
        random_initial(&problem.indi[i], problem);
        for(int j = 0; j < i; ++j){
                if(abs_float(problem.indi[i].fitness, problem.indi[j].fitness) < COST_SPACE) {
                    vivid = false;
                    break;
                }
        }
        if(!vivid){
            i--;
        }
    }
    population_sorting(problem.indi, current_size);
    for(int i = 0; i < current_size; ++i)
        indi_to_chro(&problem.indi[i], &problem.chro[i]);
}
Problem initializer(string input_file_name) {
    Problem problem = read_data(input_file_name);

    for(int i = 0; i < problem.vNumber; ++i)
        for(int j = 0; j < problem.vNumber; ++j)
            if(i == j)
                problem.travel_cost[i][j] = problem.travel_time[i][j] = 0;
            else
                problem.travel_cost[i][j] = problem.travel_time[i][j] = sqrt(pow(abs(problem.customer[i].x-problem.customer[j].x), 2)
                                         + pow(abs(problem.customer[i].y-problem.customer[j].y), 2));






    srand(unsigned(time(0)));


//    初始化customer matrix D
    problem.customer_mat = getVertexMatrix(problem.customer_size, problem.customer, &problem.customer[0]);
    problem.original_dist = mat(problem.customer_size, problem.customer_size);

    for(int i = 0; i < problem.customer_size; ++i) {
        for(int j = 0; j < problem.customer_size; ++j) {
            problem.original_dist(i, j) = problem.travel_cost[i+1][j+1];
        }
    }
    /* 初始化一批individual */

    for(int i = 0; i < POP_SIZE; ++i) {
        bool vivid = true;
        random_initial(&problem.indi[i], problem);
        //simple_initial(&indi[i]);
        for(int j = 0; j < i; ++j) {
                if(abs_float(problem.indi[i].fitness, problem.indi[j].fitness) < COST_SPACE) {
                    vivid = false;
                    break;
                }
        }
        if(!vivid){
            --i;
        }
    }

    return problem;
}
/*clarke&wright方法*/
void cw_initial(delimiter_individual *indi){

};
