#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Chromosome.h"
#include "constants.h"

int main() {


//    for (const auto& pair : JOBS) {
//        std::cout << pair.first << "::" << pair.second << "\n";
//    }
//
//    for (const auto& pair : JOBS_KEYS){
//        cout<<pair<<endl;
//    }

//    for(const auto& pair :MACHINES){
//        cout<<pair.first<<endl;
//        for(const auto& inner_dict : pair.second){
//            cout<<inner_dict.first<<endl;
//            for (const auto& inner_inner_vect :inner_dict.second){
//                cout<<inner_inner_vect<<endl;
//            }
//        }
//    }
      std::vector<std::vector<std::string>> chromosome;
      Chromosome proba(JOBS, MACHINES, chromosome);
//    cout<<proba.to_string()<<endl;

    vector<Chromosome> chromosomes = generate_chromosome_list(4, JOBS, MACHINES, {});
    for(auto& ch : chromosomes){
        cout<<ch.to_string()<<endl;
    }

    std::map<Chromosome, int> test = get_chromosome_rang_dict(chromosomes, JOBS, MACHINES);
    for(auto& ch : test){
       cout<<ch.second<<endl;
    }

    std::vector<std::pair <Chromosome, Chromosome>> testic = rulette_selection(test);
    for (auto it = testic.begin(); it != testic.end(); ++it) {
        std::cout << it->first.to_string() << " " << it->second.to_string() << std::endl;
    }

//    std::vector<Chromosome> newgen = crossover(testic);
//    for(auto& ch : newgen){
//        cout<<ch.to_string()<<endl;
//    }

    return 0;
}
