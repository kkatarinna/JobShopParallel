//
// Created by Katarina Krstin on 5.6.23..
//

#include "geneticAlgorithm.h"
using namespace std;

vector<Chromosome> genetic(int population_size, double mutation_rate, int max_iter, double convergence_check){
    vector<Chromosome> chromosomes = generate_chromosome_list(population_size, JOBS, MACHINES, {});
    vector<Chromosome> the_best_list;
    vector<int> avg_values;
    vector<int> list_of_averages_trough_time;
    vector<int> list_of_best_values_trough_time;

    for(int i=0; i<max_iter; i++){
        std::map<Chromosome, int> chromosome_dict = get_chromosome_rang_dict(chromosomes, JOBS, MACHINES);
        std::vector<std::pair <Chromosome, Chromosome>> pairs = rulette_selection(chromosome_dict);
        std::vector<Chromosome> newgen = crossover(pairs);
        std::vector<Chromosome> mutirani = mutation(newgen, 0.7);

        vector<vector<vector<string>>> hromozomiZaProsledjivanje;
        for(auto& chromosome : chromosomes){
            hromozomiZaProsledjivanje.push_back(chromosome.chromosome);
        }
        chromosomes = generate_chromosome_list(population_size, JOBS, MACHINES, hromozomiZaProsledjivanje);
        cout<<"NEW GEN "+ std::to_string(i+1) +" =============================================="<<endl;
        for(auto& ch : chromosomes){
            cout<<ch.to_string()<<endl;
        }
    }

    return chromosomes;
}
