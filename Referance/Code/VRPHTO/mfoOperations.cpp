#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

void factorial_cost(int startPoint,int size){
	int seq[VERTEX_NUMBER];
		for(int i=0;i<TASK_NUMBER;i++)
			for(int j=startPoint;j<size;j++){
				memcpy(seq,chro[j].sequence,sizeof(seq));
				if(i==VRP_T1){
					decoding(seq,vNumber[VRP_T1]);	
					split_T1(&indi[j],seq);
					chro[j].fitness[VRP_T1]=indi[j].fitness[VRP_T1];
				}
				if(i==VRP_T2){
					decoding(seq,vNumber[VRP_T2]);
					split_T2(&indi[j],seq);
					chro[j].fitness[VRP_T2]=indi[j].fitness[VRP_T2];
				}
			}		

}
	
void factorial_rank(int size){		
	for(int i=0;i<TASK_NUMBER;i++){
		population_sorting(chro,size,i);
		for(int j=0;j<size;j++)
			chro[j].fRank[i]=j+1;			
	}
}

void scalar_fitness(int size){	
	int min_rank;
	for(int i=0;i<size;i++){
		min_rank=get_min_element(chro[i].fRank,TASK_NUMBER);
		chro[i].scalar_fitness=1.0/min_rank;
	}
}

void skill_factor(int startPoint,int size){	
	int min_index;
	for(int i=startPoint;i<size;i++){
		min_index=get_min_index(chro[i].fRank,TASK_NUMBER);
		chro[i].skill_factor=min_index;
		if(min_index==VRP_T2)
			chro[i].count=vNumber[VRP_T2]-1;
		if(min_index==VRP_T1)
			chro[i].count=vNumber[VRP_T1]-1;
	}		
}


void getType(int *typeList, undelimiter_individual c){
	delimiter_individual del;

	int count;
	float demand;

	int tmp_seq[2*VERTEX_NUMBER];
	int tmp_count;

	int i=1;
	if(c.skill_factor==VRP_T1){
		split_T1(&del,c.sequence);
		count=del.count;
		while(i<count){

			tmp_seq[0]=0;tmp_seq[1]=0;
			tmp_count=2;

			demand=0;

			int j;
			for(j=i;j<count;j++){
				demand+=customer_T1[del.sequence[j]].demand;
				if(del.sequence[j]==DEPOT)break;
				tmp_count=add_element(tmp_seq,del.sequence[j],tmp_count-1,tmp_count);
			}
		
			i=j+1;
			if(demand!=0){
				typeList[get_a_type_T1(demand,tmp_seq,tmp_count)]++;
			}
		}
	}
	else{
		split_T2(&del,c.sequence);
		count=del.count;
		while(i<count){

			tmp_seq[0]=0;tmp_seq[1]=0;
			tmp_count=2;

			demand=0;

			int j;
			for(j=i;j<count;j++){
				demand+=customer_T2[del.sequence[j]].demand;
				if(del.sequence[j]==DEPOT)break;
				tmp_count=add_element(tmp_seq,del.sequence[j],tmp_count-1,tmp_count);
			}
		
			i=j+1;
			if(demand!=0){
				typeList[get_a_type_T2(demand,tmp_seq,tmp_count)]++;
			}
		}
	}
}

int get_a_type_T1(float route_demand, int *temseq,int count){
	float off_dis=0;
	float pri_dis=0;
	int official_type=type_number[VRP_T1],private_type=type_number[VRP_T1];
	float official_cost,private_cost;
	int i;

	for(i=0;i<type_number[VRP_T1];i++)
		if(route_demand<=vehicle_type_T1[i].capacity&&vehicle_type_T1[i].type==0){
			official_type=i;
			break;
		}

	for(i=0;i<type_number[VRP_T1];i++)
		if(route_demand<=vehicle_type_T1[i].capacity&&vehicle_type_T1[i].type==1){
			if(evaluate_vw_T1(i, temseq,count)){
				private_type=i;
				break;
			}
		}
	for(int i=1;i<count;i++){
		off_dis+=distance_T1[temseq[i-1]][temseq[i]];
		if(i<count-1)
			pri_dis+=distance_T1[temseq[i-1]][temseq[i]];
	}
	official_cost=vehicle_type_T1[official_type].fix_cost+vehicle_type_T1[official_type].varible_cost*off_dis;
	if(private_type==type_number[VRP_T1])
		return official_type;
	else{
		private_cost=vehicle_type_T1[private_type].fix_cost+vehicle_type_T1[private_type].varible_cost*pri_dis;
		if(official_cost<=private_cost)
			return official_type;
		else{
			return private_type;
		}
	}
}

int get_a_type_T2(float route_demand, int *temseq,int count){
	float off_dis=0;
	float pri_dis=0;
	int official_type=type_number[VRP_T2],private_type=type_number[VRP_T2];
	float official_cost,private_cost;
	int i;

	for(i=0;i<type_number[VRP_T2];i++)
		if(route_demand<=vehicle_type_T2[i].capacity&&vehicle_type_T2[i].type==0){
			official_type=i;
			break;
		}

	for(i=0;i<type_number[VRP_T2];i++)
		if(route_demand<=vehicle_type_T2[i].capacity&&vehicle_type_T2[i].type==1){
			if(evaluate_vw_T2(i, temseq,count)){
				private_type=i;
				break;
			}
		}
	for(int i=1;i<count;i++){
		off_dis+=distance_T2[temseq[i-1]][temseq[i]];
		if(i<count-1)
			pri_dis+=distance_T2[temseq[i-1]][temseq[i]];
	}
	official_cost=vehicle_type_T2[official_type].fix_cost+vehicle_type_T2[official_type].varible_cost*off_dis;
	if(private_type==type_number[VRP_T2])
		return official_type;
	else{
		private_cost=vehicle_type_T2[private_type].fix_cost+vehicle_type_T2[private_type].varible_cost*pri_dis;
		if(official_cost<=private_cost)
			return official_type;
		else{
			return private_type;
		}
	}
}