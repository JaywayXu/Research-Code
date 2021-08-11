#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include "functions.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void undel_indi_copy(undelimiter_individual *target, undelimiter_individual *source)
{
	memcpy(target->sequence, source->sequence, sizeof(source->sequence));
	//memcpy(target->service_time, source->service_time, sizeof(source->service_time));
	target->count=source->count;
	target->fitness=source->fitness;
	target->nums_of_vehicle=source->nums_of_vehicle;
}

void del_indi_copy(delimiter_individual *target, delimiter_individual *source)
{
	memcpy(target->sequence, source->sequence, sizeof(source->sequence));
	target->count=source->count;
	target->fitness=source->fitness;
	target->nums_of_vehicle=source->nums_of_vehicle;
}

void indi_to_chro(delimiter_individual *indi, undelimiter_individual *chro){
	memcpy(chro->sequence,indi->sequence,sizeof(indi->sequence));
	chro->count=indi->count;
	chro->fitness=indi->fitness;
	chro->count=remove_task_seq_delimiters(chro->sequence,chro->count);
}
int delete_individual(delimiter_individual *indi,int size,int pos){
	for(int i=pos;i<size;i++)
		del_indi_copy(&indi[pos],&indi[pos+1]);

	return size-1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int remove_task_seq_delimiters(int *task_seq,int count)
{
	for (int i =count-1; i >=0; i--)
	{
		if (task_seq[i] == DEPOT){
			delete_element(task_seq, i,count);
			count--;
		}
	}
	return count;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void print_one_dim_array_float(float *a,int count){
	for (int i = 0; i <count; i++)
	{
		printf("%f ", a[i]);
	}
	printf("\n");
}
int count_zero(int *a, int count) {
    int res = -1;
    for(int i = 0; i < count; ++i) {
        if(abs(a[i]) < 0.1)
            res++;
    }
    return res;
}
void print_one_dim_array(int *a,int count)
{
	for (int i = 0; i <count; i++)
	{
		printf("%2d ", a[i]);
	}
	printf("\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int rand_choose(int num)
{

	int k = rand()%num;
	//if(k==24){
	//
	//	printf("24£¡num=%d",num);
	//}

	return k;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int find_element(int *a, int ele,int count){
	for(int i=0;i<count;i++)
		if(a[i]==ele)
			return i;
	return -1;
}

int delete_element(int *a, int pos,int count)
{
	if (pos < 0 || pos > count)
	{
	    printf("pos: %d\n", pos);
		printf("the deleting position is wrong!\n");
		exit(0);
	}

	count--;
	for (int i = pos; i < count; i++)
	{
		a[i] = a[i+1];
	}
	return count;
}

int add_element_float(float *a, float e, int pos,int count)
{
	if(count==0){
		a[0]=e;
		return ++count;
	}


	for (int i = count; i > pos; i--)
	{
		a[i] = a[i-1];
	}

	count++;
	a[pos] = e;

	return count;
}

int add_element(int *a, int e, int pos,int count)
{
	if(count==0){
		a[0]=e;
		return ++count;
	}


	for (int i = count; i > pos; i--)
	{
		a[i] = a[i-1];
	}

	count++;
	a[pos] = e;

	return count;
}

void swap_element(int *sequence,int pos1,int pos2){
	int temp;

	temp=sequence[pos1];

	sequence[pos1]=sequence[pos2];
	sequence[pos2]=temp;
}

float abs_float(float a, float b){
	if(a>b)return a-b;
	else return b-a;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
bool split(delimiter_individual *del_indi, undelimiter_individual *undel_indi, Problem &problem)
{
	int count=undel_indi->count+1;
	int sequence[2*VERTEX_NUMBER];
	sequence[0]=0;
	for(int i=0;i<undel_indi->count;i++)
		sequence[i+1]=undel_indi->sequence[i];

	const int n = VERTEX_NUMBER;

	float dis[n], load[n];
	dis[0] = 0;
	load[0] = 0;
	for(int i = 1; i < count; ++i) {
        dis[i] = dis[i-1] + problem.travel_cost[sequence[i]][sequence[i-1]];
        load[i] = load[i-1] + problem.customer[sequence[i]].demand;
	}
	float v[n][MOST_INSERT];
	int p[n][MOST_INSERT];
	for(int i = 0; i < n; ++i)
    for(int j = 0; j < MOST_INSERT; ++j)
		v[i][j]=p[i][j]=MAX_VALUE;
    for(int i = 0; i < MOST_INSERT; ++i)
        v[0][i] = p[0][i] = 0;

    for(int k = 1; k <= problem.k_size; k++)
	for(int j = 1; j < problem.vNumber; ++j) {
        for(int i = j; i > 0; --i) {
            if(load[j] - load[i-1] > problem.capacity)
                break;
            if(v[i-1][k-1] >= MAX_VALUE)
                continue;
            float change_dis = problem.travel_cost[DEPOT][sequence[i]] + dis[j] - dis[i] + problem.travel_cost[DEPOT][sequence[j]];
            if(change_dis + v[i-1][k-1] < v[j][k]) {
                v[j][k] = change_dis + v[i-1][k-1];
                p[j][k] = i-1;
            }
        }
	}
    int k_best = problem.k_size;
    int p_min = MAX_VALUE;
    for(int i = 1; i <= problem.k_size; ++i) {
        if(p_min > v[count-1][i]) {
            p_min = v[count-1][i];
            k_best = i;
        }
    }

	int current_position=p[count-1][k_best];

//	printf("%d  \n", current_position);
	while(current_position){
        if(current_position < 0 || current_position > n)
            return false;

		count=add_element(sequence,0,current_position+1,count);
		current_position=p[current_position][--k_best];
	}
	count=add_element(sequence,0,count,count);
	memcpy(del_indi->sequence,sequence,sizeof(sequence));
	del_indi->count=count;
	del_indi->fitness=p_min;
	del_indi->nums_of_vehicle=caculate_vehicle_number(del_indi->sequence,del_indi->count);
	return true;
}

bool new_split(delimiter_individual *del_indi, undelimiter_individual *undel_indi, Problem &problem) {
    int repair_time = 0;
    while(!split(del_indi, undel_indi, problem)) {
        ++repair_time;
        repair(undel_indi);
//        printf("repair_time: %d\n", repair_time);
        if(repair_time > problem.vNumber)
            return false;
    }
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool evaluate_load(int *sequence,int count, Problem &problem){
	int load=0;
	for(int i=0;i<count;i++){
		if(sequence[i]==0)load=0;
		else
			load+=problem.customer[sequence[i]].demand;
		if(load>problem.capacity)return false;
	}

	return true;

}

bool evaluate_route_time(int *sequence,int count, Problem &problem){
//	float rt=0;
//	for(int i=1;i<count;i++){
//		rt+=problem.travel_time[sequence[i-1]][sequence[i]]+problem.drop_time;
//		if(sequence[i]==0)rt-=problem.drop_time;
//		if(rt>problem.route_time)return false;
//		if(sequence[i]==0)rt=0;
//	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float caculate_fitness(int *sequence,int count, Problem &problem){
	float fitness=0;
	int vnumber=caculate_vehicle_number(sequence,count);
	for(int i=1;i<count;i++)
		fitness+=problem.travel_cost[sequence[i-1]][sequence[i]];

	fitness+=vnumber*MEMETIC_TIME_ADD;

	return fitness;
}

int caculate_vehicle_number(int *sequence,int count){
	int vehicle_number=0;
	for(int i=0;i<count;i++)
		if(sequence[i]==DEPOT)
			vehicle_number++;

	return vehicle_number-1;
}
