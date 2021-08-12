#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "functions.h"

const char *input_files_T1[] = {
    // Instance for Task1
    "benchmark/C1A/C101.txt",
    "benchmark/C1A/C103.txt",
    "benchmark/C1A/C105.txt",
    "benchmark/C1A/C107.txt",

};

const char *input_files_T2[] = {
    // Instance for Task2
    "benchmark/C1A/C102.txt",
    "benchmark/C1A/C104.txt",
    "benchmark/C1A/C106.txt",
    "benchmark/C1A/C108.txt",

};

char *path[] = {
    "result/C1A/result1/",  "result/C1A/result2/", "result/C1A/result3/",
    "result/C1A/result4/",  "result/C1A/result5/", "result/C1A/result6/",
    "result/C1A/result7/",  "result/C1A/result8/", "result/C1A/result9/",
    "result/C1A/result10/",

};

char *res_file_T1[] = {
    "C101.txt",
    "C103.txt",
    "C105.txt",
    "C107.txt",

};

char *res_file_T2[] = {
    "C102.txt",
    "C104.txt",
    "C106.txt",
    "C108.txt",
};

char *output_average = "result/C1A/average/";
char *output_time = "result/C1A/average/time.txt";

char output_file_T1[50];
char output_file_T2[50];
char average_T1[50];
char average_T2[50];

float lsTime;
int lsCount;

float bestfitness[TASK_NUMBER];
int vNumber[TASK_NUMBER];
int type_number[TASK_NUMBER];
int max_capacity[TASK_NUMBER];

float exeTime;
int task_eval[TASK_NUMBER];
int total_eval[TASK_NUMBER];

/* for VRP_T1 */
vertex customer_T1[VERTEX_NUMBER];
vType vehicle_type_T1[MAX_TYPE];
float travel_time_T1[VERTEX_NUMBER][VERTEX_NUMBER];
float distance_T1[VERTEX_NUMBER][VERTEX_NUMBER];

/* for VRP_T2 */
vertex customer_T2[VERTEX_NUMBER];
vType vehicle_type_T2[MAX_TYPE];
float travel_time_T2[VERTEX_NUMBER][VERTEX_NUMBER];
float distance_T2[VERTEX_NUMBER][VERTEX_NUMBER];

delimiter_individual indi[T_SIZE];
undelimiter_individual chro[T_SIZE];

int main(void) {
    FILE *fp_T1;
    FILE *fw_T1;

    FILE *fp_T2;
    FILE *fw_T2;

    FILE *fw_average_T1;
    FILE *fw_average_T2;

    FILE *fw_time;

    int ptr_T1 = 0;
    int ptr_T2 = 0;

    fw_time = fopen(output_time, "w+");

    for (int N = 0; N < FNUMBER; N++) {
        /* Initialize VRP_T1 */
        fp_T1 = fopen(input_files_T1[N], "r");
        printf("%s\n", input_files_T1[N]);
        fscanf(fp_T1, "%d", &vNumber[VRP_T1]);
        vNumber[VRP_T1] += 1;

        for (int i = 0; i < vNumber[VRP_T1]; i++) {
            fscanf(fp_T1, "%d", &customer_T1[i].number);
            fscanf(fp_T1, "%f", &customer_T1[i].x);
            fscanf(fp_T1, "%f", &customer_T1[i].y);
            fscanf(fp_T1, "%f", &customer_T1[i].demand);
            fscanf(fp_T1, "%f", &customer_T1[i].ready_time);
            fscanf(fp_T1, "%f", &customer_T1[i].due_date);
            fscanf(fp_T1, "%f", &customer_T1[i].service_time);
        }
        fscanf(fp_T1, "%d", &type_number[VRP_T1]);
        for (int i = 0; i < type_number[VRP_T1]; i++) {
            fscanf(fp_T1, "%d", &vehicle_type_T1[i].number);
            fscanf(fp_T1, "%f", &vehicle_type_T1[i].capacity);
            fscanf(fp_T1, "%f", &vehicle_type_T1[i].fix_cost);
            fscanf(fp_T1, "%f", &vehicle_type_T1[i].varible_cost);
            fscanf(fp_T1, "%f", &vehicle_type_T1[i].vetime);
            fscanf(fp_T1, "%f", &vehicle_type_T1[i].vltime);
            fscanf(fp_T1, "%d", &vehicle_type_T1[i].type);
        }
        max_capacity[VRP_T1] =
            vehicle_type_T1[type_number[VRP_T1] - 1].capacity;

        for (int i = 0; i < vNumber[VRP_T1]; i++)
            for (int j = 0; j < vNumber[VRP_T1]; j++)
                if (i == j)
                    travel_time_T1[i][j] = 0;
                else
                    travel_time_T1[i][j] =
                        sqrt(pow(abs(customer_T1[i].x - customer_T1[j].x), 2) +
                             pow(abs(customer_T1[i].y - customer_T1[j].y), 2));
        memcpy(distance_T1, travel_time_T1, sizeof(travel_time_T1));

        /* Initialize VRP_T1 */
        fp_T2 = fopen(input_files_T2[N], "r");
        printf("%s\n", input_files_T2[N]);
        fscanf(fp_T2, "%d", &vNumber[VRP_T2]);
        vNumber[VRP_T2] += 1;

        for (int i = 0; i < vNumber[VRP_T2]; i++) {
            fscanf(fp_T2, "%d", &customer_T2[i].number);
            fscanf(fp_T2, "%f", &customer_T2[i].x);
            fscanf(fp_T2, "%f", &customer_T2[i].y);
            fscanf(fp_T2, "%f", &customer_T2[i].demand);
            fscanf(fp_T2, "%f", &customer_T2[i].ready_time);
            fscanf(fp_T2, "%f", &customer_T2[i].due_date);
            fscanf(fp_T2, "%f", &customer_T2[i].service_time);
        }
        fscanf(fp_T2, "%d", &type_number[VRP_T2]);
        for (int i = 0; i < type_number[VRP_T2]; i++) {
            fscanf(fp_T2, "%d", &vehicle_type_T2[i].number);
            fscanf(fp_T2, "%f", &vehicle_type_T2[i].capacity);
            fscanf(fp_T2, "%f", &vehicle_type_T2[i].fix_cost);
            fscanf(fp_T2, "%f", &vehicle_type_T2[i].varible_cost);
            fscanf(fp_T2, "%f", &vehicle_type_T2[i].vetime);
            fscanf(fp_T2, "%f", &vehicle_type_T2[i].vltime);
            fscanf(fp_T2, "%d", &vehicle_type_T2[i].type);
        }
        max_capacity[VRP_T2] =
            vehicle_type_T2[type_number[VRP_T2] - 1].capacity;

        for (int i = 0; i < vNumber[VRP_T2]; i++)
            for (int j = 0; j < vNumber[VRP_T2]; j++)
                if (i == j)
                    travel_time_T2[i][j] = 0;
                else
                    travel_time_T2[i][j] =
                        sqrt(pow(abs(customer_T2[i].x - customer_T2[j].x), 2) +
                             pow(abs(customer_T2[i].y - customer_T2[j].y), 2));
        memcpy(distance_T2, travel_time_T2, sizeof(travel_time_T2));

        fclose(fp_T1);
        fclose(fp_T2);

        ptr_T1 = 0;
        ptr_T2 = 0;
        while (output_average[ptr_T1] != 0) {
            average_T1[ptr_T1] = output_average[ptr_T1];
            average_T2[ptr_T2] = output_average[ptr_T2];
            ptr_T1++;
            ptr_T2++;
        }
        int k = 0;
        while (res_file_T1[N][k] != 0) {
            average_T1[ptr_T1] = res_file_T1[N][k];
            ptr_T1++;
            k++;
        }
        k = 0;
        while (res_file_T2[N][k] != 0) {
            average_T2[ptr_T2] = res_file_T2[N][k];
            ptr_T2++;
            k++;
        }

        fw_average_T1 = fopen(average_T1, "w+");
        fw_average_T2 = fopen(average_T2, "w+");

        printf("%s\n", average_T1);
        printf("%s\n", average_T2);

        float sum_fitness[TASK_NUMBER][ENUMBER * NP];
        memset(sum_fitness, 0, sizeof(sum_fitness));
        exeTime = 0;

        int current_size;
        for (int ex_time = 0; ex_time < EX_TIME; ex_time++) {
            srand(unsigned(time(0)));
            for (int i = 0; i < POP_SIZE; i++) {
                encoding(chro[i].sequence);
            }

            factorial_cost(0, POP_SIZE);
            factorial_rank(POP_SIZE);
            scalar_fitness(POP_SIZE);
            skill_factor(0, POP_SIZE);

            current_size = POP_SIZE;
            population_sorting(chro, current_size, VRP_T1);
            bestfitness[VRP_T1] = chro[0].fitness[VRP_T1];
            population_sorting(chro, current_size, VRP_T2);
            bestfitness[VRP_T2] = chro[0].fitness[VRP_T2];
            popSorting_by_scalarFitness(chro, current_size);

            undelimiter_individual c1, c2;
            delimiter_individual del_c1, del_c2;

            ptr_T1 = 0;
            ptr_T2 = 0;

            while (path[ex_time][ptr_T1] != 0) {
                output_file_T1[ptr_T1] = path[ex_time][ptr_T1];
                output_file_T2[ptr_T2] = path[ex_time][ptr_T2];
                ptr_T1++;
                ptr_T2++;
            }

            k = 0;
            while (res_file_T1[N][k] != 0) {
                output_file_T1[ptr_T1] = res_file_T1[N][k];
                ptr_T1++;
                k++;
            }

            k = 0;
            while (res_file_T2[N][k] != 0) {
                output_file_T2[ptr_T2] = res_file_T2[N][k];
                ptr_T2++;
                k++;
            }

            fw_T1 = fopen(output_file_T1, "w+");
            fw_T2 = fopen(output_file_T2, "w+");

            printf("%s\n", output_file_T1);
            printf("%s\n", output_file_T2);

            int generation = 0;
            clock_t start_time = clock();
            lsTime = 0;
            lsCount = 0;
            total_eval[VRP_T1] = 0;
            total_eval[VRP_T2] = 0;

            for (int phase = 1; phase <= NP; phase++) {
                task_eval[VRP_T1] = 0;
                task_eval[VRP_T2] = 0;
                while (task_eval[VRP_T1] != ENUMBER ||
                       task_eval[VRP_T2] != ENUMBER) {
                    assortative_mating(&c1, &c2, current_size);

                    if (task_eval[c1.skill_factor] < ENUMBER) {
                        undel_indi_copy(&chro[current_size], &c1);
                        current_size++;
                        if (c1.fitness[c1.skill_factor] <
                            bestfitness[c1.skill_factor]) {
                            bestfitness[c1.skill_factor] =
                                c1.fitness[c1.skill_factor];
                            printf("c1.fitness[%d]:%f\n", c1.skill_factor,
                                   c1.fitness[c1.skill_factor]);
                        }
                        if (current_size == T_SIZE) current_size = POP_SIZE;
                    }

                    if (task_eval[c2.skill_factor] < ENUMBER) {
                        undel_indi_copy(&chro[current_size], &c2);
                        current_size++;
                        if (c2.fitness[c2.skill_factor] <
                            bestfitness[c2.skill_factor]) {
                            bestfitness[c2.skill_factor] =
                                c2.fitness[c2.skill_factor];
                            printf("c2.fitness[%d]:%f\n", c2.skill_factor,
                                   c2.fitness[c2.skill_factor]);
                        }
                        if (current_size == T_SIZE) current_size = POP_SIZE;
                    }

                    factorial_rank(current_size);
                    scalar_fitness(current_size);
                    popSorting_by_scalarFitness(chro, current_size);

                    if (current_size == T_SIZE) current_size = POP_SIZE;

                    if (c1.skill_factor == VRP_T1 &&
                        task_eval[VRP_T1] < ENUMBER) {
                        fprintf(fw_T1, "%d ", total_eval[VRP_T1]);
                        fprintf(fw_T1, "%0.2f\r\n", bestfitness[VRP_T1]);
                        sum_fitness[VRP_T1][total_eval[VRP_T1]] +=
                            bestfitness[VRP_T1];
                        task_eval[VRP_T1]++;
                        total_eval[VRP_T1]++;
                    }
                    if (c1.skill_factor == VRP_T2 &&
                        task_eval[VRP_T2] < ENUMBER) {
                        fprintf(fw_T2, "%d ", total_eval[VRP_T2]);
                        fprintf(fw_T2, "%0.2f\r\n", bestfitness[VRP_T2]);
                        sum_fitness[VRP_T2][total_eval[VRP_T2]] +=
                            bestfitness[VRP_T2];
                        task_eval[VRP_T2]++;
                        total_eval[VRP_T2]++;
                    }

                    if (c2.skill_factor == VRP_T1 &&
                        task_eval[VRP_T1] < ENUMBER) {
                        fprintf(fw_T1, "%d ", total_eval[VRP_T1]);
                        fprintf(fw_T1, "%0.2f\r\n", bestfitness[VRP_T1]);
                        sum_fitness[VRP_T1][total_eval[VRP_T1]] +=
                            bestfitness[VRP_T1];
                        task_eval[VRP_T1]++;
                        total_eval[VRP_T1]++;
                    }
                    if (c2.skill_factor == VRP_T2 &&
                        task_eval[VRP_T2] < ENUMBER) {
                        fprintf(fw_T2, "%d ", total_eval[VRP_T2]);
                        fprintf(fw_T2, "%0.2f\r\n", bestfitness[VRP_T2]);
                        sum_fitness[VRP_T2][total_eval[VRP_T2]] +=
                            bestfitness[VRP_T2];
                        task_eval[VRP_T2]++;
                        total_eval[VRP_T2]++;
                    }
                }
                popSorting_by_scalarFitness(chro, POP_SIZE);
                if (phase <= NP) {
                    for (int i = NC; i < POP_SIZE; i++) {
                        encoding(chro[i].sequence);
                    }

                    factorial_cost(NC, POP_SIZE);
                    factorial_rank(POP_SIZE);
                    scalar_fitness(POP_SIZE);
                    skill_factor(NC, POP_SIZE);
                }
            }
            clock_t endtime = clock();
            exeTime += (float)(endtime - start_time) / CLOCKS_PER_SEC;
            printf("exeTime: %f\n", exeTime);
            printf("lsTime: %f\n", lsTime);
            printf("lsCount: %d\n", lsCount);

            int *finalType;
            population_sorting(chro, POP_SIZE, VRP_T1);
            printf("%f\n", chro[0].fitness[VRP_T1]);

            finalType = new int[type_number[VRP_T1]];
            memset(finalType, 0, sizeof(int) * type_number[VRP_T1]);
            getType(finalType, chro[0]);
            for (int i = 0; i < type_number[VRP_T1]; i++)
                fprintf(fw_T1, "%d ", finalType[i]);
            ////////////////////////////////////////////
            population_sorting(chro, POP_SIZE, VRP_T2);
            printf("%f\n", chro[0].fitness[VRP_T2]);

            finalType = new int[type_number[VRP_T2]];
            memset(finalType, 0, sizeof(int) * type_number[VRP_T2]);
            getType(finalType, chro[0]);
            for (int i = 0; i < type_number[VRP_T2]; i++)
                fprintf(fw_T2, "%d ", finalType[i]);

            fclose(fw_T1);
            fclose(fw_T2);
        }

        fprintf(fw_time, "%f\r\n", exeTime / EX_TIME);
        for (int i = 0; i < ENUMBER * NP; i++) {
            fprintf(fw_average_T1, "%d ", i);
            fprintf(fw_average_T1, "%f\r\n", sum_fitness[VRP_T1][i] / EX_TIME);
            fprintf(fw_average_T2, "%d ", i);
            fprintf(fw_average_T2, "%f\r\n", sum_fitness[VRP_T2][i] / EX_TIME);
        }
        fclose(fw_average_T1);
        fclose(fw_average_T2);
    }
    fclose(fw_time);
};
