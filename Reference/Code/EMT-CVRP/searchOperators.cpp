#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include "functions.h"
#include <time.h>


void population_sorting(delimiter_individual *population, int popsize)
{
//	delimiter_individual tmp_chro;
//	for (int i = 0; i < popsize-1; i++)
//	{
//		for (int j = i+1; j < popsize; j++)
//		{
//			if (population[j].fitness < population[i].fitness)
//			{
//				del_indi_copy(&tmp_chro, &population[i]);
//				del_indi_copy(&population[i], &population[j]);
//				del_indi_copy(&population[j], &tmp_chro);
//			}
//		}
//	}
	std::sort(population, population + popsize);
}

void simple_xover(undelimiter_individual *c, undelimiter_individual *p1, undelimiter_individual *p2)
{
	int a, b;
	int i, j, k;
	int seq1[2*VERTEX_NUMBER], seq2[2*VERTEX_NUMBER];

	memcpy(seq1, p1->sequence, sizeof(p1->sequence));
	memcpy(seq2, p2->sequence, sizeof(p2->sequence));

	int length = p1->count;

	a = rand_choose(length);
	b = rand_choose(length);
	if (a > b)
	{
		int tmp = a;
		a = b;
		b = tmp;
	}
	int tem;
	memcpy(c->sequence, p2->sequence, sizeof(p2->sequence));
	c->count=p2->count;
	for(i=a;i<=b;i++){
		tem=seq1[i];
		c->sequence[i]=seq1[i];
	}
}

void ordered_xover(undelimiter_individual *c, undelimiter_individual *p1, undelimiter_individual *p2)
{
	int a, b;
	int i, j, k;
	int seq1[2*VERTEX_NUMBER], seq2[2*VERTEX_NUMBER];
	int count1=p1->count,count2=p2->count;
	undelimiter_individual temp_c1;
	undelimiter_individual temp_c2;

	int length = p1->count;
	int length1=length/2;

	/* 随机选取一段[a,b],作为要保留的染色体段*/
	a = rand_choose(length);
	b = (a+1+rand_choose(length1))%length;

	if (a > b)
	{
		int tmp = a;
		a = b;
		b = tmp;
	}
	if((b-a+1)==length)a++;

	int tem;



	//操作p1
	memcpy(seq1, p1->sequence, sizeof(p1->sequence));
	memcpy(seq2, p2->sequence, sizeof(p2->sequence));
	memcpy(temp_c1.sequence, p1->sequence, sizeof(p1->sequence));
	temp_c1.count=p1->count;


	/* 将p1中要保留的对应染色体序号从p2中删去 */
	for(i=a;i<=b;i++){
		tem=seq1[i];
		temp_c1.sequence[i]=seq1[i];
		int index = find_element(seq2, seq1[i], count2);
		count2=delete_element(seq2,index,count2);
	}
	/* 将p2剩下的染色体序号移位后，插入到p1中，从后半段到前半段 */
	int offset=count2-(b+1)%count2+1;
	for(int i=0;i<count2;i++)
		temp_c1.sequence[(b+i+1)%count1]=seq2[(offset+i)%count2];

	//操作p2，同理...
	memcpy(seq1, p1->sequence, sizeof(p1->sequence));
	memcpy(seq2, p2->sequence, sizeof(p2->sequence));
	memcpy(temp_c2.sequence, p2->sequence, sizeof(p2->sequence));
	temp_c2.count=p2->count;
	count1=p1->count,count2=p2->count;

	for(i=a;i<=b;i++){
		tem=seq2[i];
		temp_c2.sequence[i]=seq2[i];

		int index = find_element(seq1,seq2[i],count1);
		count1=delete_element(seq1,index,count1);
	}

	/* 将p2剩下的染色体序号移位后，插入到p1中，从后半段到前半段 */
	offset=count1-(b+1)%count1+1;
	for(int i=0;i<count1;i++)
		temp_c2.sequence[(b+i+1)%count2]=seq1[(offset+i)%count1];

	/* 从两个child中任选一个给c */
	int select=rand_choose(2);
	if(select)
		undel_indi_copy(c, &temp_c1);
	else
		undel_indi_copy(c, &temp_c2);

}

void binary_tournament(undelimiter_individual *p1, undelimiter_individual *p2, int popsize, undelimiter_individual *chro)
{
	int k1, k2, selk;


	k1 = rand_choose(popsize);
	k2 = rand_choose(popsize);
	if (k1 < k2)
	{
		selk = k1;
	}
	else
	{
		selk = k2;
	}
	undel_indi_copy(p1, &chro[selk]);
	k1 = rand_choose(popsize);
	k2 = rand_choose(popsize);
	if (k1 < k2)
	{
		selk = k1;
	}
	else
	{
		selk = k2;
	}
	undel_indi_copy(p2, &chro[selk]);

}

void local_search(delimiter_individual *del, Problem &problem){
	int sequence[2*VERTEX_NUMBER];
	float service_time[2*VERTEX_NUMBER];
	int count=del->count;
	float current_fitness,best_fitness;


	int u,v,x,y;
	int mark=0,improved=0;

	while(1){
		memcpy(sequence,del->sequence,sizeof(sequence));
		best_fitness=del->fitness;
		for(int i=0;i<(count-1);i++){
			u=sequence[i];
			x=sequence[i+1];
			if(sequence[i]==DEPOT){
				if(i==(count-2))mark=1;
				continue;
			}

			for(int j=0;j<(count-1);j++){
				if(j==i)continue;
				v=sequence[j];y=sequence[j+1];
				/*If u is a client node, remove u then insert it after v*/
				if(j>i){
					count=add_element(sequence,u,j+1,count);
					count=delete_element(sequence,i,count);
				}
				if(j<i){
					count=delete_element(sequence,i,count);
					count=add_element(sequence,u,j+1,count);
				}
				if(evaluate_load(sequence,count,problem)&&evaluate_route_time(sequence,count,problem)){
							current_fitness=caculate_fitness(sequence,count,problem);
					if(current_fitness<best_fitness){
						improved=1;
						break;
					}
				}
				memcpy(sequence,del->sequence,sizeof(sequence));

				/*If u and v are clients, swap u and v*/
				if(v!=DEPOT){
					swap_element(sequence,i,j);
					if(evaluate_load(sequence,count,problem)&&evaluate_route_time(sequence,count,problem)){
							current_fitness=caculate_fitness(sequence,count,problem);
						if(current_fitness<best_fitness){
							improved=1;
							break;
						}
					}
					memcpy(sequence,del->sequence,sizeof(sequence));
				}

				if((i+1)!=j && x!=DEPOT) { //保证x和v不是同一个点
					/*If u and x are clients, remove them then insert (u, x) after v*/
					if(i<j){
						count=add_element(sequence,u,j+1,count);
						count=add_element(sequence,x,j+2,count);
						count=delete_element(sequence,i+1,count);
						count=delete_element(sequence,i,count);
					}
					if(i>j){
						count=delete_element(sequence,i+1,count);
						count=delete_element(sequence,i,count);
						count=add_element(sequence,u,j+1,count);
						count=add_element(sequence,x,j+2,count);
					}
					if(evaluate_load(sequence,count,problem)&&evaluate_route_time(sequence,count,problem)){
							current_fitness=caculate_fitness(sequence,count,problem);
						if(current_fitness<best_fitness){
							improved=1;
							break;
						}
					}
					memcpy(sequence,del->sequence,sizeof(sequence));
					/*If u and x are clients, remove them then insert (x, u) after v 反向基本上会失败，先不实现*/
					if(i<j){
						count=add_element(sequence,x,j+1,count);
						count=add_element(sequence,u,j+2,count);
						count=delete_element(sequence,i+1,count);
						count=delete_element(sequence,i,count);
					}
					if(i>j){
						count=delete_element(sequence,i+1,count);
						count=delete_element(sequence,i,count);
						count=add_element(sequence,x,j+1,count);
						count=add_element(sequence,u,j+2,count);
					}
					if(evaluate_load(sequence,count,problem)&&evaluate_route_time(sequence,count,problem)){
							current_fitness=caculate_fitness(sequence,count,problem);
						if(current_fitness<best_fitness){
							improved=1;
							break;
						}
					}
					memcpy(sequence,del->sequence,sizeof(sequence));

					/*If u, x and v are clients, swap (u,x) and v*/
					if(v!=DEPOT){
						swap_element(sequence,i,j);
						if(i<j){
							count=add_element(sequence,x,j+1,count);
							count=delete_element(sequence,i+1,count);
						}
						if(i>j){
							count=delete_element(sequence,i+1,count);
							count=add_element(sequence,x,j+1,count);
						}
						if(evaluate_load(sequence,count,problem)&&evaluate_route_time(sequence,count,problem)){
							current_fitness=caculate_fitness(sequence,count,problem);
							if(current_fitness<best_fitness){
								improved=1;
								break;
							}
						}
						memcpy(sequence,del->sequence,sizeof(sequence));
					}

					/*If (u, x) and (v, y) are clients, swap (u, x) and (v, y)*/
					if(v!=DEPOT && y!=DEPOT){
						swap_element(sequence,i,j);
						swap_element(sequence,i+1,j+1);
						if(evaluate_load(sequence,count,problem)&&evaluate_route_time(sequence,count,problem)){
							current_fitness=caculate_fitness(sequence,count,problem);
							if(current_fitness<best_fitness){

								improved=1;
								break;
							}
						}
						memcpy(sequence,del->sequence,sizeof(sequence));
					}

					/*replace (u, x) and (v, y) by (u, v) and (x, y)*/
					if(v!=DEPOT && y!=DEPOT){
						swap_element(sequence,i+1,j);
						if(evaluate_load(sequence,count,problem)&&evaluate_route_time(sequence,count,problem)){
							current_fitness=caculate_fitness(sequence,count,problem);
							if(current_fitness<best_fitness){
								improved=1;
								break;
							}
						}
						memcpy(sequence,del->sequence,sizeof(sequence));
					}

					/*replace (u, x) and (v, y) by (u, y) and (x, v)*/
					if(v!=DEPOT && y!=DEPOT){
						swap_element(sequence,i+1,j+1);
						swap_element(sequence,j,j+1);
						if(evaluate_load(sequence,count,problem)&&evaluate_route_time(sequence,count,problem)){
							current_fitness=caculate_fitness(sequence,count,problem);
							if(current_fitness<best_fitness){
								improved=1;
								break;
							}
						}
						memcpy(sequence,del->sequence,sizeof(sequence));
					}
				}

				/*2-opt*: interchange the last parts of two trips */
				if(v!=DEPOT){
					bool in_same_route=true;
					if(j>i){
						for(int k=i;k<j;k++)
							if(sequence[k]==DEPOT){
								in_same_route=false;
								break;
						}
					}
					if(j<i){
						for(int k=j;k<i;k++)
							if(sequence[k]==DEPOT){
								in_same_route=false;
								break;
						}
					}

					if(!in_same_route){
						int iu=i;int iv=j;
						while(sequence[iu]!=DEPOT&&sequence[iv]!=DEPOT){
							swap_element(sequence,iu,iv);
							iu++;
							iv++;
						}
						if(sequence[iu]!=DEPOT){
							int sqiu;
							while(sequence[iu]!=DEPOT){
								sqiu=sequence[iu];
								if(j>i){
									count=add_element(sequence,sqiu,iv,count);
									count=delete_element(sequence,iu,count);}
								if(j<i){
									count=delete_element(sequence,iu,count);
									count=add_element(sequence,sqiu,iv,count);
									iu++;
									iv++;
								}
							}
						}
						if(sequence[iv]!=DEPOT){
							int sqiv;
							while(sequence[iv]!=DEPOT){
								sqiv=sequence[iv];
								if(j>i){
									count=delete_element(sequence,iv,count);
									count=add_element(sequence,sqiv,iu,count);
									iu++;
									iv++;
								}
								if(j<i){
									count=add_element(sequence,sqiv,iu,count);
									count=delete_element(sequence,iv,count);
									}
							}
						}
						if(evaluate_load(sequence,count,problem)&&evaluate_route_time(sequence,count,problem)){
							current_fitness=caculate_fitness(sequence,count,problem);
							if(current_fitness<best_fitness){
								improved=1;
								break;
							}
						}
						memcpy(sequence,del->sequence,sizeof(sequence));
					}
				}

			}

			if(improved){
				improved=0;
				memcpy(del->sequence,sequence,sizeof(sequence));
				del->fitness=current_fitness;
				break;
			}
			if(i==(count-2)){
				mark=1;
			}
		}
		if(mark)
			break;
	}

}


void local_search_v2(delimiter_individual *del, Problem &problem, int op){
	int current_fitness;
	int search_fitness;
    int count = 0;
//    printf("op = %d\n", op);
    while(++count <= OUT_LS_LIMIT){
//        printf("count = %d\n", count);
        current_fitness=del->fitness;
        replace(del,problem);
        if(del->fitness<current_fitness){
            search_fitness=del->fitness;
            continue;
        }

        if(op != 1) {
            single_insertion(del,problem);
            if(del->fitness<current_fitness){
                search_fitness=del->fitness;
                continue;
            }

            two_two_swap(del,problem);
            if(del->fitness<current_fitness){
                search_fitness=del->fitness;
                continue;
            }
        }
        break;

    }

//    if(yes) {
//        puts("--------------------");
//        printf("count: %d\n", del->count);
//        print_one_dim_array(del->sequence, del->count);
//        printf("customer: %d  factor: %d\n", problem.customer_size, del->mfo_skill_factor);
//        puts("--------------------");
//        system("pause");
//    }
}




