//
// Created by Katarina Krstin on 5.6.23..
//

#ifndef PROJEKAT_MUTATION_H
#define PROJEKAT_MUTATION_H
#include <vector>
#include "Chromosome.h"
#include "constants.h"

std::vector<Chromosome> mutation(std::vector<Chromosome> chromosomes, double mutation_rate);
#endif //PROJEKAT_MUTATION_H
