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

inline const std::map<std::string, int> JOBS = generate_Jobs(6, 2);
inline const std::vector<std::string> JOBS_KEYS = extract_Jobs_Keys(JOBS);
inline const std::map<std::string, std::map<std::string, std::vector<int>>> MACHINES = generate_Machines(5, JOBS, 20);


#endif //PROJEKAT_CONSTANTS_H
