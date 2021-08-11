#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "functions.h"
#include <time.h>

/*If u is a client node, remove u then insert it after v*/
void single_insertion(delimiter_individual *del, Problem &problem){
	float service_time[2*VERTEX_NUMBER];
	int sequence[2*VERTEX_NUMBER];
	int count=del->count;
	float current_fitness,best_fitness;

	int u;
	int mark=0,improved=0;
    int cnt = 0;
    clock_t startTime, endTime;
    startTime = clock();
	while(++cnt < LS_LIMIT){
        if(large_scale) {
            endTime = clock();
            if((double)(endTime - startTime) / CLOCKS_PER_SEC > SEARCH_TIME)
                break;
        }
		memcpy(sequence,del->sequence,sizeof(sequence));
		best_fitness=del->fitness;
		for(int i=0;i<(count-1);i++){
		    if(large_scale) {
                endTime = clock();
                if((double)(endTime - startTime) / CLOCKS_PER_SEC > SEARCH_TIME)
                    break;
            }
			u=sequence[i];
			if(sequence[i]==DEPOT){// 保证u不是DEPOT
				if(i==(count-2))mark=1;
				continue;
			}

			for(int j=0;j<(count-1);j++){
                if(large_scale) {
                    endTime = clock();
                    if((double)(endTime - startTime) / CLOCKS_PER_SEC > SEARCH_TIME)
                        break;
                }
				if(j==i)continue;
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

/*If u and x are clients, remove them then insert (u, x) after v*/
void double_insertion(delimiter_individual *del, Problem &problem){
	float service_time[2*VERTEX_NUMBER];
	int sequence[2*VERTEX_NUMBER];
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
				if((i+1)!=j && x!=DEPOT) { //保证x和v不是同一个点
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

/*If u and v are clients, swap u and v*/
void one_one_swap(delimiter_individual *del, Problem& problem){
	float service_time[2*VERTEX_NUMBER];
	int sequence[2*VERTEX_NUMBER];
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
				if(v!=DEPOT){
					swap_element(sequence,i,j);

					if(evaluate_load(sequence,count, problem)&&evaluate_route_time(sequence,count, problem)){
						current_fitness=caculate_fitness(sequence,count, problem);
						if(current_fitness<best_fitness){
							improved=1;
							break;
						}
					}
					memcpy(sequence,del->sequence,sizeof(sequence));
				}
			}
			if(improved){
				improved=0;
				memcpy(del->sequence,sequence,sizeof(sequence));
				del->fitness=current_fitness;

				break;
			}
		/*	printf("i=%d,count=:%d\n",i,count); */
			if(i==(count-2)){
				mark=1;
			}
		}
		if(mark)
			break;
	}
}

/*If u, x and v are clients, swap (u,x) and v*/
void two_one_swap(delimiter_individual *del, Problem &problem){
	float service_time[2*VERTEX_NUMBER];
	int sequence[2*VERTEX_NUMBER];
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
				if((i+1)!=j && x!=DEPOT) { //保证x和v不是同一个点
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

/*If (u, x) and (v, y) are clients, swap (u, x) and (v, y)*/
void two_two_swap(delimiter_individual *del, Problem &problem){
	float service_time[2*VERTEX_NUMBER];
	int sequence[2*VERTEX_NUMBER];
	int count=del->count;
	float current_fitness,best_fitness;

	int u,v,x,y;
	int mark=0,improved=0;
    int cnt = 0;
    clock_t startTime, endTime;
    startTime = clock();
	while(++cnt <= LS_LIMIT){
        if(large_scale) {
            endTime = clock();
            if((double)(endTime - startTime) / CLOCKS_PER_SEC > SEARCH_TIME)
                break;
        }
		memcpy(sequence,del->sequence,sizeof(sequence));
		best_fitness=del->fitness;
		for(int i=0;i<(count-1);i++){
		    if(large_scale) {
                endTime = clock();
                if((double)(endTime - startTime) / CLOCKS_PER_SEC > SEARCH_TIME)
                    break;
            }
			u=sequence[i];
			x=sequence[i+1];
			if(sequence[i]==DEPOT){
				if(i==(count-2))mark=1;
				continue;
			}

			for(int j=0;j<(count-1);j++){
                if(large_scale) {
                    endTime = clock();
                    if((double)(endTime - startTime) / CLOCKS_PER_SEC > SEARCH_TIME)
                        break;
                }
				if(j==i)continue;
				v=sequence[j];y=sequence[j+1];
				if((i+1)!=j && x!=DEPOT) { //保证x和v不是同一个点
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

/*replace (u, x) and (v, y) by (u, v) and (x, y)*/
void replace(delimiter_individual *del, Problem &problem){
	float service_time[2*VERTEX_NUMBER];
	int sequence[2*VERTEX_NUMBER];
	int count=del->count;
	float current_fitness,best_fitness;

	int u,v,x,y;
	int mark=0,improved=0;
	int cnt = 0;
    clock_t startTime,endTime;
    startTime = clock();
	while(++cnt < LS_LIMIT){
        if(large_scale) {
            endTime = clock();
            if((double)(endTime - startTime) / CLOCKS_PER_SEC > SEARCH_TIME)
                break;
        }
		memcpy(sequence,del->sequence,sizeof(sequence));
		best_fitness=del->fitness;
		for(int i=0;i<(count-1);i++){
            if(large_scale) {
                endTime = clock();
                if((double)(endTime - startTime) / CLOCKS_PER_SEC > SEARCH_TIME)
                    break;
            }
			u=sequence[i];
			x=sequence[i+1];
			if(sequence[i]==DEPOT){
				if(i==(count-2))mark=1;
				continue;
			}

			for(int j=0;j<(count-1);j++){
                if(large_scale) {
                    endTime = clock();
                    if((double)(endTime - startTime) / CLOCKS_PER_SEC > SEARCH_TIME)
                        break;
                }
				if(j==i)continue;
				v=sequence[j];y=sequence[j+1];
				if((i+1)!=j && x!=DEPOT) { //保证x和v不是同一个点
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

/*replace (u, x) and (v, y) by (u, y) and (x, v)*/
void diverse_replace(delimiter_individual *del, Problem &problem){
	float service_time[2*VERTEX_NUMBER];
	int sequence[2*VERTEX_NUMBER];
	int count=del->count;
	float current_fitness,best_fitness;

	int u,v,x,y;
	int mark=0,improved=0;
    clock_t startTime,endTime;
    startTime = clock();
	while(1){
        if(large_scale) {
            endTime = clock();
            if((double)(endTime - startTime) / CLOCKS_PER_SEC > 3)
                break;
        }
		memcpy(sequence,del->sequence,sizeof(sequence));
		best_fitness=del->fitness;
		for(int i=0;i<(count-1);i++){
            if(large_scale) {
                endTime = clock();
                if((double)(endTime - startTime) / CLOCKS_PER_SEC > 3)
                    break;
            }
			u=sequence[i];
			x=sequence[i+1];
			if(sequence[i]==DEPOT){
				if(i==(count-2))mark=1;
				continue;
			}

			for(int j=0;j<(count-1);j++){
                if(large_scale) {
                    endTime = clock();
                    if((double)(endTime - startTime) / CLOCKS_PER_SEC > 3)
                        break;
                }
				if(j==i)continue;
				v=sequence[j];y=sequence[j+1];
				if((i+1)!=j && x!=DEPOT) { //保证x和v不是同一个点
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

/*case 1:u前路径->u->x->x后路径,v前路径->v->y->y后路径，变为，u前路径->u->y->y后路径,v前路径->v->x->x后路径*/
void sr_2opt(delimiter_individual *del, Problem &problem){
	float service_time[2*VERTEX_NUMBER];
	int sequence[2*VERTEX_NUMBER];
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
				/*If u and v are clients, swap u and v*/
				if((i+1)!=j && x!=DEPOT && v!=DEPOT) { //保证x和v不是同一个点
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
						int sqiu,sqiv;
						while(sequence[iu]!=DEPOT&&sequence[iv]!=DEPOT){
							swap_element(sequence,iu,iv);
							iu++;
							iv++;
						}
						if(sequence[iu]!=DEPOT){
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
