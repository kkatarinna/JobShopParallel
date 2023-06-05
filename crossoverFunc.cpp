//
// Created by Katarina Krstin on 4.6.23..
//

#include "crossoverFunc.h"

std::vector<std::string> extract_Machines_Keys(std::map<std::string, std::map<std::string, std::vector<int>>> machines){
    std::vector<std::string> keys;
    for (const auto& pair : machines) {
        keys.push_back(pair.first);
    }

    return keys;
}

std::vector<Chromosome> crossover(const std::vector<std::pair<Chromosome, Chromosome>>& parents) {
    std::vector<Chromosome> children;

    for (const auto& pair : parents) {
        Chromosome child1 = *new Chromosome();
        Chromosome child2 = *new Chromosome();
        const Chromosome& mom = pair.first;
        const Chromosome& dad = pair.second;

        child1.chromosome.push_back(mom.chromosome[0]);
        child1.chromosome.push_back(dad.chromosome[1]);

        child2.chromosome.push_back(dad.chromosome[0]);
        child2.chromosome.push_back(mom.chromosome[1]);

        // Check validity of machine order in child1
        for (int j = 0; j < JOBS_KEYS.size(); j++) {
            int o = 0;
            for (int i = 0; i < mom.chromosome[1].size(); i++) {
                std::string& job = child1.chromosome[0][i];
                std::string& machine = child1.chromosome[1][i];

                if (job == JOBS_KEYS[j]) {
                    int process_duration = MACHINES.at(machine).at(job)[o];
                    if (process_duration == 0) {
                        // Find a machine that can process the job
                        while (process_duration == 0) {
                            std::random_device rd;
                            std::uniform_int_distribution<int> dist(0, extract_Machines_Keys(MACHINES).size() - 1);
                            int randomIndex = dist(rd);
                            machine = extract_Machines_Keys(MACHINES)[randomIndex];
                            process_duration = MACHINES.at(machine).at(job)[o];
                        }
                    }
                }
            }
        }

        // Check validity of machine order in child2
        for (int j = 0; j < JOBS_KEYS.size(); j++) {
            int o = 0;
            for (int i = 0; i < mom.chromosome[1].size(); i++) {
                const std::string& job = child2.chromosome[0][i];
                std::string& machine = child2.chromosome[1][i];

                if (job == JOBS_KEYS[j]) {
                    int process_duration = MACHINES.at(machine).at(job)[o];
                    if (process_duration == 0) {
                        // Find a machine that can process the job
                        while (process_duration == 0) {
                            std::random_device rd;
                            std::uniform_int_distribution<int> dist(0, extract_Machines_Keys(MACHINES).size() - 1);
                            int randomIndex = dist(rd);
                            machine = extract_Machines_Keys(MACHINES)[randomIndex];
                            process_duration = MACHINES.at(machine).at(job)[o];
                        }
                    }
                }
            }
        }

        children.push_back(Chromosome(JOBS, MACHINES, child1.chromosome));
        children.push_back(Chromosome(JOBS, MACHINES, child2.chromosome));

    }

    return children;
}


