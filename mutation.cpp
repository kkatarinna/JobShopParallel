//
// Created by Katarina Krstin on 5.6.23..
//

#include "mutation.h"

using namespace std;

std::vector<Chromosome> mutation(std::vector<Chromosome> chromosomes, double mutation_rate) {
    std::vector<Chromosome> mutated_chromosomes;
    for (auto& chromosome : chromosomes) {
        Chromosome mutated;
        vector<string> operations = chromosome.chromosome[0];
        vector<string> machines = chromosome.chromosome[1];

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(0.0, 1.0);

        if (dis(gen) < mutation_rate) {
            std::uniform_int_distribution<int> pos_dist(0, machines.size() - 1);
            int pos1 = pos_dist(gen);
            int pos2 = pos_dist(gen);

            string m1 = machines[pos1];
            string m2 = machines[pos2];
            machines[pos1] = m2;
            machines[pos2] = m1;


            //prolazimo kroz masine i kroz poslove da vidimo da li je novi redosled masina dobar
            for (int j = 0; j < JOBS_KEYS.size(); j++) {
                int o = 0;
                for (int i = 0; i < machines.size(); i++) {
                    string job = operations[i];
                    string machine = machines[i];

                    if (job == JOBS_KEYS[j]) {
                        int process_duration = MACHINES.at(machine).at(job)[o];
                        if (MACHINES.at(machine).at(job)[o] == 0) {
                            //ukoliko je 0 onda mora da pronadje masinu koja radi

                            while (process_duration != 0) {
                                std::uniform_int_distribution<int> new_m_dist(0, MACHINES.size() - 1);
                                int index = new_m_dist(gen);
                                auto it = std::next(std::begin(MACHINES), index);
                                string new_m = it->first;

                                process_duration = MACHINES.at(machine).at(job)[o];
                                // Assign new_m to the 'i'th machine (assuming 'machines' is an array or vector)
                                machines[i] = new_m;
                            }
                        }
                    }
                }
            }
        }

        vector<std::vector<std::string>> temp_vect;
        temp_vect.push_back(operations);
        temp_vect.push_back(machines);
        mutated.setChromosome(temp_vect);
        mutated_chromosomes.push_back(mutated);
    }
    return mutated_chromosomes;
}