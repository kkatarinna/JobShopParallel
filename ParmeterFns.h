//
// Created by Katarina Krstin on 3.6.23..
//

#ifndef PROJEKAT_PARMETERFNS_H
#define PROJEKAT_PARMETERFNS_H

#include <iostream>
#include <map>
#include <random>
#include <vector>
#include "Chromosome.h"
//#include "constants.h"
using namespace std;

map<string, int> generate_Jobs(int num_of_jobs, int num_of_operations);
vector<string> extract_Jobs_Keys(map<string, int> jobs);
std::vector<Chromosome> generate_chromosome_list(int population_size, std::map<std::string, int> jobs, std::map<std::string, std::map<std::string, std::vector<int>>> machines, std::vector< std::vector<std::vector<std::string>> > chromosomes);
std::map<std::string, std::map<std::string, std::vector<int>>> generate_Machines(int num_of_machines, const std::map<std::string, int> jobs, int machine_times_max);
int fitness_function(Chromosome chromosome, std::map<std::string, std::map<std::string, std::vector<int>>> machines, std::map<std::string, int> jobs, bool is_elitis);
std::map<Chromosome, int> get_chromosome_rang_dict(std::vector<Chromosome> chromosomes_list, map<string, int> jobs, std::map<std::string, std::map<std::string, std::vector<int>>> machines);
std::vector<std::pair <Chromosome, Chromosome>> rulette_selection(std::map<Chromosome, int> &sorted_chromosome_dict);
std::vector<Chromosome> crossover(const std::vector<std::pair<Chromosome, Chromosome>>& parents);

#endif //PROJEKAT_PARMETERFNS_H
