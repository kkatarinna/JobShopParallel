//
// Created by Katarina Krstin on 3.6.23..
//

#include "ParmeterFns.h"

std::map<std::string, int> generate_Jobs(int num_of_jobs, int num_of_operations) {
    std::map<std::string, int> jobs;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(2, num_of_operations + 1);
    for (int i = 0; i < num_of_jobs; i++) {
        std::string job_key = "J" + std::to_string(i + 1);
        int job = dis(gen);
        jobs[job_key] = job;
    }
    return jobs;
}

vector<string> extract_Jobs_Keys(map<string, int> jobs){
    vector<string> keys;
    for (const auto& pair : jobs) {
        keys.push_back(pair.first);
    }

    return keys;
}

std::vector<Chromosome> generate_chromosome_list(int population_size, std::map<std::string, int> jobs, std::map<std::string, std::map<std::string, std::vector<int>>> machines, std::vector< std::vector<std::vector<std::string>> > chromosomes){
    std::vector<Chromosome> chromosome_list;
    if (chromosomes.size() != 0) {
        for (auto chromosome : chromosomes) {
            chromosome_list.push_back(Chromosome(jobs, machines, chromosome));
        }
    } else {
        for (int i = 0; i < population_size; i++) {
            chromosome_list.push_back(Chromosome(jobs, machines, {}));
        }
    }
    return chromosome_list;
}

std::map<std::string, std::map<std::string, std::vector<int>>> generate_Machines(int num_of_machines, const std::map<std::string, int> jobs, int machine_times_max) {
    std::map<std::string, std::map<std::string, std::vector<int>>> machines;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < num_of_machines; i++) {
        std::string machine_key = "M" + std::to_string(i + 1);
        //std::vector<std::map<std::string, std::vector<int>>> machine_inner_vector;
        std::map<std::string, std::vector<int>> machine_inner_dict;

        for (const auto& entry : jobs) {
            std::vector<int> machine_times;

            for (int j = 0; j < entry.second; j++) {
                std::uniform_int_distribution<> dis(0, machine_times_max);
                machine_times.push_back(dis(gen));
            }

            machine_inner_dict.insert({entry.first, machine_times});
            //machine_inner_vector.push_back(machine_inner_dict);
        }
        machines.insert({machine_key, machine_inner_dict});


    }

    return machines;
}
