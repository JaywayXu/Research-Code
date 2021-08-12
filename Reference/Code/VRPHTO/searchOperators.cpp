#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "functions.h"

#define DOUBLE 0
#define SINGLE 1

void population_sorting(undelimiter_individual *population, int popsize,
                        int taskNumber) {
    undelimiter_individual tmp_chro;
    for (int i = 0; i < popsize - 1; i++) {
        for (int j = i + 1; j < popsize; j++) {
            if (population[j].fitness[taskNumber] <
                population[i].fitness[taskNumber]) {
                undel_indi_copy(&tmp_chro, &population[i]);
                undel_indi_copy(&population[i], &population[j]);
                undel_indi_copy(&population[j], &tmp_chro);
            }
        }
    }
}

void popSorting_by_scalarFitness(undelimiter_individual *population,
                                 int popsize) {
    undelimiter_individual tmp_chro;
    for (int i = 0; i < popsize - 1; i++) {
        for (int j = i + 1; j < popsize; j++) {
            if (population[j].scalar_fitness > population[i].scalar_fitness) {
                undel_indi_copy(&tmp_chro, &population[i]);
                undel_indi_copy(&population[i], &population[j]);
                undel_indi_copy(&population[j], &tmp_chro);
            }
        }
    }
}

void assortative_mating(undelimiter_individual *c1, undelimiter_individual *c2,
                        int current_size) {
    undelimiter_individual p1, p2;
    int type;
    binary_tournament(&p1, &p2, current_size);

    float ran = 1.0 * rand() / RAND_MAX;
    if (p1.skill_factor == p2.skill_factor || ran < RMP) {
        ordered_xover(c1, c2, &p1, &p2);
        type = DOUBLE;
    }

    else {
        mutation(&p1, c1);
        mutation(&p2, c2);
        type = SINGLE;
    }

    cultural_transmission(c1, c2, &p1, &p2, type);
}

void ordered_xover(undelimiter_individual *c1, undelimiter_individual *c2,
                   undelimiter_individual *p1, undelimiter_individual *p2) {
    int a, b;
    int i, j, k;
    int seq1[2 * VERTEX_NUMBER], seq2[2 * VERTEX_NUMBER];

    undelimiter_individual temp_c1;
    undelimiter_individual temp_c2;

    int length = vNumber[VRP_T1] > vNumber[VRP_T2] ? vNumber[VRP_T1] - 1
                                                   : vNumber[VRP_T2] - 1;
    int length1 = length / 2;

    a = rand_choose(length);
    b = (a + 1 + rand_choose(length1)) % length;

    if (a > b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    if ((b - a + 1) == length) a++;

    int tem;

    memcpy(seq1, p1->sequence, sizeof(p1->sequence));
    memcpy(seq2, p2->sequence, sizeof(p2->sequence));
    memcpy(temp_c1.sequence, p1->sequence, sizeof(p1->sequence));
    temp_c1.count = length;
    int count1 = length, count2 = length;

    for (i = a; i <= b; i++) {
        tem = seq1[i];
        count2 =
            delete_element(seq2, find_element(seq2, seq1[i], count2), count2);
    }

    int offset = count2 - (b + 1) % count2 + 1;
    for (int i = 0; i < count2; i++)
        temp_c1.sequence[(b + i + 1) % count1] = seq2[(offset + i) % count2];

    memcpy(seq1, p1->sequence, sizeof(p1->sequence));
    memcpy(seq2, p2->sequence, sizeof(p2->sequence));
    memcpy(temp_c2.sequence, p2->sequence, sizeof(p2->sequence));
    temp_c2.count = length;
    count1 = length, count2 = length;
    for (i = a; i <= b; i++) {
        tem = seq2[i];
        count1 =
            delete_element(seq1, find_element(seq1, seq2[i], count1), count1);
    }

    offset = count1 - (b + 1) % count1 + 1;
    for (int i = 0; i < count1; i++)
        temp_c2.sequence[(b + i + 1) % count2] = seq1[(offset + i) % count1];

    undel_indi_copy(c1, &temp_c1);
    undel_indi_copy(c2, &temp_c2);
}

void binary_tournament(undelimiter_individual *p1, undelimiter_individual *p2,
                       int popsize) {
    int k1, k2, selk;
    int candi1[T_SIZE], candi2[T_SIZE];
    int count1 = popsize, count2 = popsize;

    for (int i = 0; i < popsize; i++) {
        candi1[i] = i;
    }
    memcpy(candi2, candi1, sizeof(candi1));

    k1 = rand_choose(count1);
    k2 = rand_choose(count1);
    if (k1 < k2) {
        selk = k1;
    } else {
        selk = k2;
    }
    undel_indi_copy(p1, &chro[candi1[selk]]);
    count2 = delete_element(candi2, selk, count2);

    k1 = rand_choose(count2);
    k2 = rand_choose(count2);
    if (k1 < k2) {
        selk = k1;
    } else {
        selk = k2;
    }
    undel_indi_copy(p2, &chro[candi2[selk]]);
}

void mutation(undelimiter_individual *p, undelimiter_individual *c) {
    int pos1, pos2;
    int count;
    int seq[2 * VERTEX_NUMBER];
    memcpy(seq, p->sequence, sizeof(seq));
    count = vNumber[VRP_T1] > vNumber[VRP_T2] ? vNumber[VRP_T1] - 1
                                              : vNumber[VRP_T2] - 1;

    for (int i = 0; i < 1; i++) {
        pos1 = rand() % count;
        pos2 = rand() % count;
        while (pos1 == pos2) pos2 = rand() % count;

        swap_element(seq, pos1, pos2);
    }

    memcpy(c->sequence, seq, sizeof(seq));
    c->count = count;
}

void cultural_transmission(undelimiter_individual *c1,
                           undelimiter_individual *c2,
                           undelimiter_individual *p1,
                           undelimiter_individual *p2, int type) {
    delimiter_individual del_c1, del_c2;
    int seq1[VERTEX_NUMBER], seq2[VERTEX_NUMBER];

    if (type == DOUBLE) {
        float ran = 1.0 * rand() / RAND_MAX;
        if (ran < 0.5) {
            c1->skill_factor = p1->skill_factor;
            c2->skill_factor = p1->skill_factor;
        } else {
            c1->skill_factor = p2->skill_factor;
            c2->skill_factor = p2->skill_factor;
        }
    }
    if (type == SINGLE) {
        c1->skill_factor = p1->skill_factor;
        c2->skill_factor = p2->skill_factor;
    }

    get_decoding_split(c1, &del_c1);
    get_decoding_split(c2, &del_c2);

    clock_t lsstart;
    double random = 1.0 * rand() / RAND_MAX;
    if (random < PLS) {
        lsCount++;
        lsstart = clock();
        local_search(&del_c1, c1->skill_factor);
        local_search(&del_c2, c2->skill_factor);
        lsTime += (float)(clock() - lsstart) / CLOCKS_PER_SEC;
    }

    del_c1.count = remove_task_seq_delimiters(del_c1.sequence, del_c1.count);
    del_c2.count = remove_task_seq_delimiters(del_c2.sequence, del_c2.count);

    rebuilt_chrom(c1, &del_c1);
    rebuilt_chrom(c2, &del_c2);

    c1->fitness[c1->skill_factor] = del_c1.fitness[c1->skill_factor];
    c2->fitness[c2->skill_factor] = del_c2.fitness[c2->skill_factor];
}

void get_decoding_split(undelimiter_individual *c,
                        delimiter_individual *del_c) {
    int seq[VERTEX_NUMBER];
    memcpy(seq, c->sequence, sizeof(seq));

    if (c->skill_factor == VRP_T1) {
        decoding(seq, VRP_T1);
        split_T1(del_c, seq);
        c->fitness[VRP_T1] = del_c->fitness[VRP_T1];
        c->fitness[VRP_T2] = INT_MAX;
    }
    if (c->skill_factor == VRP_T2) {
        decoding(seq, VRP_T2);
        split_T2(del_c, seq);
        c->fitness[VRP_T2] = del_c->fitness[VRP_T2];
        c->fitness[VRP_T1] = INT_MAX;
    }
}

void rebuilt_chrom(undelimiter_individual *c, delimiter_individual *del_c) {
    int j = 0;
    int maxNumber =
        vNumber[VRP_T1] > vNumber[VRP_T2] ? vNumber[VRP_T1] : vNumber[VRP_T2];
    maxNumber -= 1;
    for (int i = 0; i < maxNumber; i++) {
        if (c->sequence[i] < vNumber[c->skill_factor]) {
            c->sequence[i] = del_c->sequence[j];
            j++;
        }
    }
}

void local_search(delimiter_individual *del, int type) {
    if (type == VRP_T1) local_search_T1(del);
    if (type == VRP_T2) local_search_T2(del);
}

void local_search_T1(delimiter_individual *del) {
    int sequence[2 * VERTEX_NUMBER];
    float service_time[2 * VERTEX_NUMBER];
    int count = del->count;
    float current_fitness, best_fitness;

    int u, v, x, y;
    int mark = 0, improved = 0;

    while (1) {
        memcpy(sequence, del->sequence, sizeof(sequence));
        best_fitness = del->fitness[VRP_T1];
        for (int i = 0; i < (count - 1); i++) {
            u = sequence[i];
            x = sequence[i + 1];
            if (sequence[i] == DEPOT) {
                if (i == (count - 2)) mark = 1;
                continue;
            }

            for (int j = 0; j < (count - 1); j++) {
                if (j == i) continue;
                v = sequence[j];
                y = sequence[j + 1];
                /*If u is a client node, remove u then insert it after v*/
                if (j > i) {
                    count = add_element(sequence, u, j + 1, count);
                    count = delete_element(sequence, i, count);
                }
                if (j < i) {
                    count = delete_element(sequence, i, count);
                    count = add_element(sequence, u, j + 1, count);
                }
                caculate_service_time_T1(sequence, service_time, count);
                if (evaluate_service_time_T1(sequence, service_time, count) &&
                    evaluate_load_T1(sequence, count)) {
                    current_fitness = caculate_fitness_T1(sequence, count);
                    if (current_fitness < best_fitness) {
                        improved = 1;
                        break;
                    }
                }
                memcpy(sequence, del->sequence, sizeof(sequence));

                /*If u and v are clients, swap u and v*/
                if (v != DEPOT) {
                    swap_element(sequence, i, j);
                    caculate_service_time_T1(sequence, service_time, count);
                    if (evaluate_service_time_T1(sequence, service_time,
                                                 count) &&
                        evaluate_load_T1(sequence, count)) {
                        current_fitness = caculate_fitness_T1(sequence, count);
                        if (current_fitness < best_fitness) {
                            improved = 1;
                            break;
                        }
                    }
                    memcpy(sequence, del->sequence, sizeof(sequence));
                }

                if ((i + 1) != j && x != DEPOT) {
                    /*If u and x are clients, remove them then insert (u, x)
                     * after v*/
                    if (i < j) {
                        count = add_element(sequence, u, j + 1, count);
                        count = add_element(sequence, x, j + 2, count);
                        count = delete_element(sequence, i + 1, count);
                        count = delete_element(sequence, i, count);
                    }
                    if (i > j) {
                        count = delete_element(sequence, i + 1, count);
                        count = delete_element(sequence, i, count);
                        count = add_element(sequence, u, j + 1, count);
                        count = add_element(sequence, x, j + 2, count);
                    }
                    caculate_service_time_T1(sequence, service_time, count);
                    if (evaluate_service_time_T1(sequence, service_time,
                                                 count) &&
                        evaluate_load_T1(sequence, count)) {
                        current_fitness = caculate_fitness_T1(sequence, count);
                        if (current_fitness < best_fitness) {
                            improved = 1;
                            break;
                        }
                    }
                    memcpy(sequence, del->sequence, sizeof(sequence));
                    /*If u and x are clients, remove them then insert (x, u)
                     * after v*/
                    if (i < j) {
                        count = add_element(sequence, x, j + 1, count);
                        count = add_element(sequence, u, j + 2, count);
                        count = delete_element(sequence, i + 1, count);
                        count = delete_element(sequence, i, count);
                    }
                    if (i > j) {
                        count = delete_element(sequence, i + 1, count);
                        count = delete_element(sequence, i, count);
                        count = add_element(sequence, x, j + 1, count);
                        count = add_element(sequence, u, j + 2, count);
                    }
                    caculate_service_time_T1(sequence, service_time, count);
                    if (evaluate_service_time_T1(sequence, service_time,
                                                 count) &&
                        evaluate_load_T1(sequence, count)) {
                        current_fitness = caculate_fitness_T1(sequence, count);
                        if (current_fitness < best_fitness) {
                            improved = 1;
                            break;
                        }
                    }
                    memcpy(sequence, del->sequence, sizeof(sequence));

                    /*If u, x and v are clients, swap (u,x) and v*/
                    if (v != DEPOT) {
                        swap_element(sequence, i, j);
                        if (i < j) {
                            count = add_element(sequence, x, j + 1, count);
                            count = delete_element(sequence, i + 1, count);
                        }
                        if (i > j) {
                            count = delete_element(sequence, i + 1, count);
                            count = add_element(sequence, x, j + 1, count);
                        }
                        caculate_service_time_T1(sequence, service_time, count);
                        if (evaluate_service_time_T1(sequence, service_time,
                                                     count) &&
                            evaluate_load_T1(sequence, count)) {
                            current_fitness =
                                caculate_fitness_T1(sequence, count);
                            if (current_fitness < best_fitness) {
                                improved = 1;
                                break;
                            }
                        }
                        memcpy(sequence, del->sequence, sizeof(sequence));
                    }

                    /*If (u, x) and (v, y) are clients, swap (u, x) and (v, y)*/
                    if (v != DEPOT && y != DEPOT) {
                        swap_element(sequence, i, j);
                        swap_element(sequence, i + 1, j + 1);
                        caculate_service_time_T1(sequence, service_time, count);
                        if (evaluate_service_time_T1(sequence, service_time,
                                                     count) &&
                            evaluate_load_T1(sequence, count)) {
                            current_fitness =
                                caculate_fitness_T1(sequence, count);
                            if (current_fitness < best_fitness) {
                                improved = 1;
                                break;
                            }
                        }
                        memcpy(sequence, del->sequence, sizeof(sequence));
                    }

                    /*replace (u, x) and (v, y) by (u, v) and (x, y)*/
                    if (v != DEPOT && y != DEPOT) {
                        swap_element(sequence, i + 1, j);
                        caculate_service_time_T1(sequence, service_time, count);
                        if (evaluate_service_time_T1(sequence, service_time,
                                                     count) &&
                            evaluate_load_T1(sequence, count)) {
                            current_fitness =
                                caculate_fitness_T1(sequence, count);
                            if (current_fitness < best_fitness) {
                                improved = 1;
                                break;
                            }
                        }
                        memcpy(sequence, del->sequence, sizeof(sequence));
                    }

                    /*replace (u, x) and (v, y) by (u, y) and (x, v)*/
                    if (v != DEPOT && y != DEPOT) {
                        swap_element(sequence, i + 1, j + 1);
                        swap_element(sequence, j, j + 1);
                        caculate_service_time_T1(sequence, service_time, count);
                        if (evaluate_service_time_T1(sequence, service_time,
                                                     count) &&
                            evaluate_load_T1(sequence, count)) {
                            current_fitness =
                                caculate_fitness_T1(sequence, count);
                            if (current_fitness < best_fitness) {
                                improved = 1;
                                break;
                            }
                        }
                        memcpy(sequence, del->sequence, sizeof(sequence));
                    }
                }

                /*2-opt*: interchange the last parts of two trips */
                if (v != DEPOT) {
                    bool in_same_route = true;
                    if (j > i) {
                        for (int k = i; k < j; k++)
                            if (sequence[k] == DEPOT) {
                                in_same_route = false;
                                break;
                            }
                    }
                    if (j < i) {
                        for (int k = j; k < i; k++)
                            if (sequence[k] == DEPOT) {
                                in_same_route = false;
                                break;
                            }
                    }

                    if (!in_same_route) {
                        /*case 1:before_u->u->x->after_x and
                         * before_v->v->y->after_y£¬to£¬before_u->u->y->after_y
                         * and before_v->v->x->after_x*/
                        int iu = i;
                        int iv = j;
                        int sqiu, sqiv;
                        while (sequence[iu] != DEPOT && sequence[iv] != DEPOT) {
                            swap_element(sequence, iu, iv);
                            iu++;
                            iv++;
                        }
                        if (sequence[iu] != DEPOT) {
                            while (sequence[iu] != DEPOT) {
                                sqiu = sequence[iu];
                                if (j > i) {
                                    count =
                                        add_element(sequence, sqiu, iv, count);
                                    count = delete_element(sequence, iu, count);
                                }
                                if (j < i) {
                                    count = delete_element(sequence, iu, count);
                                    count =
                                        add_element(sequence, sqiu, iv, count);
                                    iu++;
                                    iv++;
                                }
                            }
                        }
                        if (sequence[iv] != DEPOT) {
                            while (sequence[iv] != DEPOT) {
                                sqiv = sequence[iv];
                                if (j > i) {
                                    count = delete_element(sequence, iv, count);
                                    count =
                                        add_element(sequence, sqiv, iu, count);
                                    iu++;
                                    iv++;
                                }
                                if (j < i) {
                                    count =
                                        add_element(sequence, sqiv, iu, count);
                                    count = delete_element(sequence, iv, count);
                                }
                            }
                        }
                        caculate_service_time_T1(sequence, service_time, count);
                        if (evaluate_service_time_T1(sequence, service_time,
                                                     count) &&
                            evaluate_load_T1(sequence, count)) {
                            current_fitness =
                                caculate_fitness_T1(sequence, count);
                            if (current_fitness < best_fitness) {
                                improved = 1;
                                break;
                            }
                        }
                        memcpy(sequence, del->sequence, sizeof(sequence));
                        /*case 2:before_u->u->x->after_x and
                         * before_v->v->y->after_y£¬to£¬before_u->u->v->before_v
                         * and after_x->x->y->after_y*/
                        iu = i;
                        iv = j;
                        while (sequence[iu] != DEPOT && sequence[iv] != DEPOT) {
                            swap_element(sequence, iu, iv);
                            iu++;
                            iv--;
                        }
                        if (sequence[iu] != DEPOT) {
                            while (sequence[iu] != DEPOT) {
                                sqiu = sequence[iu];
                                if (j > i) {
                                    count = add_element(sequence, sqiu, iv + 1,
                                                        count);
                                    count = delete_element(sequence, iu, count);
                                    iv--;
                                }
                                if (j < i) {
                                    count = delete_element(sequence, iu, count);
                                    count = add_element(sequence, sqiu, iv + 1,
                                                        count);
                                    iu++;
                                }
                            }
                        }
                        if (sequence[iv] != DEPOT) {
                            while (sequence[iv] != DEPOT) {
                                sqiv = sequence[iv];
                                if (j > i) {
                                    count = delete_element(sequence, iv, count);
                                    count =
                                        add_element(sequence, sqiv, iu, count);
                                    iu++;
                                }
                                if (j < i) {
                                    count =
                                        add_element(sequence, sqiv, iu, count);
                                    count = delete_element(sequence, iv, count);
                                    iv--;
                                }
                            }
                        }
                        caculate_service_time_T1(sequence, service_time, count);
                        if (evaluate_service_time_T1(sequence, service_time,
                                                     count) &&
                            evaluate_load_T1(sequence, count)) {
                            current_fitness =
                                caculate_fitness_T1(sequence, count);
                            if (current_fitness < best_fitness) {
                                improved = 1;
                                break;
                            }
                        }
                        memcpy(sequence, del->sequence, sizeof(sequence));
                    }
                }
            }

            if (improved) {
                improved = 0;
                memcpy(del->sequence, sequence, sizeof(sequence));
                del->fitness[VRP_T1] = current_fitness;
                memcpy(del->service_time, service_time, sizeof(service_time));
                break;
            }
            if (i == (count - 2)) {
                mark = 1;
            }
        }
        if (mark) break;
    }
}

void local_search_T2(delimiter_individual *del) {
    int sequence[2 * VERTEX_NUMBER];
    float service_time[2 * VERTEX_NUMBER];
    int count = del->count;
    float current_fitness, best_fitness;

    int u, v, x, y;
    int mark = 0, improved = 0;

    while (1) {
        memcpy(sequence, del->sequence, sizeof(sequence));
        best_fitness = del->fitness[VRP_T2];
        for (int i = 0; i < (count - 1); i++) {
            u = sequence[i];
            x = sequence[i + 1];
            if (sequence[i] == DEPOT) {
                if (i == (count - 2)) mark = 1;
                continue;
            }

            for (int j = 0; j < (count - 1); j++) {
                if (j == i) continue;
                v = sequence[j];
                y = sequence[j + 1];
                /*If u is a client node, remove u then insert it after v*/
                if (j > i) {
                    count = add_element(sequence, u, j + 1, count);
                    count = delete_element(sequence, i, count);
                }
                if (j < i) {
                    count = delete_element(sequence, i, count);
                    count = add_element(sequence, u, j + 1, count);
                }
                caculate_service_time_T2(sequence, service_time, count);
                if (evaluate_service_time_T2(sequence, service_time, count) &&
                    evaluate_load_T2(sequence, count)) {
                    current_fitness = caculate_fitness_T2(sequence, count);
                    if (current_fitness < best_fitness) {
                        improved = 1;
                        break;
                    }
                }
                memcpy(sequence, del->sequence, sizeof(sequence));

                /*If u and v are clients, swap u and v*/
                if (v != DEPOT) {
                    swap_element(sequence, i, j);
                    caculate_service_time_T2(sequence, service_time, count);
                    if (evaluate_service_time_T2(sequence, service_time,
                                                 count) &&
                        evaluate_load_T2(sequence, count)) {
                        current_fitness = caculate_fitness_T2(sequence, count);
                        if (current_fitness < best_fitness) {
                            improved = 1;
                            break;
                        }
                    }
                    memcpy(sequence, del->sequence, sizeof(sequence));
                }

                if ((i + 1) != j && x != DEPOT) {
                    /*If u and x are clients, remove them then insert (u, x)
                     * after v*/
                    if (i < j) {
                        count = add_element(sequence, u, j + 1, count);
                        count = add_element(sequence, x, j + 2, count);
                        count = delete_element(sequence, i + 1, count);
                        count = delete_element(sequence, i, count);
                    }
                    if (i > j) {
                        count = delete_element(sequence, i + 1, count);
                        count = delete_element(sequence, i, count);
                        count = add_element(sequence, u, j + 1, count);
                        count = add_element(sequence, x, j + 2, count);
                    }
                    caculate_service_time_T2(sequence, service_time, count);
                    if (evaluate_service_time_T2(sequence, service_time,
                                                 count) &&
                        evaluate_load_T2(sequence, count)) {
                        current_fitness = caculate_fitness_T2(sequence, count);
                        if (current_fitness < best_fitness) {
                            improved = 1;
                            break;
                        }
                    }
                    memcpy(sequence, del->sequence, sizeof(sequence));
                    /*If u and x are clients, remove them then insert (x, u)
                     * after v*/
                    if (i < j) {
                        count = add_element(sequence, x, j + 1, count);
                        count = add_element(sequence, u, j + 2, count);
                        count = delete_element(sequence, i + 1, count);
                        count = delete_element(sequence, i, count);
                    }
                    if (i > j) {
                        count = delete_element(sequence, i + 1, count);
                        count = delete_element(sequence, i, count);
                        count = add_element(sequence, x, j + 1, count);
                        count = add_element(sequence, u, j + 2, count);
                    }
                    caculate_service_time_T2(sequence, service_time, count);
                    if (evaluate_service_time_T2(sequence, service_time,
                                                 count) &&
                        evaluate_load_T2(sequence, count)) {
                        current_fitness = caculate_fitness_T2(sequence, count);
                        if (current_fitness < best_fitness) {
                            improved = 1;
                            break;
                        }
                    }
                    memcpy(sequence, del->sequence, sizeof(sequence));

                    /*If u, x and v are clients, swap (u,x) and v*/
                    if (v != DEPOT) {
                        swap_element(sequence, i, j);
                        if (i < j) {
                            count = add_element(sequence, x, j + 1, count);
                            count = delete_element(sequence, i + 1, count);
                        }
                        if (i > j) {
                            count = delete_element(sequence, i + 1, count);
                            count = add_element(sequence, x, j + 1, count);
                        }
                        caculate_service_time_T2(sequence, service_time, count);
                        if (evaluate_service_time_T2(sequence, service_time,
                                                     count) &&
                            evaluate_load_T2(sequence, count)) {
                            current_fitness =
                                caculate_fitness_T2(sequence, count);
                            if (current_fitness < best_fitness) {
                                improved = 1;
                                break;
                            }
                        }
                        memcpy(sequence, del->sequence, sizeof(sequence));
                    }

                    /*If (u, x) and (v, y) are clients, swap (u, x) and (v, y)*/
                    if (v != DEPOT && y != DEPOT) {
                        swap_element(sequence, i, j);
                        swap_element(sequence, i + 1, j + 1);
                        caculate_service_time_T2(sequence, service_time, count);
                        if (evaluate_service_time_T2(sequence, service_time,
                                                     count) &&
                            evaluate_load_T2(sequence, count)) {
                            current_fitness =
                                caculate_fitness_T2(sequence, count);
                            if (current_fitness < best_fitness) {
                                improved = 1;
                                break;
                            }
                        }
                        memcpy(sequence, del->sequence, sizeof(sequence));
                    }

                    /*replace (u, x) and (v, y) by (u, v) and (x, y)*/
                    if (v != DEPOT && y != DEPOT) {
                        swap_element(sequence, i + 1, j);
                        caculate_service_time_T2(sequence, service_time, count);
                        if (evaluate_service_time_T2(sequence, service_time,
                                                     count) &&
                            evaluate_load_T2(sequence, count)) {
                            current_fitness =
                                caculate_fitness_T2(sequence, count);
                            if (current_fitness < best_fitness) {
                                improved = 1;
                                break;
                            }
                        }
                        memcpy(sequence, del->sequence, sizeof(sequence));
                    }

                    /*replace (u, x) and (v, y) by (u, y) and (x, v)*/
                    if (v != DEPOT && y != DEPOT) {
                        swap_element(sequence, i + 1, j + 1);
                        swap_element(sequence, j, j + 1);
                        caculate_service_time_T2(sequence, service_time, count);
                        if (evaluate_service_time_T2(sequence, service_time,
                                                     count) &&
                            evaluate_load_T2(sequence, count)) {
                            current_fitness =
                                caculate_fitness_T2(sequence, count);
                            if (current_fitness < best_fitness) {
                                improved = 1;
                                break;
                            }
                        }
                        memcpy(sequence, del->sequence, sizeof(sequence));
                    }
                }

                /*2-opt*: interchange the last parts of two trips */
                if (v != DEPOT) {
                    bool in_same_route = true;
                    if (j > i) {
                        for (int k = i; k < j; k++)
                            if (sequence[k] == DEPOT) {
                                in_same_route = false;
                                break;
                            }
                    }
                    if (j < i) {
                        for (int k = j; k < i; k++)
                            if (sequence[k] == DEPOT) {
                                in_same_route = false;
                                break;
                            }
                    }

                    if (!in_same_route) {
                        /*case 1*/
                        int iu = i;
                        int iv = j;
                        int sqiu, sqiv;
                        while (sequence[iu] != DEPOT && sequence[iv] != DEPOT) {
                            swap_element(sequence, iu, iv);
                            iu++;
                            iv++;
                        }
                        if (sequence[iu] != DEPOT) {
                            while (sequence[iu] != DEPOT) {
                                sqiu = sequence[iu];
                                if (j > i) {
                                    count =
                                        add_element(sequence, sqiu, iv, count);
                                    count = delete_element(sequence, iu, count);
                                }
                                if (j < i) {
                                    count = delete_element(sequence, iu, count);
                                    count =
                                        add_element(sequence, sqiu, iv, count);
                                    iu++;
                                    iv++;
                                }
                            }
                        }
                        if (sequence[iv] != DEPOT) {
                            while (sequence[iv] != DEPOT) {
                                sqiv = sequence[iv];
                                if (j > i) {
                                    count = delete_element(sequence, iv, count);
                                    count =
                                        add_element(sequence, sqiv, iu, count);
                                    iu++;
                                    iv++;
                                }
                                if (j < i) {
                                    count =
                                        add_element(sequence, sqiv, iu, count);
                                    count = delete_element(sequence, iv, count);
                                }
                            }
                        }
                        caculate_service_time_T2(sequence, service_time, count);
                        if (evaluate_service_time_T2(sequence, service_time,
                                                     count) &&
                            evaluate_load_T2(sequence, count)) {
                            current_fitness =
                                caculate_fitness_T2(sequence, count);
                            if (current_fitness < best_fitness) {
                                improved = 1;
                                break;
                            }
                        }
                        memcpy(sequence, del->sequence, sizeof(sequence));
                        /*case 2*/
                        iu = i;
                        iv = j;
                        while (sequence[iu] != DEPOT && sequence[iv] != DEPOT) {
                            swap_element(sequence, iu, iv);
                            iu++;
                            iv--;
                        }
                        if (sequence[iu] != DEPOT) {
                            while (sequence[iu] != DEPOT) {
                                sqiu = sequence[iu];
                                if (j > i) {
                                    count = add_element(sequence, sqiu, iv + 1,
                                                        count);
                                    count = delete_element(sequence, iu, count);
                                    iv--;
                                }
                                if (j < i) {
                                    count = delete_element(sequence, iu, count);
                                    count = add_element(sequence, sqiu, iv + 1,
                                                        count);
                                    iu++;
                                }
                            }
                        }
                        if (sequence[iv] != DEPOT) {
                            while (sequence[iv] != DEPOT) {
                                sqiv = sequence[iv];
                                if (j > i) {
                                    count = delete_element(sequence, iv, count);
                                    count =
                                        add_element(sequence, sqiv, iu, count);
                                    iu++;
                                }
                                if (j < i) {
                                    count =
                                        add_element(sequence, sqiv, iu, count);
                                    count = delete_element(sequence, iv, count);
                                    iv--;
                                }
                            }
                        }
                        caculate_service_time_T2(sequence, service_time, count);
                        if (evaluate_service_time_T2(sequence, service_time,
                                                     count) &&
                            evaluate_load_T2(sequence, count)) {
                            current_fitness =
                                caculate_fitness_T2(sequence, count);
                            if (current_fitness < best_fitness) {
                                improved = 1;
                                break;
                            }
                        }
                        memcpy(sequence, del->sequence, sizeof(sequence));
                    }
                }
            }

            if (improved) {
                improved = 0;
                memcpy(del->sequence, sequence, sizeof(sequence));
                del->fitness[VRP_T2] = current_fitness;
                memcpy(del->service_time, service_time, sizeof(service_time));
                break;
            }
            if (i == (count - 2)) {
                mark = 1;
            }
        }
        if (mark) break;
    }
}