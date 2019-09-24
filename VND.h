#ifndef PJ_FINAL_VND_H
#define PJ_FINAL_VND_H


#include <algorithm>
#include "neighborhood.h"


using namespace std;


vector<int> VndFunction(vector<vector<int> > &vnd_solution, vector<vector<int> > &matrix, int vehicles, int iterations,
                        int capacity, vector<vector<int> > &swap_solution, vector<vector<int> > &twoOpt_solution,
                        vector<vector<int> > &inverter_solution, vector<vector<int> > &temp_solution,
                        vector<int> &temp_distance, vector<vector<int>> &greedy_solution) {

    int i = 0, k = 0, o = 0, j=0, count_aux=0, dist_aux=0;
    vector<int> temp_route;
    vector<int> best_route;
    int min_route = 0;

    vector<int> aux;

    vector<int> swap_distance = SwapFunction(temp_solution, swap_solution, matrix, vehicles, i + 100000);
    vector<int> twoOpt_distance = TwoOptFunction(temp_solution, twoOpt_solution, matrix, vehicles, i + 10000);
    vector<int> inverter_distance = InverterFunction(temp_solution, inverter_solution, matrix, vehicles, i + 0);

    vnd_solution.clear();

    for (j = 0; j < greedy_solution.size(); j++) {

        min_route = min(temp_distance[j], swap_distance[j]);
        min_route = min(min_route, inverter_distance[j]);
        min_route = min(min_route, twoOpt_distance[j]);


        aux.clear();

        if (swap_distance[j] == min_route) {
            
            for (k = 0; k < swap_solution.at(j).size(); k++)
                aux.push_back(swap_solution[j][k]);

        } else if (twoOpt_distance[j] == min_route) {
           
            for (k = 0; k < twoOpt_solution.at(j).size(); k++)
                aux.push_back(twoOpt_solution[j][k]);

        } else if (inverter_distance[j] == min_route) {
      
            for (k = 0; k < inverter_solution.at(j).size(); k++)
                aux.push_back(inverter_solution[j][k]);

        } else if (temp_distance[j] == min_route) {

            for (k = 0; k < temp_solution.at(j).size(); k++)
                aux.push_back(temp_solution[j][k]);

        }

        dist_aux=0;


        best_route.push_back(min_route);
        vnd_solution.push_back(aux);

       

    }


    return best_route;
}

#endif //PJ_FINAL_VND_H
