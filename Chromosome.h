//
// Created by Katarina Krstin on 3.6.23..
//

#ifndef PROJEKAT_CHROMOSOME_H
#define PROJEKAT_CHROMOSOME_H


#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <string>

class Chromosome{
private:
    std::vector<std::vector<std::string>> chromosome;
    std::vector<std::vector<std::string>> generate_chromosome(std::map<std::string, int> jobs_dict, std::map<std::string, std::map<std::string, std::vector<int>>> machines_dict);
public:
    Chromosome(std::map<std::string, int> jobs, std::map<std::string, std::map<std::string, std::vector<int>>> machines, std::vector<std::vector<std::string>> chromosome);
    std::string to_string();
    };

#endif //PROJEKAT_CHROMOSOME_H
