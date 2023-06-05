//
// Created by Katarina Krstin on 5.6.23..
//

#ifndef PROJEKAT_GENETICALGORITHM_H
#define PROJEKAT_GENETICALGORITHM_H
#include <iostream>
#include "Chromosome.h"
#include "constants.h"
#include "mutation.h"
#include "crossoverFunc.h"

vector<Chromosome> genetic(int population_size, double mutation_rate = 0.7, int max_iter = 100, double convergence_check = 0.005);
#endif //PROJEKAT_GENETICALGORITHM_H
