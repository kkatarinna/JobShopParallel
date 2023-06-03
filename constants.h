//
// Created by Katarina Krstin on 3.6.23..
//

#ifndef PROJEKAT_CONSTANTS_H
#define PROJEKAT_CONSTANTS_H

#include <vector>
#include <map>
#include <iostream>
#include "ParmeterFns.h"
using namespace std;

extern const std::map<std::string, int> JOBS = generate_Jobs(6, 2); //{ {"J1", 3}, {"J2", 2}, {"J3",3}, {"J4",3}, {"J5",2}, {"J6",2} };
extern const std::vector<std::string> JOBS_KEYS = extract_Jobs_Keys(JOBS); //{"J1", "J2", "J3", "J4", "J5", "J6"};
extern const std::map<std::string, std::map<std::string, std::vector<int>>> MACHINES = generate_Machines(5, JOBS, 20); //{{"M1", {{"J1", {2, 5, 2}}, {"J2", {10, 2}}}}, {"M2", {{"J1", {2, 0, 5}}, {"J2", {10, 2}}}}, {"M3", {{"J1", {0, 5, 0}}, {"J2", {10, 0}}}}};
//extern const std::vector< std::vector<std::vector<std::string>> > CHROMOSOMES = generate_chromosome_list(100, JOBS, MACHINES, {{{""}}});


#endif //PROJEKAT_CONSTANTS_H
