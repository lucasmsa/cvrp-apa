#ifndef PJ_FINAL_NEIGHBORHOOD_H
#define PJ_FINAL_NEIGHBORHOOD_H

#include "greedyfunction.h"

using namespace std;

vector<int>
InverterFunction(vector<vector<int>> &solution, vector<vector<int>> &inverter_solution, vector<vector<int> > &matrix,
                 int vehicles, int randomizer) {

    inverter_solution = solution;
    vector<int> new_distance;
    int i = 0, k = 0, index_dist = 0;
    int distances = 0;
    int index = 1;
    srand(randomizer + seed);
    seed += 3;
    double adj[] = {0.4, 0.5, 0.6, 0.7, 0.8};
    int a = sizeof(adj) / sizeof(*adj), b = 0;
    double swap_adjuster = 0;
    int new_adjuster = 0;

    for (k = 0; k < solution.size(); k++) {
        swap_adjuster = adj[rand() % a];
        new_adjuster = int(round((swap_adjuster * inverter_solution.at(k).size())));
        b = new_adjuster;
        while (index < new_adjuster) {
            if (inverter_solution.at(k).at(index) == 0 || inverter_solution.at(k).at(b) == 0 || index == b)
                break;

            swap(inverter_solution[k][index], inverter_solution[k][b]);
            index += 1;
            b -= 1;
        }
        while (i < inverter_solution[k].size() - 1) {
            distances += matrix[inverter_solution[k][i]][inverter_solution[k][i + 1]];
            i += 1;
        }
        new_distance.push_back(distances);
        distances = 0;
        i = 0;
        index_dist += 1;
        index = 1;
    }

    return new_distance;
}


vector<int>
TwoOptFunction(vector<vector<int>> &solution, vector<vector<int>> &twoOpt_solution, vector<vector<int> > &matrix,
               int vehicles, int randomizer) {

    
    twoOpt_solution = solution;
    vector<int> new_distance;
    int i = 0, k = 0, index_dist = 0, o = 0;
    int distances = 0;
    int index = 1;

    srand(randomizer + seed);
    seed += 1;
    double adj[] = {0.2, 0.25, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};

    int a = sizeof(adj) / sizeof(*adj);
    double swap_adjuster = 0;
    int new_adjuster = 0;

    for (k = 0; k < solution.size(); k++) {
        swap_adjuster = adj[rand() % a];
        new_adjuster = int(round((swap_adjuster * twoOpt_solution.at(k).size())));

        while (index < new_adjuster) {

            if ((index + 2) >= twoOpt_solution.at(k).size() - 1)
                break;

            swap(twoOpt_solution[k][index], twoOpt_solution[k][index + 2]);
            index += 3;

        }

        while (i < twoOpt_solution[k].size() - 1) {
            distances += matrix[twoOpt_solution[k][i]][twoOpt_solution[k][i + 1]];
            i += 1;
        }
        new_distance.push_back(distances);
        distances = 0;
        i = 0;
        index_dist += 1;
        index = 1;
    }

    return new_distance;
}


vector<int>
SwapFunction(vector<vector<int>> &solution, vector<vector<int>> &swap_solution, vector<vector<int> > &matrix,
             int vehicles, int randomizer) {

    swap_solution = solution;
    vector<int> new_distance;
    int i = 0, k = 0, o = 0;
    int distances = 0;
    int index = 1;

    srand(randomizer + seed);
    seed += 3;
    double adj[] = {0.2, 0.25, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};

    int a = sizeof(adj) / sizeof(*adj);
    double swap_adjuster = 0;
    int new_adjuster = 0;


    for (k = 0; k < solution.size(); k++) {

        swap_adjuster = adj[rand() % a];
        new_adjuster = int(round((swap_adjuster * swap_solution.at(k).size())));
        while (index < new_adjuster && index) {
            if ((index + 1) >= swap_solution.at(k).size() - 1)
                break;
            swap(swap_solution[k][index], swap_solution[k][index + 1]);
            index += 2;
        }

        while (i < swap_solution[k].size() - 1) {
            distances += matrix[swap_solution.at(k).at(i)][swap_solution.at(k).at(i + 1)];
            i += 1;
        }
        new_distance.push_back(distances);
        distances = 0;
        i = 0;
        index = 1;
    }

    return new_distance;
}


#endif //PJ_FINAL_NEIGHBORHOOD_H
