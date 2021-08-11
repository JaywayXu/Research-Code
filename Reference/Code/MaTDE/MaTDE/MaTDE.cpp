// Many-task Evolutionary Framework (implemented using DE, MaTDE)
// Related paper: Y. Chen, J. Zhong, L. Feng and J. Zhang. "An Adaptive
// Archive-Based Evolutionary Framework for Many-Task Optimization." Coded by:
// Yongliang Chen South China University of Technology, Guangzhou, China Last
// Update: 2019/06/05
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#define MAX_NVARS 50        // The maximum dimension of the tasks.
#define POPSIZE 100         // Population size for each sub-population
#define MAX_OBJS 1          // Maximum number of objectives
#define MAX_GEN 1000        // Maximum generation
#define RECORD_FRE 100      // Interval of recording
#define RUNS 10             // Total runs for each Problem
#define MAXEVALS 300000     // Mximum number of evaluations
#define K_ARCHIVE_SIZE 300  // Archive size
#define total_task_num 10   // Total task number
#define alpha 0.1           // The rate of Transfer Learning Crossover
#define replace_rate 0.2    // Archive update rate (UR)
#define ro 0.8              // The attenuation coefficient
#define shrink_rate 0.8     // shrink rate of the local refined process

int task_num;                 // The task number of current problem
int NVARS;                    // Dimension of the current function being solved.
int NVARS_t[total_task_num];  // Dimension number of each task
double LBOUND[MAX_NVARS];     // Lower bound of the function being solved
double UBOUND[MAX_NVARS];     // Upper bound of the function being solved
const double PI = acos(-1.0);
int generation;                                      // current generation
double possibility[total_task_num][total_task_num];  // Possibility table
double reward[total_task_num][total_task_num];       // Reward table
int evals;                                           // Evaluation times
int job;                                             // Current run number

struct gene {
    double x[MAX_NVARS];  // variable values
    double f[MAX_OBJS];   // objectives
};
//-------------------structure of chromosome.-------------------------
gene population[total_task_num][4 * POPSIZE], newpopulation,
    mixpopulation[2 * POPSIZE];

//--------------------variables for result reporting-----------------
double fbest_value[total_task_num][MAX_GEN / RECORD_FRE + 1][RUNS];
int TLC_record[total_task_num][MAX_GEN / RECORD_FRE][total_task_num];

//----------------for single-objective test------------------------
#define Single_Num 10
int successful_transfer[total_task_num][total_task_num][10];
double fbest[total_task_num];
//---------parameters for DE---------------------
#define LF 0.1
#define UF 2
#define LCR 0.1
#define UCR 0.9
double F;
double CR;

//-----------parameters for approximation measuring-----------
double Cov[total_task_num][MAX_NVARS][MAX_NVARS];  // Covariance matrixs
double Cov_Inv[total_task_num][MAX_NVARS]
              [MAX_NVARS];       // Inverse covariance matrixs
double Cov_Det[total_task_num];  // Deteminents for covariance matrixs
double Cov_Mean[total_task_num]
               [MAX_NVARS];  // Mean vector for covariance matrixs
double KLD[total_task_num];  // Similarities between a certain task to other
                             // tasks based on KL divergence
double avg_value[total_task_num]
                [MAX_NVARS];         // Average values for each dimension
int k_archive_size[total_task_num];  // Current size of archive
struct gene K_archive[total_task_num][K_ARCHIVE_SIZE];  // Archive
int trans_target;

#include "benchmark.h"

//@function£ºgenerate a random value uniformly distributing within [a,b]
double randval(double a, double b) {
    return a + (b - a) * rand() / (double)RAND_MAX;
}

//------------fitness calculation---------------------
void objective(int g, double x[MAX_NVARS], double f[]) {
    if (g == 0) {
        f[0] = Sphere(x, g);
    } else if (g == 1) {
        f[0] = Sphere2(x, g);
    } else if (g == 2) {
        f[0] = Sphere3(x, g);
    } else if (g == 3) {
        f[0] = Weierstrass25D(x, g);
    } else if (g == 4) {
        f[0] = Rosenbrock(x, g);
    } else if (g == 5) {
        f[0] = Ackley(x, g);
    } else if (g == 6) {
        f[0] = Weierstrass50D(x, g);
    } else if (g == 7) {
        f[0] = Schwefel(x, g);
    } else if (g == 8) {
        f[0] = Griewank(x, g);
    } else if (g == 9) {
        f[0] = Rastrgin(x, g);
    }

    evals += 1;
}

void get_Cov(int trans_target) {
    int i, j, l;
    for (i = 0; i < NVARS; i++) {
        double s = 0;
        for (j = 0; j < k_archive_size[trans_target]; j++) {
            s += K_archive[trans_target][j].x[i];
        }
        avg_value[trans_target][i] = s / k_archive_size[trans_target];
    }

    for (i = 0; i < NVARS; i++)
        for (j = 0; j <= i; j++) {
            double s = 0;
            for (l = 0; l < k_archive_size[trans_target]; l++)
                s += (K_archive[trans_target][l].x[i] -
                      avg_value[trans_target][i]) *
                     (K_archive[trans_target][l].x[j] -
                      avg_value[trans_target][j]);
            Cov[trans_target][i][j] = Cov[trans_target][j][i] =
                s / k_archive_size[trans_target];
        }
}

void get_Cov_Det(int trans_target) {
    int i, j, k, is, js, l, u, v;
    double f, det, q, d;
    double a[MAX_NVARS][MAX_NVARS];
    for (i = 0; i < NVARS; i++)
        for (j = 0; j < NVARS; j++) a[i][j] = Cov[trans_target][i][j];

    f = 1.0;
    det = 1.0;
    for (k = 0; k <= NVARS - 2; k++) {
        q = 0.0;

        for (i = k; i <= NVARS - 1; i++) {
            for (j = k; j <= NVARS - 1; j++) {
                d = fabs(a[i][j]);
                if (d > q) {
                    q = d;
                    is = i;
                    js = j;
                }
            }
        }

        if (q + 1.0 == 1.0) {
            det = 0.0;
            //	printf("error!");
            return;
        }

        if (is != k) {
            f = -f;
            for (j = k; j <= NVARS - 1; j++) {
                d = a[k][j];
                a[k][j] = a[is][j];
                a[is][j] = d;
            }
        }

        if (js != k) {
            f = -f;
            for (i = k; i <= NVARS - 1; i++) {
                d = a[i][js];
                a[i][js] = a[i][k];
                a[i][k] = d;
            }
        }

        det = det * a[k][k];
        for (i = k + 1; i <= NVARS - 1; i++) {
            d = a[i][k] / a[k][k];
            for (j = k + 1; j <= NVARS - 1; j++) {
                a[i][j] = a[i][j] - d * a[k][j];
            }
        }
    }

    det = f * det * a[NVARS - 1][NVARS - 1];

    Cov_Det[trans_target] = det;
}

void get_Cov_Inv(int trans_target) {
    int is[MAX_NVARS], js[MAX_NVARS];
    int i, j, k, l, u, v;
    double d, p;
    for (i = 0; i < NVARS; i++)
        for (j = 0; j < NVARS; j++)
            Cov_Inv[trans_target][i][j] = Cov[trans_target][i][j];

    for (i = 0; i < NVARS; i++) {
        is[i] = 0;
        js[i] = 0;
    }

    for (k = 0; k <= NVARS - 1; k++) {
        d = 0.0;
        for (i = k; i <= NVARS - 1; i++) {
            for (j = k; j <= NVARS - 1; j++) {
                p = fabs(Cov_Inv[trans_target][i][j]);
                if (p > d) {
                    d = p;
                    is[k] = i;
                    js[k] = j;
                }
            }
        }

        if (d + 1.0 == 1.0) {
            //	printf("error!");
            return;
        }

        if (is[k] != k) {
            for (j = 0; j <= NVARS - 1; j++) {
                p = Cov_Inv[trans_target][k][j];
                Cov_Inv[trans_target][k][j] = Cov_Inv[trans_target][is[k]][j];
                Cov_Inv[trans_target][is[k]][j] = p;
            }
        }

        if (js[k] != k) {
            for (i = 0; i <= NVARS - 1; i++) {
                p = Cov_Inv[trans_target][i][k];
                Cov_Inv[trans_target][i][k] = Cov_Inv[trans_target][i][js[k]];
                Cov_Inv[trans_target][i][js[k]] = p;
            }
        }

        Cov_Inv[trans_target][k][k] = 1.0 / Cov_Inv[trans_target][k][k];

        for (j = 0; j <= NVARS - 1; j++)
            if (j != k)
                Cov_Inv[trans_target][k][j] *= Cov_Inv[trans_target][k][k];
        for (i = 0; i <= NVARS - 1; i++)
            if (i != k)
                for (j = 0; j <= NVARS - 1; j++)
                    if (j != k) {
                        Cov_Inv[trans_target][i][j] =
                            Cov_Inv[trans_target][i][j] -
                            Cov_Inv[trans_target][i][k] *
                                Cov_Inv[trans_target][k][j];
                    }

        for (i = 0; i <= NVARS - 1; i++) {
            if (i != k) {
                Cov_Inv[trans_target][i][k] =
                    -Cov_Inv[trans_target][i][k] * Cov_Inv[trans_target][k][k];
            }
        }
    }

    for (k = NVARS - 1; k >= 0; k--) {
        if (js[k] != k) {
            for (j = 0; j <= NVARS - 1; j++) {
                p = Cov_Inv[trans_target][k][j];
                Cov_Inv[trans_target][k][j] = Cov_Inv[trans_target][js[k]][j];
                Cov_Inv[trans_target][js[k]][j] = p;
            }
        }

        if (is[k] != k) {
            for (i = 0; i <= NVARS; i++) {
                p = Cov_Inv[trans_target][i][k];
                Cov_Inv[trans_target][i][k] = Cov_Inv[trans_target][i][is[k]];
                Cov_Inv[trans_target][i][is[k]] = p;
            }
        }
    }
}

double get_Trace(int t1, int t2) {
    int i, j, l;
    double sum;
    double result[MAX_NVARS][MAX_NVARS];
    for (i = 0; i < NVARS; i++) {
        for (j = 0; j < NVARS; j++) {
            sum = 0;
            for (l = 0; l < NVARS; l++)
                sum += Cov_Inv[t1][i][l] * Cov[t2][l][j];
            result[i][j] = sum;
        }
    }

    sum = 0;
    for (i = 0; i < NVARS; i++) sum += result[i][i];

    return sum;
}

double get_Mul(int t1, int t2) {
    double a[MAX_NVARS];
    double sum;
    int i, j;

    for (i = 0; i < NVARS; i++) {
        sum = 0;
        for (j = 0; j < NVARS; j++) {
            sum += (avg_value[t1][j] - avg_value[t2][j]) * Cov_Inv[t1][j][i];
        }
        a[i] = sum;
    }

    sum = 0;
    for (i = 0; i < NVARS; i++) {
        sum += (avg_value[t1][i] - avg_value[t2][i]) * a[i];
    }

    return sum;
}

// Calculate the KLD between "task" task and the other tasks
void cal_KLD(int task) {
    int i, j;
    double tr, u;
    double s1, s2;
    for (i = 0; i < task_num; i++) {
        if (task == i) continue;
        NVARS = (NVARS_t[task] > NVARS_t[i]
                     ? NVARS_t[i]
                     : NVARS_t[task]);  // Pick the smaller dimension number to
                                        // calculate KLD
        get_Cov(task);
        get_Cov(i);
        get_Cov_Det(task);
        get_Cov_Inv(task);
        get_Cov_Det(i);
        get_Cov_Inv(i);
        tr = get_Trace(task, i);
        u = get_Mul(task, i);
        if (Cov_Det[i] < 1e-3) Cov_Det[i] = 0.001;
        if (Cov_Det[task] < 1e-3) Cov_Det[task] = 0.001;
        s1 = fabs(0.5 * (tr + u - NVARS + log(Cov_Det[task] / Cov_Det[i])));

        tr = get_Trace(i, task);
        u = get_Mul(i, task);

        s2 = fabs(0.5 * (tr + u - NVARS + log(Cov_Det[i] / Cov_Det[task])));

        KLD[i] = 0.5 * (s1 + s2);
    }
    NVARS = NVARS_t[task];
}

// Insert individual p into "task" archive
void put_k_archive(gene &p, int task) {
    if (k_archive_size[task] < K_ARCHIVE_SIZE - 1)
        K_archive[task][k_archive_size[task]++] = p;
    else {
        int l = rand() % K_ARCHIVE_SIZE;
        K_archive[task][l] = p;
    }
}

int adaptive_choose(int task) {
    int i;
    double sum = 0;
    int max = 0;
    double max_p = -1e10;
    cal_KLD(task);
    // Update possibility table
    for (i = 0; i < task_num; i++) {
        if (i == task) continue;
        possibility[task][i] =
            ro * possibility[task][i] + reward[task][i] / (1 + log(1 + KLD[i]));
        sum += possibility[task][i];
    }

    // roulette wheel selection
    double p = randval(0, 1);
    double s = 0;
    for (i = 0; i < task_num; i++) {
        if (i == task) continue;
        s += possibility[task][i] / sum;
        if (s >= p) break;
    }
    return i;
}

void production(int task) {
    int i, j, k, l;
    int r1;

    if (randval(0, 1) >
        alpha) {  // perform the crossover and mutation within the subpopulation
        for (i = 0; i < POPSIZE; i++) {
            do {
                r1 = rand() % POPSIZE;
            } while (i == r1);
            F = randval(LF, UF);
            CR = randval(LCR, UCR);

            k = rand() % NVARS;
            for (j = 0; j < MAX_NVARS; j++) {
                newpopulation.x[j] =
                    population[task][i].x[j] +
                    F * (population[task][r1].x[j] - population[task][i].x[j]);
                if (newpopulation.x[j] > UBOUND[j])
                    newpopulation.x[j] =
                        randval(population[task][i].x[j], UBOUND[j]);
                if (newpopulation.x[j] < LBOUND[j])
                    newpopulation.x[j] =
                        randval(LBOUND[j], population[task][i].x[j]);
                if (k == j || randval(0, 1) < CR) {
                } else {
                    newpopulation.x[j] = population[task][i].x[j];
                }
            }

            objective(task, newpopulation.x, newpopulation.f);

            if (newpopulation.f[0] < population[task][i].f[0]) {
                population[task][i] = newpopulation;
            }
        }
    } else {
        // knowledge transferring£º
        // perform the crossover and mutation cross different subpopulations
        l = adaptive_choose(task);

        gene p = population[task][0];
        double s = 0;
        s = fbest[task];
        TLC_record[task][generation / RECORD_FRE][l]++;
        for (i = 0; i < POPSIZE; i++) {
            r1 = rand() % POPSIZE;
            CR = randval(LCR, UCR);
            k = rand() % NVARS;

            for (j = 0; j < MAX_NVARS; j++) {
                if (k == j ||
                    randval(0, 1) < CR) {  // at least one dimension is replaced
                    newpopulation.x[j] = population[l][r1].x[j];
                } else {
                    newpopulation.x[j] = population[task][i].x[j];
                }
            }
            objective(task, newpopulation.x, newpopulation.f);

            if (newpopulation.f[0] < population[task][i].f[0]) {
                population[task][i] = newpopulation;
            }
        }

        if (fbest[task] < s) {
            reward[task][l] /= shrink_rate;
            successful_transfer[task][l][generation / 100]++;
        } else
            reward[task][l] *= shrink_rate;
    }
}

// Parameter initialization
void initialized() {
    int i, j, l;
    evals = 0;

    for (int i = 0; i < total_task_num; i++) NVARS_t[i] = MAX_NVARS;
    NVARS_t[3] /= 2;
    for (i = 0; i < task_num; i++) fbest[i] = 1e20;
    for (i = 0; i < MAX_NVARS; i++) {
        UBOUND[i] = 1;
        LBOUND[i] = 0;
    }

    memset(k_archive_size, 0, sizeof(k_archive_size));

    for (l = 0; l < task_num; l++) {
        for (i = 0; i < POPSIZE; i++) {
            for (j = 0; j < MAX_NVARS; j++) {
                population[l][i].x[j] = randval(LBOUND[j], UBOUND[j]);
            }
            NVARS = NVARS_t[l];
            objective(l, population[l][i].x, population[l][i].f);
            put_k_archive(population[l][i], l);
        }
    }

    for (i = 0; i < task_num; i++) {
        for (j = 0; j < task_num; j++) {
            possibility[i][j] = 0;
            reward[i][j] = 1;
        }
    }
}

void MaTDE() {
    int i, j;
    initialized();
    generation = 0;
    //------------record the initial results---------------------
    for (i = 0; i < task_num; i++) {
        fbest_value[i][0][job] = fbest[i];
    }
    printf("generation:%d\n", generation);
    for (i = 0; i < task_num; i++) {
        printf("fbest%d=%lf\n", i + 1, fbest_value[i][0][job]);
    }

    while (generation < MAX_GEN) {
        // generate offspring based on the two populations, knowledge transfer
        // will happen here.
        for (i = 0; i < task_num; i++) {
            NVARS = NVARS_t[i];
            production(i);
        }
        // Update archive
        for (i = 0; i < task_num; i++) {
            for (j = 0; j < POPSIZE; j++)
                if (randval(0, 1) < replace_rate)
                    put_k_archive(population[i][j], i);
        }
        // Print the current best
        if ((generation + 1) % RECORD_FRE == 0) {
            int k = (generation + 1) / RECORD_FRE;
            for (i = 0; i < task_num; i++) {
                fbest_value[i][k][job] = fbest[i];
                printf("run:%d\n", job);
                printf("generation:%d\t", generation + 1);
                printf("fbest%d=%lf\n", i + 1, fbest_value[i][k][job]);
            }
        }
        generation++;
    }
}

void final_report() {
    FILE *pf;
    char name[50];
    double sum[total_task_num][MAX_GEN / RECORD_FRE + 1];
    int i, j, l;

    for (i = 0; i < task_num; i++) {
        sprintf(name, "./Result/30 RUNS results for task %d.txt", i + 1);
        fopen(name, "w");
        for (j = 0; j < RUNS; j++) {
            if (j < RUNS - 1)
                fprintf(pf, "%lf,", fbest_value[i][MAX_GEN / RECORD_FRE][j]);
            else
                fprintf(pf, "%lf", fbest_value[i][MAX_GEN / RECORD_FRE][j]);
        }
        fclose(pf);
    }

    for (i = 0; i < task_num; i++)
        for (j = 0; j <= MAX_GEN / RECORD_FRE; j++) sum[i][j] = 0;

    for (i = 0; i <= MAX_GEN / RECORD_FRE; i++) {
        for (j = 0; j < RUNS; j++) {
            for (l = 0; l < task_num; l++) {
                sum[l][i] += fbest_value[l][i][j];
            }
        }
    }

    fopen("./Result/final results.txt", "w");
    for (i = 0; i < task_num; i++) {
        fprintf(pf, "task%d:%lf\n", i + 1, sum[i][MAX_GEN / RECORD_FRE] / RUNS);
    }
    fclose(pf);

    sprintf(name, "./Result/Convergence Curve.txt");
    fopen(name, "w");
    for (i = 0; i <= MAX_GEN / RECORD_FRE; i++) {
        for (j = 0; j < task_num; j++) fprintf(pf, "%lf\t", sum[j][i] / RUNS);

        fprintf(pf, "\n");
    }
    fclose(pf);

    for (i = 0; i < task_num; i++) {
        sprintf(name, "./Result/TLC record for task%d.txt", i + 1);
        fopen(name, "w");
        for (j = 0; j < MAX_GEN / RECORD_FRE; j++) {
            fprintf(pf, "GEN %d ~ %d: ", j * RECORD_FRE, (j + 1) * RECORD_FRE);
            for (l = 0; l < task_num; l++) {
                if (l != i)
                    fprintf(pf, "task%d: %lf\t", l + 1,
                            (double)TLC_record[i][j][l] / RUNS);
            }
            fprintf(pf, "\n");
        }
        fclose(pf);
    }
}

int main(int argc, char *argv[]) {
    double duration;
    double total = 0;

    int k = 0;
    // Set task number
    task_num = total_task_num;
    for (job = 0; job < RUNS; job++) {
        printf("\njob = %d\n", job);
        srand(job);
        MaTDE();
    }
    final_report();

    return 0;
}
