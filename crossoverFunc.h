//
// Created by Katarina Krstin on 4.6.23..
//

#ifndef PROJEKAT_CROSSOVERFUNC_H
#define PROJEKAT_CROSSOVERFUNC_H

#include <iostream>
#include <map>
#include <random>
#include <vector>
#include "Chromosome.h"
#include "constants.h"

std::vector<std::string> extract_Machines_Keys(std::map<std::string, std::map<std::string, std::vector<int>>> machines);
std::vector<Chromosome> crossover(const std::vector<std::pair<Chromosome, Chromosome>>& parents);


#endif //PROJEKAT_CROSSOVERFUNC_H
