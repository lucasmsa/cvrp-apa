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

//        cout << "TEMP: " << temp_distance[j] << " SWAP: " << swap_distance[j] << " INVERTER: "<< inverter_distance[j] << " 2OPT: " << twoOpt_distance[j]<<"||min: "<< min_route << endl; 

        aux.clear();

        if (swap_distance[j] == min_route) {

            for (k = 0; k < swap_solution.at(j).size(); k++)
                aux.push_back(swap_solution[j][k]);

        } else if (twoOpt_distance[j] == min_route) {

            for (k = 0; k < twoOpt_solution.at(j).size(); k++)
                aux.push_back(swap_solution[j][k]);

        } else if (inverter_distance[j] == min_route) {

            for (k = 0; k < inverter_solution.at(j).size(); k++)
                aux.push_back(inverter_solution[j][k]);

        } else if (temp_distance[j] == min_route) {


            for (k = 0; k < temp_solution.at(j).size(); k++)
                aux.push_back(temp_solution[j][k]);

        }

        dist_aux=0;

        for (count_aux = 0; count_aux < aux.size()-1; count_aux++)
            dist_aux+=matrix.at(aux.at(count_aux)).at(aux.at(count_aux+1));   
        
        best_route.push_back(dist_aux);
        vnd_solution.push_back(aux);
       

    }
/*
	cout << "###########################################################################################################################################"<<endl;

    for (int m = 0; m < vehicles; m++)
    {
         for (int n = 0; n < final_solution.at(m).size(); n++)
         {
             cout << final_solution[m][n] << " ";
         }

         cout << endl;
         cout << "Melhor solucao: " << best_route[m] << endl << endl;
    }
*/

  /*int distance = 0;
    int m = 0, n = 0, sum=0;
for (m = 0; m < vnd_solution.size(); m++)
    {
        for (n = 0; n < vnd_solution.at(m).size()-1; n++)
        {
            distance += matrix[vnd_solution.at(m).at(n)][vnd_solution.at(m).at(n+1)];
            cout << vnd_solution[m][n] << ", ";
        }
        cout << vnd_solution[m][n];
        sum += best_route.at(m);
        cout << "; " << endl;
        cout << "VEICULO " << m << ", CALCULO DA DISTANCIA: " << distance << ", CALCULO DA FINAL_ROUTE: " << best_route.at(m) << endl;
        distance = 0;

    }
    cout << "Distance Travelled: " << distance <<  ", outro: " << sum << endl;
    cout << "SOLUTION SIZE (NUMBER OF ROUTES): " << vnd_solution.size() << endl;

*/

    return best_route;
}

#endif //PJ_FINAL_VND_H
