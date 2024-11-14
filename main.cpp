#include "hungarian.h"
int main() {

    // std::vector<std::vector<int>> costs = {
    //     {250, 400, 350, 100},
    //     {400, 600, 350, 100},
    //     {200, 400, 250, 100}
    // };

    std::vector<std::vector<int>> costs = {
        {250, 400, 350},
        {400, 600, 350},
        {200, 400, 250},
        {300, 450, 500}
    };

    HungarianAlgorithm hungarian(costs);
    auto matches = hungarian.solve();

    std::cout << "Assignments:" << std::endl;
    for (const auto& match : matches) {
        std::cout << "Worker " << match.first
            << " -> Job " << match.second
            << " (Cost: " << costs[match.first][match.second] << ")" << std::endl;
    }

    // std::cout << "Total minimum cost: " << hungarian.getMinCost() << std::endl;

    return 0;
};
