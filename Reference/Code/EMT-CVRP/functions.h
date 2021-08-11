#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <armadillo>
using namespace arma;

#define DEPOT 0

#define EX_TIME 2

/*Memetic*/
#define MEMETIC_TIME_ADD 0
#define ITA 2500
#define COST_SPACE 0.2
#define NP 2
#define NC 10
#define GNUMBER ITA*NP/POP_SIZE
#define MAX_VALUE 99999
/*Transfer 参数*/

const int large_scale = true;
const int SINGEL = 0;
const int DOUBLE = 1;
const float MAX_FLOAT = 10000000.0;
const int MUTATION_SIZE = 5;
const float RMP = 0.7;
const float PLS = 0.1;
const int TASK_NUMBER = 2;
const int MAX_INITAL = 10000;
//const float SEARCH_TIME = large_scale ? 2.0 : 10.0;
//const int MOST_INSERT = large_scale ? 15 : 15;
//const int MAX_CAPACITY = large_scale ? 800 : 220;
//const int VERTEX_NUMBER = large_scale ? 155 : 100;
//const int OUT_LS_LIMIT = large_scale ? 150 : 500;
//const int LS_LIMIT = large_scale ? 5000 : 999999;
const float SEARCH_TIME = large_scale ? 2.0 : 10.0;
const int MOST_INSERT = large_scale ? 20 : 16;
const int MAX_CAPACITY = large_scale ? 3500 : 360;
const int VERTEX_NUMBER = large_scale ? 280 : 100;
const int OUT_LS_LIMIT = large_scale ? 150 : 400;
const int LS_LIMIT = large_scale ? 5000 : 999999;

const int POP_SIZE = 50;
const float EXPAND_RATE = 10;
const float BIG_DIS = 100 * EXPAND_RATE;
const float EPS = 0.001;

const int TRANSFER_SPEED = 5; // interval
const int TRANSFER_SIZE = 5; // size


const int FILE_SIZE_A = 27;
const int FILE_SIZE_P = 24;
const int FILE_SIZE_B = 23;
const int FILE_SIZE_K = 7;
const int FILE_SIZE_S = 15;
const int FILE_SIZE_SC = 27;
const int FILE_SIZE_R = 2;
const int GROUP_SIZE = 2;
const int RUN_TIME = 20;
const int RANDOM_SIZE = 18;
typedef struct vertex{
	//int number;
	float x;
	float y;
	float demand;
	/*float ready_time;
	float due_date;
	float service_time;*/
}vertex;

typedef struct undelimiter_individual
{
	int sequence[2*VERTEX_NUMBER];
	int count;

	int nums_of_vehicle;
	float fitness;


} undelimiter_individual;

typedef struct delimiter_individual
{
	int sequence[2*VERTEX_NUMBER];
	float service_time[2*VERTEX_NUMBER];
	int count;

	float fitness;
	int nums_of_vehicle;

	bool operator< (const delimiter_individual &rhs) const {
        return fitness < rhs.fitness;
	}

} delimiter_individual;



void undel_indi_copy(undelimiter_individual *target, undelimiter_individual *source);
void del_indi_copy(delimiter_individual *target, delimiter_individual *source);

void print_one_dim_array(int *a,int count);

typedef struct removal_list{
	int sequence[100*VERTEX_NUMBER];
	int count;
} removal_list;

class Problem {

public:
    int customer_size;
    int vNumber;
    int capacity;
    float route_time;
    float drop_time;
    float optimal_val;
    float mean_x;
    float mean_y;
    int k_size;

    vertex *customer;  //需要服务的顾客集合
    float *travel_time[VERTEX_NUMBER];
    float *travel_cost[VERTEX_NUMBER];

    delimiter_individual *indi;
    undelimiter_individual *chro;
    mat customer_mat;
    mat original_dist;


    Problem() {
        for(int i = 0; i < VERTEX_NUMBER; ++i) {
            travel_time[i] = new float[VERTEX_NUMBER];
            travel_cost[i] = new float[VERTEX_NUMBER];
        }
        customer = new vertex[VERTEX_NUMBER];
        indi = new delimiter_individual[POP_SIZE];
        chro = new undelimiter_individual[POP_SIZE];
    }

    ~Problem() {
        for(int i = 0; i < VERTEX_NUMBER; ++i) {
            delete[] travel_time[i];
            delete[] travel_cost[i];
        }
        delete[] customer;
        delete[] indi;
        delete[] chro;
    }
//    void print(int print_size) {
//        for(int i = 0; i < min(POP_SIZE, print_size); ++i) {
//            printf("current %d chromesome:\n", i + 1);
//            for(int j = 0; j < indi[i].count; ++j) {
//                printf("%d ", indi[i].sequence[j]);
//            }
//            puts("");
//        }
//    }
};

extern std::string *input_files;
extern std::string mat_file_dir;


/* initialize.cpp */
void simple_initial(delimiter_individual *indi);
void advanced_initial(delimiter_individual *indi);
void random_initial(delimiter_individual *indi, Problem &problem);
void random_undel(undelimiter_individual &undel, int size);
void initializeProblem(Problem &problem, int current_size);
void repair(undelimiter_individual *undel);
Problem initializer(std::string input_file_name);
Problem MFOproblem_initialize(std::string input_file_name);

/* searchOperators.cpp */
void population_sorting(delimiter_individual *population, int popsize);
void simple_xover(undelimiter_individual *c, undelimiter_individual *p1, undelimiter_individual *p2);
void ordered_xover(undelimiter_individual *c, undelimiter_individual *p1, undelimiter_individual *p2);
void binary_tournament(undelimiter_individual *p1, undelimiter_individual *p2, int popsize, undelimiter_individual *chro);
int survivor_selection(delimiter_individual *indi,int popsize);
void regeneration(delimiter_individual *del,undelimiter_individual *undel);
void local_search(delimiter_individual *del, Problem &problem);

/* arrayOperations.cpp */
int count_zero(int *a, int count);
void indi_to_chro(delimiter_individual *indi, undelimiter_individual *chro);
int delete_individual(delimiter_individual *indi,int size,int pos);
int remove_task_seq_delimiters(int *task_seq,int count);

void print_one_dim_array_float(float *a,int count);
int rand_choose(int num);

int delete_element(int *a, int pos,int count);
int find_element(int *a, int ele,int count);
int add_element(int *a, int e, int pos,int count);
int add_element_float(float *a, float e, int pos,int count);
void swap_element(int *sequence,int pos1,int pos2);
float abs_float(float a, float b);

bool split(delimiter_individual *del_indi, undelimiter_individual *undel_indi, Problem &problem);
bool new_split(delimiter_individual *del_indi, undelimiter_individual *undel_indi, Problem &problem);

bool evaluate_load(int *sequence,int count, Problem &problem);
bool evaluate_route_time(int *sequence,int count, Problem &problem);
float caculate_fitness(int *sequence,int count, Problem &problem);
int caculate_vehicle_number(int *sequence,int count);

void matrixtest();

void local_search_v2(delimiter_individual *del,  Problem &problem, int op);
void single_insertion(delimiter_individual *del, Problem &problem);
void double_insertion(delimiter_individual *del, Problem &problem);
void one_one_swap(delimiter_individual *del,     Problem &problem);
void two_one_swap(delimiter_individual *del,     Problem &problem);
void two_two_swap(delimiter_individual *del,     Problem &problem);
void replace(delimiter_individual *del,          Problem &problem);
void diverse_replace(delimiter_individual *del,  Problem &problem);
void sr_2opt(delimiter_individual *del,          Problem &problem);


// MatrixOperations
mat autoEncoder(mat A, mat B);
mat getVertexMatrix(int customer_size, vertex *v, vertex *center);
mat getDisMat(int customer_size, delimiter_individual &chromosome);
mat getSquareMat(mat matrix);
float getPosRowSum(mat d, int pos);
float getPosColSum(mat d, int pos);
mat getMultiDimensionScaling(mat D);
void test_matrix();
undelimiter_individual kMeans(mat &data, int k, mat &original_dist);
void print_MDS(mat &res);
float calc_error(mat &F, mat &D);
mat standardization(mat &t);

// TransferOperations
undelimiter_individual transferOperation(delimiter_individual &ind, int customer_size, mat &M, mat &original_dist, int K);
undelimiter_individual selfInsertOperation(delimiter_individual &ind, int customer_size, mat &original_dist, int K);
float OPT(Problem &problem, undelimiter_individual &chromesome, int current_size, std::string problem_n, int op);

// Solvers
void solver(Problem &problem, std::string output_file_name, int ls, int rand_insert, int do_km, int output);
void operaitonProcess(Problem &problem, int current_size, std::string problem_n, int op);
void transferSolver(Problem &problem_1, Problem &problem_2, std::string output_file_name_1,
                    std::string output_file_name_2, int nls, int random_transfer, int f_i, int f_j, std::string mat_dir);
float add_to_problem(delimiter_individual &del_c, Problem &problem, int op);
// commons
void file_outputs(std::vector<float> &res, std::string file_name);
mat mat_read(int f1, int f2, int n, int m, const std::string &mat_file_dir);
int problem_match(Problem &problem, int except, std::string *input_files, int file_size);
Problem read_data(std::string input_file_name);
void file_output_mathces(std::vector< std::pair<int, int> > &matches, std::string file_name);
std::string nts(int number);
void check_bug(std::string message, undelimiter_individual *c);
delimiter_individual get_one_solution(Problem &problem);
void print_mat_int(mat &DL);
void print_mat_float(mat &DL);
void solution_output(delimiter_individual *del, std::string file_name);
void points_output(mat &points, std::string file_name);
void print_problem(Problem &problem);


#endif // FUNCTIONS_H_INCLUDED
