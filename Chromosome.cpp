////
//// Created by Katarina Krstin on 3.6.23..
////

#include "Chromosome.h"
#include <vector>
#include <map>
#include <random>
#include <string>

#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <ctime>

using namespace std;

Chromosome::Chromosome(std::map<std::string, int> jobs, std::map<std::string, std::map<std::string, std::vector<int>>> machines, std::vector<std::vector<std::string>> chromosome)

{
        if (chromosome.size() == 0) {
            this->chromosome = generate_chromosome(jobs, machines);
        } else {
            this->chromosome = chromosome;
        }
    }

Chromosome::Chromosome() {
    this->chromosome = {};
}

std::string Chromosome::to_string() {
    std::string str = "iz klase : ";
    for (int i = 0; i < this->chromosome.size(); i++) {
        for (int j = 0; j < this->chromosome[i].size(); j++) {
            str += this->chromosome[i][j] + " ";
        }
    }
    return str;
}

std::vector<std::vector<std::string>> Chromosome::generate_chromosome(std::map<std::string, int> jobs_dict, std::map<std::string, std::map<std::string, std::vector<int>>> machines_dict) {
    {
        std::vector<std::string> job_slot;
        std::vector<std::string> machine_slot;
        std::map<std::string, int> all_jobs_occurance_counter;

        for (const auto& job : jobs_dict) {
            all_jobs_occurance_counter[job.first] = 0;
        }

        std::random_device rd;
        std::mt19937 gen(rd());

        std::vector<std::string> job_keys;
        for (const auto& job : jobs_dict) {
            job_keys.push_back(job.first);
        }

        while (!job_keys.empty()) {
            std::uniform_int_distribution<> dis(0, job_keys.size() - 1);
            int random_index = dis(gen);
            std::string choice = job_keys[random_index];

            if (all_jobs_occurance_counter[choice] < jobs_dict[choice]) {
                all_jobs_occurance_counter[choice] += 1;
                job_slot.push_back(choice);

                bool all_same = true;
                for (const auto& job : jobs_dict) {
                    if (all_jobs_occurance_counter[job.first] != job.second) {
                        all_same = false;
                        break;
                    }
                }

                if (all_same) {
                    break;
                }
            }

            job_keys.erase(job_keys.begin() + random_index);
        }

        for (auto& job_counter : all_jobs_occurance_counter) {
            job_counter.second = 0;
        }

        for (const auto& job_key : job_slot) {
            std::vector<std::string> machine_keys;
            for (const auto& machine : machines_dict) {
                std::map<std::string, std::vector<int>> temp_machine = machine.second;
                if (0 != temp_machine[job_key][all_jobs_occurance_counter[job_key]]) {
                    machine_keys.push_back(machine.first);
                }
            }

            std::uniform_int_distribution<> dis(0, machine_keys.size() - 1);
            int random_index = dis(gen);
            std::string choice = machine_keys[random_index];
            machine_slot.push_back(choice);
            all_jobs_occurance_counter[job_key] += 1;
        }

        std::vector<std::vector<std::string>> chromosome;
        chromosome.push_back(job_slot);
        chromosome.push_back(machine_slot);
        return chromosome;

    }

}

bool Chromosome::operator<(const Chromosome& rhs) const {
    if (chromosome.size() != rhs.chromosome.size()) {
        return chromosome.size() < rhs.chromosome.size();
    }

    // Compare the elements of the chromosome vector
    for (size_t i = 0; i < chromosome.size(); i++) {
        // Compare the elements of the chromosome vector at index 'i'
        // based on your desired comparison logic
        // For example, you can compare strings lexicographically
        if (chromosome[i] != rhs.chromosome[i]) {
            return chromosome[i] < rhs.chromosome[i];
        }
    }

    // Chromosome objects are equal
    return false;
}

bool Chromosome::operator==(const Chromosome& other) const {
    return chromosome == other.chromosome;
}





