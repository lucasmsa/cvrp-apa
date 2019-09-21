#ifndef PJ_FINAL_ILS_H
#define PJ_FINAL_ILS_H

#include "neighborhood.h"
#include "greedyfunction.h"
#include <limits.h>
#include <vector>
#include <random>
#include "VND.h"

using namespace std;


vector<int> DisturbanceFunction(vector<vector<int> > solution, vector<vector<int> >& swap_solution, vector<vector<int> >& twoOpt_solution, vector<vector<int> >& inverter_solution,vector<vector<int> >& matrix, int vehicles, int i, vector<int>& final_route, vector<vector<int>> greedy_solution){

    srand(time(NULL));
    int a = rand() % 3;
    vector<int> temp_distance;
    vector<vector<int>> temp_solution;

    if (a == 0){
        temp_distance = SwapFunction(solution, swap_solution, matrix, vehicles, i+100000);
        temp_solution = swap_solution;
    }
    else if (a == 1){
        temp_distance = TwoOptFunction(solution, twoOpt_solution, matrix, vehicles, i+10000);
        temp_solution = twoOpt_solution; 
    }
    else if (a == 2){
        temp_distance = InverterFunction(solution, inverter_solution, matrix, vehicles, i+0);
        temp_solution = inverter_solution;
    }

    for (int j = 0; j < greedy_solution.size(); j++)
    {
       if(temp_distance[j] <= final_route[j]){
           solution[j].clear();
           solution[j] = temp_solution[j];
    
       }   
    }
    
}

vector<vector<int> >ILS(vector<int >& greedy_distance,vector<int>& final_route, vector<vector<int> >& vnd_solution, vector<vector<int> >& matrix, int vehicles, int iterations, int capacity, vector<int>& demand, vector<vector<int> >& swap_solution, vector<vector<int> >& twoOpt_solution, vector<vector<int> >& inverter_solution, vector<vector<int> >& greedy_solution){
                   
    greedy_distance = GreedyFunction(matrix, vehicles, capacity, demand, greedy_solution);
    final_route = VndFunction(vnd_solution,matrix, vehicles, 10, capacity, swap_solution, twoOpt_solution, inverter_solution,greedy_solution, greedy_distance);
                
    int i = 0;

    vector<vector<int>> solution = vnd_solution;
    vector<vector<int>> temp_solution;


    for (i = 0; i < iterations; i++)
    {
        DisturbanceFunction(solution, swap_solution, twoOpt_solution, inverter_solution, matrix, vehicles, i, final_route);
        final_route.clear();
        final_route = VndFunction(solution,matrix, vehicles, 10, capacity, swap_solution, twoOpt_solution, inverter_solution,greedy_solution, greedy_distance);

    }

    return solution;
    
}






#endif