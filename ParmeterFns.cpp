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

int fitness_function(Chromosome chromosome, std::map<std::string, std::map<std::string, std::vector<int>>> machines, std::map<std::string, int> jobs, bool is_elitis) {
    map<string, int> times;

    for (auto i : machines) {
        times[i.first] = 0;
    }

    for (int i = 0; i < jobs.size(); i++) {
        string curren_job = chromosome.chromosome[0][i];
        int p = 0;
        int o = 0;
        vector<string> used_machines;
        vector<int> durations;
        int total_duration = 0;
        for (string job : chromosome.chromosome[0]) {
            if (job == curren_job) {
                string machine = chromosome.chromosome[1][p];
                int process_duration = machines[machine][job][o];

                if (o == 0) {
                    times[machine] += process_duration;
                }
                else {
                    if (find(used_machines.begin(), used_machines.end(), machine) == used_machines.end()) {
                        times[machine] += process_duration;
                    }
                    else {
                        for (int u = 0; u < used_machines.size(); u++) {
                            if (machine == used_machines[u]) {
                                times[machine] -= durations[u];
                            }
                        }
                        times[machine] += total_duration;
                    }
                }
                o += 1;
                used_machines.push_back(machine);
                total_duration += process_duration;
                durations.push_back(process_duration);
            }
            p += 1;
        }
    }

    int finish_time = 0;
    for (auto i : times) {
        finish_time = max(finish_time, i.second);
    }
    return finish_time;
}

std::map<Chromosome, int> get_chromosome_rang_dict(std::vector<Chromosome> chromosomes_list, map<string, int> jobs, std::map<std::string, std::map<std::string, std::vector<int>>> machines) {
    std::map<Chromosome, int> data;
    for (auto& chromosome : chromosomes_list) {
        data[chromosome] = fitness_function(chromosome, machines, jobs, false);
    }
    std::vector<std::pair<Chromosome, int>> temp_vector(data.begin(), data.end());

    // Sortiranje vektora na osnovu vrednosti (int vrednosti u parovima)
    std::sort(temp_vector.begin(), temp_vector.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    // Izgradnja nove mape na osnovu sortiranog vektora
    std::map<Chromosome, int> sorted_map;
    for (const auto& pair : temp_vector) {
        sorted_map.insert(pair);
    }

    data.clear();
    for (auto item : sorted_map) {
        data.insert(std::pair<Chromosome, int>(item.first, item.second));
    }
    return data;
}

std::vector<std::pair <Chromosome, Chromosome>>  rulette_selection(std::map<Chromosome, int> &sorted_chromosome_dict) {
    for (auto &key : sorted_chromosome_dict) {
        int multiplyer = (int)rand() / RAND_MAX;
        key.second *= multiplyer;
    }

    std::vector<std::pair<Chromosome, int>> data_sorted;
    for (auto &key : sorted_chromosome_dict) {
        data_sorted.push_back(std::make_pair(key.first, key.second));
    }
    std::vector<std::pair<Chromosome, int>> temp_vector(data_sorted.begin(), data_sorted.end());

    // Sortiranje vektora na osnovu vrednosti (int vrednosti u parovima)
    std::sort(temp_vector.begin(), temp_vector.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    // Izgradnja nove mape na osnovu sortiranog vektora
    std::map<Chromosome, int> sorted_map;
    for (const auto& pair : temp_vector) {
        sorted_map.insert(pair);
    }

    sorted_chromosome_dict.clear();
    for (auto &item : data_sorted) {
        sorted_chromosome_dict.insert(std::make_pair(item.first, item.second));
    }

    std::vector<std::pair <Chromosome, Chromosome>> list_of_pairs;
    int i = 0;
    for (auto &key : sorted_chromosome_dict) {
        Chromosome t1 = key.first;
        if ((i + 1) % 2 == 0) {
            Chromosome t2 = key.first;
            list_of_pairs.push_back(std::pair<Chromosome, Chromosome>(t1, t2));
        }
        i++;
    }
    return list_of_pairs;
}

std::string getRandomMachine(const std::map<std::string, std::map<std::string, std::vector<int>>>& machines) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, machines.size() - 1);

    auto it = machines.begin();
    std::advance(it, dis(gen));
    return it->first;
}


//std::vector<Chromosome> crossover(const std::vector<std::pair<Chromosome, Chromosome>>& parents) {
//    std::vector<Chromosome> children;
//
//    for (const auto& pair : parents) {
//        Chromosome child1 = *new Chromosome();
//        Chromosome child2 = *new Chromosome();
//        const Chromosome& mom = pair.first;
//        const Chromosome& dad = pair.second;
//
//        child1.chromosome.push_back(mom.chromosome[0]);
//        child1.chromosome.push_back(dad.chromosome[1]);
//
//        child2.chromosome.push_back(dad.chromosome[0]);
//        child2.chromosome.push_back(mom.chromosome[1]);
//
//        // Check validity of machine order in child1
//        for (int j = 0; j < JOBS_KEYS.size(); j++) {
//            int o = 0;
//            for (int i = 0; i < mom.chromosome[1].size(); i++) {
//                std::string& job = child1.chromosome[0][i];
//                std::string& machine = child1.chromosome[1][i];
//
//                if (job == JOBS_KEYS[j]) {
//                    int process_duration = MACHINES.at(machine).at(job)[o];
//                    if (process_duration == 0) {
//                        // Find a machine that can process the job
//                        while (process_duration == 0) {
//                            std::random_device rd;
//                            std::uniform_int_distribution<int> dist(0, extract_Machines_Keys(MACHINES).size() - 1);
//                            int randomIndex = dist(rd);
//                            machine = extract_Machines_Keys(MACHINES)[randomIndex];
//                            process_duration = MACHINES.at(machine).at(job)[o];
//                        }
//                    }
//                }
//            }
//        }
//
//        // Check validity of machine order in child2
//        for (int j = 0; j < JOBS_KEYS.size(); j++) {
//            int o = 0;
//            for (int i = 0; i < mom.chromosome[1].size(); i++) {
//                const std::string& job = child2.chromosome[0][i];
//                std::string& machine = child2.chromosome[1][i];
//
//                if (job == JOBS_KEYS[j]) {
//                    int process_duration = MACHINES.at(machine).at(job)[o];
//                    if (process_duration == 0) {
//                        // Find a machine that can process the job
//                        while (process_duration == 0) {
//                            std::random_device rd;
//                            std::uniform_int_distribution<int> dist(0, extract_Machines_Keys(MACHINES).size() - 1);
//                            int randomIndex = dist(rd);
//                            machine = extract_Machines_Keys(MACHINES)[randomIndex];
//                            process_duration = MACHINES.at(machine).at(job)[o];
//                        }
//                    }
//                }
//            }
//        }
//
//        children.push_back(Chromosome(JOBS, MACHINES, child1.chromosome));
//        children.push_back(Chromosome(JOBS, MACHINES, child2.chromosome));
//
//    }
//
//    return children;
//}


