#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "functions.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void undel_indi_copy(undelimiter_individual *target,
                     undelimiter_individual *source) {
    memcpy(target->sequence, source->sequence, sizeof(source->sequence));
    memcpy(target->fitness, source->fitness, sizeof(source->fitness));
    memcpy(target->fRank, source->fRank, sizeof(source->fRank));
    target->count = source->count;
    target->nums_of_vehicle = source->nums_of_vehicle;
    target->scalar_fitness = source->scalar_fitness;
    target->skill_factor = source->skill_factor;
}

void del_indi_copy(delimiter_individual *target, delimiter_individual *source) {
    memcpy(target->sequence, source->sequence, sizeof(source->sequence));
    memcpy(target->fitness, source->fitness, sizeof(source->fitness));
    memcpy(target->service_time, source->service_time,
           sizeof(source->service_time));
    target->count = source->count;
    target->nums_of_vehicle = source->nums_of_vehicle;
}

void indi_to_chro(delimiter_individual *indi, undelimiter_individual *chro) {
    memcpy(chro->sequence, indi->sequence, sizeof(indi->sequence));
    memcpy(chro->fitness, indi->fitness, sizeof(indi->fitness));
    chro->count = indi->count;
    chro->nums_of_vehicle = indi->nums_of_vehicle;
    chro->count = remove_task_seq_delimiters(chro->sequence, chro->count);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int remove_task_seq_delimiters(int *task_seq, int count) {
    for (int i = count - 1; i >= 0; i--) {
        if (task_seq[i] == DEPOT) {
            delete_element(task_seq, i, count);
            count--;
        }
    }
    return count;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void print_one_dim_array_float(float *a, int count) {
    for (int i = 0; i < count; i++) {
        printf("%f ", a[i]);
    }
    printf("\n");
}

void print_one_dim_array(int *a, int count) {
    for (int i = 0; i < count; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int rand_choose(int num) {
    int k = rand() % num;
    // if(k==24){
    //
    //	printf("24£¡num=%d",num);
    //}

    return k;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int find_element(int *a, int ele, int count) {
    for (int i = 0; i < count; i++)
        if (a[i] == ele) return i;
    return NULL;
}

int delete_element(int *a, int pos, int count) {
    count--;
    for (int i = pos; i < count; i++) {
        a[i] = a[i + 1];
    }
    return count;
}

int add_element_float(float *a, float e, int pos, int count) {
    if (count == 0) {
        a[0] = e;
        return ++count;
    }

    for (int i = count; i > pos; i--) {
        a[i] = a[i - 1];
    }

    count++;
    a[pos] = e;

    return count;
}

int add_element(int *a, int e, int pos, int count) {
    if (count == 0) {
        a[0] = e;
        return ++count;
    }

    for (int i = count; i > pos; i--) {
        a[i] = a[i - 1];
    }

    count++;
    a[pos] = e;

    return count;
}

void swap_element(int *sequence, int pos1, int pos2) {
    int temp;

    temp = sequence[pos1];

    sequence[pos1] = sequence[pos2];
    sequence[pos2] = temp;
}

float abs_float(float a, float b) {
    if (a > b)
        return a - b;
    else
        return b - a;
}

int get_min_element(int *seq, int count) {
    int min = seq[0];
    for (int i = 0; i < count; i++) {
        if (seq[i] < min) min = seq[i];
    }

    return min;
}
int get_min_index(int *seq, int count) {
    int min = seq[0];
    int index = 0;
    for (int i = 0; i < count; i++) {
        if (seq[i] < min) {
            min = seq[i];
            index = i;
        }
    }

    return index;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int caculate_vehicle_number(int *sequence, int count) {
    int vehicle_number = 0;
    for (int i = 0; i < count; i++)
        if (sequence[i] == DEPOT) vehicle_number++;

    return vehicle_number - 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void split_T1(delimiter_individual *del_indi, int *seq) {
    int count = vNumber[VRP_T1];
    int sequence[2 * VERTEX_NUMBER];
    sequence[0] = 0;
    for (int i = 0; i < count - 1; i++) sequence[i + 1] = seq[i];

    int tmp_seq[2 * VERTEX_NUMBER];
    int tmp_count;

    const int n = VERTEX_NUMBER;
    float v[n];
    int p[n];
    v[0] = 0;
    p[0] = 0;
    for (int i = 1; i < n; i++) v[i] = INT_MAX;

    float load, cost;
    int j;

    int selected;
    float dis;

    float arrived_time;
    float service_time;
    float wait_time;
    float leave_time;
    float route_time;

    for (int i = 1; i < vNumber[VRP_T1]; i++) {
        load = 0;
        cost = 0;

        service_time = 0;
        leave_time = 0;
        route_time = 0;
        selected = DEPOT;
        j = i;

        tmp_seq[0] = 0;
        tmp_seq[1] = 0;
        tmp_count = 2;

        while (j < vNumber[VRP_T1] && load <= max_capacity[VRP_T1] &&
               route_time <= customer_T1[DEPOT].due_date &&
               service_time <= customer_T1[selected].due_date) {
            selected = sequence[j];

            tmp_count =
                add_element(tmp_seq, selected, tmp_count - 1, tmp_count);

            load += customer_T1[sequence[j]].demand;
            if (i == j) {
                cost = choose_a_type_T1(load, tmp_seq, tmp_count);
                arrived_time = leave_time + travel_time_T1[DEPOT][sequence[j]];
            }

            else {
                cost = choose_a_type_T1(load, tmp_seq, tmp_count);
                arrived_time =
                    leave_time + travel_time_T1[sequence[j - 1]][sequence[j]];
            }

            wait_time =
                customer_T1[sequence[j]].ready_time > arrived_time
                    ? (customer_T1[sequence[j]].ready_time - arrived_time)
                    : 0;
            service_time = arrived_time + wait_time;
            leave_time = service_time + customer_T1[sequence[j]].service_time;
            route_time = leave_time + travel_time_T1[DEPOT][sequence[j]];

            if (load <= max_capacity[VRP_T1] &&
                route_time <= customer_T1[DEPOT].due_date &&
                service_time <= customer_T1[sequence[j]].due_date) {
                if (v[i - 1] + cost < v[j]) {
                    v[j] = v[i - 1] + cost;
                    p[j] = i - 1;
                }
            }
            j++;
        }
    }

    int current_position = p[count - 1];
    while (current_position) {
        count = add_element(sequence, 0, current_position + 1, count);
        current_position = p[current_position];
    }
    count = add_element(sequence, 0, count, count);
    memcpy(del_indi->sequence, sequence, sizeof(sequence));
    del_indi->count = count;
    del_indi->fitness[VRP_T1] = v[vNumber[VRP_T1] - 1];
    del_indi->nums_of_vehicle =
        caculate_vehicle_number(del_indi->sequence, del_indi->count);

    caculate_service_time_T1(del_indi->sequence, del_indi->service_time,
                             del_indi->count);
}

void split_T2(delimiter_individual *del_indi, int *seq) {
    int count = vNumber[VRP_T2];
    int sequence[2 * VERTEX_NUMBER];
    sequence[0] = 0;
    for (int i = 0; i < count - 1; i++) sequence[i + 1] = seq[i];

    int tmp_seq[2 * VERTEX_NUMBER];
    int tmp_count;

    const int n = VERTEX_NUMBER;
    float v[n];
    int p[n];
    v[0] = 0;
    p[0] = 0;
    for (int i = 1; i < n; i++) v[i] = INT_MAX;

    float load, cost;
    int j;

    int selected;
    float dis;

    float arrived_time;
    float service_time;
    float wait_time;
    float leave_time;
    float route_time;

    for (int i = 1; i < vNumber[VRP_T2]; i++) {
        load = 0;
        cost = 0;
        service_time = 0;
        leave_time = 0;
        route_time = 0;
        selected = DEPOT;
        j = i;

        tmp_seq[0] = 0;
        tmp_seq[1] = 0;
        tmp_count = 2;

        while (j < vNumber[VRP_T2] && load <= max_capacity[VRP_T2] &&
               route_time <= customer_T2[DEPOT].due_date &&
               service_time <= customer_T2[selected].due_date) {
            selected = sequence[j];

            tmp_count =
                add_element(tmp_seq, selected, tmp_count - 1, tmp_count);

            load += customer_T2[sequence[j]].demand;
            if (i == j) {
                cost = choose_a_type_T2(load, tmp_seq, tmp_count);
                arrived_time = leave_time + travel_time_T2[DEPOT][sequence[j]];
            }

            else {
                cost = choose_a_type_T2(load, tmp_seq, tmp_count);
                arrived_time =
                    leave_time + travel_time_T2[sequence[j - 1]][sequence[j]];
            }

            wait_time =
                customer_T2[sequence[j]].ready_time > arrived_time
                    ? (customer_T2[sequence[j]].ready_time - arrived_time)
                    : 0;
            service_time = arrived_time + wait_time;
            leave_time = service_time + customer_T2[sequence[j]].service_time;
            route_time = leave_time + travel_time_T2[DEPOT][sequence[j]];

            if (load <= max_capacity[VRP_T2] &&
                route_time <= customer_T2[DEPOT].due_date &&
                service_time <= customer_T2[sequence[j]].due_date) {
                if (v[i - 1] + cost < v[j]) {
                    v[j] = v[i - 1] + cost;
                    p[j] = i - 1;
                }
            }
            j++;
        }
    }

    int current_position = p[count - 1];
    while (current_position) {
        count = add_element(sequence, 0, current_position + 1, count);
        current_position = p[current_position];
    }
    count = add_element(sequence, 0, count, count);
    memcpy(del_indi->sequence, sequence, sizeof(sequence));
    del_indi->count = count;
    del_indi->fitness[VRP_T2] = v[vNumber[VRP_T2] - 1];
    del_indi->nums_of_vehicle =
        caculate_vehicle_number(del_indi->sequence, del_indi->count);

    caculate_service_time_T2(del_indi->sequence, del_indi->service_time,
                             del_indi->count);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////new
void caculate_service_time_T1(int *sequence, float *stime, int count) {
    float arrived_time;
    float wait_time;
    float service_time;
    float leave_time;

    for (int i = 0; i < count; i++) {
        if (sequence[i] == DEPOT) {
            leave_time = 0;
            stime[i] = 0;
            continue;
        }
        arrived_time =
            travel_time_T1[sequence[i - 1]][sequence[i]] + leave_time;
        wait_time = customer_T1[sequence[i]].ready_time > arrived_time
                        ? (customer_T1[sequence[i]].ready_time - arrived_time)
                        : 0;
        service_time = arrived_time + wait_time;
        leave_time = service_time + customer_T1[sequence[i]].service_time;

        stime[i] = service_time;
    }
}

bool evaluate_service_time_T1(int *sequence, float *stime, int count) {
    for (int i = 0; i < count; i++)
        if (stime[i] > customer_T1[sequence[i]].due_date) return false;
    return true;
}

void caculate_service_time_T2(int *sequence, float *stime, int count) {
    float arrived_time;
    float wait_time;
    float service_time;
    float leave_time;

    for (int i = 0; i < count; i++) {
        if (sequence[i] == DEPOT) {
            leave_time = 0;
            stime[i] = 0;
            continue;
        }
        arrived_time =
            travel_time_T2[sequence[i - 1]][sequence[i]] + leave_time;
        wait_time = customer_T2[sequence[i]].ready_time > arrived_time
                        ? (customer_T2[sequence[i]].ready_time - arrived_time)
                        : 0;
        service_time = arrived_time + wait_time;
        leave_time = service_time + customer_T2[sequence[i]].service_time;

        stime[i] = service_time;
    }
}

bool evaluate_service_time_T2(int *sequence, float *stime, int count) {
    for (int i = 0; i < count; i++)
        if (stime[i] > customer_T2[sequence[i]].due_date) return false;
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////new

bool evaluate_load_T1(int *sequence, int count) {
    float load = 0;
    for (int i = 0; i < count; i++) {
        if (sequence[i] == 0) {
            load = 0;
        } else
            load += customer_T1[sequence[i]].demand;
        if (load > max_capacity[VRP_T1]) return false;
    }

    return true;
}

bool evaluate_load_T2(int *sequence, int count) {
    float load = 0;
    for (int i = 0; i < count; i++) {
        if (sequence[i] == 0) {
            load = 0;
        } else
            load += customer_T2[sequence[i]].demand;
        if (load > max_capacity[VRP_T2]) return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////new

float caculate_fitness_T1(int *sequence, int count) {
    float fitness = 0;
    float dist;
    float demand;
    int current_type;

    int tmp_seq[2 * VERTEX_NUMBER];
    int tmp_count;

    float total = 0;
    float totalfix = 0;

    int i = 1;
    while (i < count) {
        tmp_seq[0] = 0;
        tmp_seq[1] = 0;
        tmp_count = 2;

        demand = 0;
        dist = 0;

        int j;
        for (j = i; j < count; j++) {
            demand += customer_T1[sequence[j]].demand;
            if (sequence[j] == DEPOT) break;
            tmp_count =
                add_element(tmp_seq, sequence[j], tmp_count - 1, tmp_count);
        }

        i = j + 1;
        if (demand != 0) {
            fitness += choose_a_type_T1(demand, tmp_seq, tmp_count);
        }
    }

    return fitness;
}

float caculate_fitness_T2(int *sequence, int count) {
    float fitness = 0;
    float dist;
    float demand;
    int current_type;

    int tmp_seq[2 * VERTEX_NUMBER];
    int tmp_count;

    float total = 0;
    float totalfix = 0;

    int i = 1;
    while (i < count) {
        tmp_seq[0] = 0;
        tmp_seq[1] = 0;
        tmp_count = 2;

        demand = 0;
        dist = 0;

        int j;
        for (j = i; j < count; j++) {
            demand += customer_T2[sequence[j]].demand;
            if (sequence[j] == DEPOT) break;
            tmp_count =
                add_element(tmp_seq, sequence[j], tmp_count - 1, tmp_count);
        }

        i = j + 1;
        if (demand != 0) {
            fitness += choose_a_type_T2(demand, tmp_seq, tmp_count);
        }
    }

    return fitness;
}

float choose_a_type_T1(float route_demand, int *temseq, int count) {
    float off_dis = 0;
    float pri_dis = 0;
    int official_type = type_number[VRP_T1], private_type = type_number[VRP_T1];
    float official_cost, private_cost;
    int i;

    for (i = 0; i < type_number[VRP_T1]; i++)
        if (route_demand <= vehicle_type_T1[i].capacity &&
            vehicle_type_T1[i].type == 0) {
            official_type = i;
            break;
        }

    for (i = 0; i < type_number[VRP_T1]; i++)
        if (route_demand <= vehicle_type_T1[i].capacity &&
            vehicle_type_T1[i].type == 1) {
            if (evaluate_vw_T1(i, temseq, count)) {
                private_type = i;
                break;
            }
        }
    for (int i = 1; i < count; i++) {
        off_dis += distance_T1[temseq[i - 1]][temseq[i]];
        if (i < count - 1) pri_dis += distance_T1[temseq[i - 1]][temseq[i]];
    }
    official_cost = vehicle_type_T1[official_type].fix_cost +
                    vehicle_type_T1[official_type].varible_cost * off_dis;
    if (private_type == type_number[VRP_T1])
        return official_cost;
    else {
        private_cost = vehicle_type_T1[private_type].fix_cost +
                       vehicle_type_T1[private_type].varible_cost * pri_dis;
        if (official_cost <= private_cost)
            return official_cost;
        else {
            return private_cost;
        }
    }
}

float choose_a_type_T2(float route_demand, int *temseq, int count) {
    float off_dis = 0;
    float pri_dis = 0;
    int official_type = type_number[VRP_T2], private_type = type_number[VRP_T2];
    float official_cost, private_cost;
    int i;

    for (i = 0; i < type_number[VRP_T2]; i++)
        if (route_demand <= vehicle_type_T2[i].capacity &&
            vehicle_type_T2[i].type == 0) {
            official_type = i;
            break;
        }

    for (i = 0; i < type_number[VRP_T2]; i++)
        if (route_demand <= vehicle_type_T2[i].capacity &&
            vehicle_type_T2[i].type == 1) {
            if (evaluate_vw_T2(i, temseq, count)) {
                private_type = i;
                break;
            }
        }
    for (int i = 1; i < count; i++) {
        off_dis += distance_T2[temseq[i - 1]][temseq[i]];
        if (i < count - 1) pri_dis += distance_T2[temseq[i - 1]][temseq[i]];
    }
    official_cost = vehicle_type_T2[official_type].fix_cost +
                    vehicle_type_T2[official_type].varible_cost * off_dis;
    if (private_type == type_number[VRP_T2])
        return official_cost;
    else {
        private_cost = vehicle_type_T2[private_type].fix_cost +
                       vehicle_type_T2[private_type].varible_cost * pri_dis;
        if (official_cost <= private_cost)
            return official_cost;
        else {
            return private_cost;
        }
    }
}

bool evaluate_vw_T1(int type, int *temseq, int count) {
    float arrived_time;
    float service_time;
    float wait_time;
    float leave_time;

    leave_time = vehicle_type_T1[type].vetime;

    for (int j = 1; j < count; j++) {
        arrived_time = leave_time + travel_time_T1[temseq[j - 1]][temseq[j]];
        wait_time = customer_T1[temseq[j]].ready_time > arrived_time
                        ? (customer_T1[temseq[j]].ready_time - arrived_time)
                        : 0;
        service_time = arrived_time + wait_time;
        leave_time = service_time + customer_T1[temseq[j]].service_time;
        if (service_time > customer_T1[temseq[j]].due_date) return false;
    }
    if (arrived_time <= vehicle_type_T1[type].vltime &&
        arrived_time <= customer_T1[DEPOT].due_date) {
        return true;
    } else
        return false;
}

bool evaluate_vw_T2(int type, int *temseq, int count) {
    float arrived_time;
    float service_time;
    float wait_time;
    float leave_time;

    leave_time = vehicle_type_T2[type].vetime;

    for (int j = 1; j < count; j++) {
        arrived_time = leave_time + travel_time_T2[temseq[j - 1]][temseq[j]];
        wait_time = customer_T2[temseq[j]].ready_time > arrived_time
                        ? (customer_T2[temseq[j]].ready_time - arrived_time)
                        : 0;
        service_time = arrived_time + wait_time;
        leave_time = service_time + customer_T2[temseq[j]].service_time;
        if (service_time > customer_T2[temseq[j]].due_date) return false;
    }
    if (arrived_time <= vehicle_type_T2[type].vltime &&
        arrived_time <= customer_T2[DEPOT].due_date) {
        return true;
    } else
        return false;
}