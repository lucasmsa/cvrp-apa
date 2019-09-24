#ifndef PJ_FINAL_ILS_H
#define PJ_FINAL_ILS_H

#include "neighborhood.h"
#include "greedyfunction.h"
#include "VND.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

void DisturbanceFunction(vector<vector<int> >& solution, vector<vector<int> >& swap_solution, vector<vector<int> >& twoOpt_solution, vector<vector<int> >& inverter_solution,vector<vector<int> >& matrix, int vehicles, int i, vector<int>& final_route, vector<vector<int>>& greedy_solution){

    srand(seed + i + 2*seed);
    seed += 3;
    int a = rand()% 3;
    vector<int> temp_distance;
    vector<vector<int>> temp_solution;

    if (a == 0){
        temp_distance = SwapFunction(solution, swap_solution, matrix, vehicles, i+100000);
        temp_solution = swap_solution;
    }
    else if (a == 1){
        temp_distance = TwoOptFunction(solution, twoOpt_solution, matrix, vehicles, i+1000);
        temp_solution = twoOpt_solution; 
    }
    else if (a == 2){
        temp_distance = InverterFunction(solution, inverter_solution, matrix, vehicles, i+0);
        temp_solution = inverter_solution;
    }

    for (int j = 0; j < greedy_solution.size(); j++)
    {
       if(temp_distance[j] < final_route[j]){

           final_route[j] = temp_distance[j];
           solution[j].clear();
           solution[j] = temp_solution[j];
    
       }   
    }


}

vector<vector<int> >ILS(vector<int >& greedy_distance,vector<int>& final_route, vector<vector<int> >& vnd_solution, int dimension, vector<vector<int> >& matrix, int vehicles, int iterations, int capacity, vector<int>& demand, vector<vector<int> >& swap_solution, vector<vector<int> >& twoOpt_solution, vector<vector<int> >& inverter_solution, vector<vector<int> >& greedy_solution, int code_iterations, int its, double constr_time[], int l, int n_file){
    
    int i;
    clock_t Ticks[2];


    srand(time(NULL));
    seed = rand() % 1000*l;
    Ticks[0] = clock();
    greedy_distance = GreedyFunction(matrix, vehicles, capacity, dimension, 1618+seed, demand, greedy_solution);  
    Ticks[1] = clock();

    constr_time[l] +=  (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC; 

    final_route = VndFunction(vnd_solution,matrix, vehicles, 10, capacity, swap_solution, twoOpt_solution, inverter_solution,greedy_solution, greedy_distance, greedy_solution);
                
    vector<vector<int>> solution = vnd_solution;
    vector<vector<int>> temp_solution;
    vector<int>temp_distance;

    int porcent = 0, porcent_prev=0;

    //sleep(10);
    for (i = 0; i < iterations; i++)
    {

        porcent=(i*100)/iterations;

        if ((porcent > porcent_prev) || i <2)
        {
            porcent_prev = porcent;

            system("clear || cls");
            
            cout <<"-------------------------------------------------------------"<< endl;
            cout <<"                 Runing ILS Metaheuristic                   "<< endl;
            cout <<"-------------------------------------------------------------"<< endl;
            cout <<"                       FILE: "<<l << "/" <<n_file<<endl<<endl;            
            cout << "BUILDING SOLUTION..."<<its<<"/"<< code_iterations<< endl; 
            cout << "PROGRESS:" << ((i*100)/iterations) << "% ";

            for (int j = 0; j < ((i*100)/iterations); j+=2)
            {
                cout << "#";
            }

            cout<< endl;    
        }

        DisturbanceFunction(solution, swap_solution, twoOpt_solution, inverter_solution, matrix, vehicles, i+220+seed, final_route,greedy_solution);
        temp_solution = solution;
        final_route = VndFunction(solution,matrix, vehicles, 10, capacity, swap_solution, twoOpt_solution, inverter_solution,temp_solution, final_route, greedy_solution);

    }

    system("clear || cls");
            
    cout <<"-------------------------------------------------------------"<< endl;
    cout <<"                 Runing ILS Metaheuristic                   "<< endl;
    cout <<"-------------------------------------------------------------"<< endl;
    cout <<"                       FILE: "<<l << "/" <<n_file<<endl<<endl;
    cout << "BUILDING SOLUTION..."<<its<<"/"<< code_iterations<< endl; 
    cout << "PROGRESS:" << ((i*100)/iterations) << "% ";

    for (int j = 0; j < ((i*100)/iterations); j+=2)
    {
        cout << "#";
    }
    
    

    
    return solution;
}
#endif