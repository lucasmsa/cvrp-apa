#ifndef PJ_FINAL_NEIGHBORHOOD_H
#define PJ_FINAL_NEIGHBORHOOD_H

#include "greedyfunction.h"

using namespace std;

vector<int>
InverterFunction(vector<vector<int>> &solution, vector<vector<int>> &inverter_solution, vector<vector<int> > &matrix,
                 int vehicles, int randomizer) {

    inverter_solution = solution;
    cout << "=================================================================" << endl;
    cout << "INVERT" << endl;
    //vector<vector<int>> Inverter = solution;
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
        cout << "The New_adjuster is: " << swap_adjuster << endl;
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

    for (k = 0; k < solution.size(); k++) {
        cout << "[ ";
        for (i = 0; i < (inverter_solution[k].size()); i++) {
            if (i < (inverter_solution[k].size() - 1))
                cout << inverter_solution[k][i] << " -> ";
            else
                cout << inverter_solution[k][i];
        }
        cout << "] " << endl;
        cout << "New distance after Inversion: " << new_distance[k] << endl << endl;
    }

    /* cout << "##########################################################################"<< endl;
      for (int m = 0; m < solution.size(); m++)
     {
         //cout << "[ ";
         for (int n = 0; n < inverter_solution.at(m).size(); n++)
         {
             if(n == inverter_solution.at(m).size()-1) {
                 cout << inverter_solution[m][n];
                 break;
             }
             cout << inverter_solution[m][n] << ", ";

         }
         cout << "; " << endl;
         //cout << "Best solution: " << final_route[m] << ", vehicle: " << m << endl;
         //cout << "---------------------------" << endl;
     }
     cout << "##########################################################################"<< endl;
     */
    return new_distance;
}


vector<int>
TwoOptFunction(vector<vector<int>> &solution, vector<vector<int>> &twoOpt_solution, vector<vector<int> > &matrix,
               int vehicles, int randomizer) {

    cout << "=================================================================" << endl;
    cout << "TWO-OPT NUMBERED: " << endl;

    twoOpt_solution = solution;
    vector<int> new_distance;
    int i = 0, k = 0, index_dist = 0, o = 0;
    int distances = 0;
    int index = 1;
    // MIN swap_adjuster = solution.size()-2
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

            cout << twoOpt_solution[k][index + 2] << ", ";
            swap(twoOpt_solution[k][index], twoOpt_solution[k][index + 2]);
            index += 3;

        }

        cout << "The New_adjuster is: " << swap_adjuster << endl;
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

    for (k = 0; k < solution.size(); k++) {
        cout << "[ ";
        for (i = 0; i < (twoOpt_solution[k].size()); i++) {
            if (i < (twoOpt_solution[k].size() - 1))
                cout << twoOpt_solution[k][i] << " -> ";
            else
                cout << twoOpt_solution[k][i];
        }
        cout << "] " << endl;
        cout << "New distance after 2opt: " << new_distance[k] << endl << endl;
    }


    return new_distance;
}


vector<int>
SwapFunction(vector<vector<int>> &solution, vector<vector<int>> &swap_solution, vector<vector<int> > &matrix,
             int vehicles, int randomizer) {

    cout << "=================================================================" << endl;
    cout << "SWAP" << endl;
    swap_solution = solution;
    vector<int> new_distance;
    int i = 0, k = 0, o = 0;
    int distances = 0;
    int index = 1;

    srand(randomizer + seed);
    seed += 3;
    double adj[] = {0.2, 0.25, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};
    // MIN swap_adjuster = solution.size()-2
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
        cout << "The New_adjuster is: " << swap_adjuster << endl;
        while (i < swap_solution[k].size() - 1) {
            distances += matrix[swap_solution.at(k).at(i)][swap_solution.at(k).at(i + 1)];
            i += 1;
        }
        new_distance.push_back(distances);
        distances = 0;
        i = 0;
        index = 1;
    }

    for (k = 0; k < solution.size(); k++) {
        cout << "[ ";
        for (i = 0; i < (swap_solution[k].size()); i++) {
            if (i < (swap_solution[k].size() - 1))
                cout << swap_solution[k][i] << " -> ";
            else
                cout << swap_solution[k][i];
        }
        cout << "] " << endl;

        cout << "New distance after SWAP: " << new_distance[k] << endl << endl;
    }
    return new_distance;
}


#endif //PJ_FINAL_NEIGHBORHOOD_H
