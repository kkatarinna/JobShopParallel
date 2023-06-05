#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Chromosome.h"
#include "constants.h"

int main() {
    
    std::vector<std::vector<std::string>> chromosome;
    Chromosome proba(JOBS, MACHINES, chromosome);
    cout<<proba.to_string()<<endl;

    return 0;
}
