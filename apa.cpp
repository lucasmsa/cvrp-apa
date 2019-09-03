#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits.h>
#include <algorithm> 


using namespace std;

char archive[] = "./instancias_teste/P-n19-k2.txt";

// Tem a carga, que toda vez que um veículo passa pela cidade ele tem a carga 
// diminuída pela demanda da cidade

//Na função greedyconstruction termeos um tmelhor que será o valor retornado
//pela greedyfunction

//find(initial_solution.begin(), initial_solution.end(), j) != initial_solution.end() &&

vector<int> GreedyFunction(vector<vector<int> >& cities){
   
    vector<int> initial_solution;
    int i = 0, j, menor = INT_MAX, ind_menor = 10, sum_distances = 0;
    int count2 = 0;
    cout << "[ 0 ";
    while(count2 < cities.size()){
        for(j = 0; j < cities.size(); j++){
            if(cities[i][j] != 0 && cities[i][j] < menor){
                if(find(initial_solution.begin(), initial_solution.end(), j) == initial_solution.end()){
                    menor = cities[i][j];
                    ind_menor = j;
                }
            }
            
        }
        initial_solution.push_back(ind_menor); 
        sum_distances += menor;
        i = ind_menor;
        menor = INT_MAX;
        cout << " -> " << ind_menor;
        count2++;
    }
    cout << " ]" << endl;
    cout << "Total distance: " << sum_distances << endl;

    //if(o == 1)
      //  return initial_solution;
    //else if (o == 0)
        //return sum_distances;

    return initial_solution;
}

//int get_total_distance()
   
//int GreedyConstruction(vector<vector<int>>& greedysol, int)){}



int main() {

    int *sum_distances;
    ifstream arq(archive);
    string buffer;
    char linha[50];
    char delimiter[3] = ": ", *sC = {0}, *sV = {0}, *sD = {0}, buf[100] = {0}, *pch = {0};
    vector<vector<int> > matrix, demand_section;
    int i = 0, dimension = 0, vehicles = 0, capacity = 0, l = -1, c = 0, j=-1, k=0, valor, s=0;
    if (arq) {

        cout<< "ENTREI MIZERA"<< endl;
        while (getline(arq, buffer)) {

            if (i == 1) {
                strcpy(linha, buffer.c_str());
                sD = strchr(linha, ' ');
                sD++;
                dimension = atoi(sD);
                cout << "Dimension: " << dimension << endl;

            } else if (i == 2) {
                strcpy(linha, buffer.c_str());
                sV = strchr(linha, ' ');
                sV++;
                vehicles = atoi(sV);
                cout << "Vehicles: " << vehicles << endl;

            } else if (i == 3) {
                strcpy(linha, buffer.c_str());
                sC = strchr(linha, ' ');
                sC++;
                capacity = atoi(sC);
                cout << "Capacity: " << capacity << endl;

            } else if (i >= 5 && i < (dimension + 5)) {
                demand_section.push_back(vector<int>());
                stringstream split(buffer);

                while (split >> valor)
                    demand_section.back().push_back(valor);
                }

            else if(i >= (dimension + 7) && i <(dimension*2)+7){


                matrix.push_back(vector<int>());

                stringstream split(buffer);

                while (split >> valor)
                    matrix.back().push_back(valor);

            }
            i++;
        }

    }

    /*
    for (int i = 0; i < demand_section.size(); i++) {

            for (int j = 0; j < demand_section[i].size(); j++)
                cout << demand_section[i][j] << ' ';

            cout << '\n';
    }*/

    /*
    for (int i = 0; i < matrix.size(); i++) {
        
            for (int j = 0; j < matrix[i].size(); j++)
                cout << matrix[i][j] << ' ';

            cout << '\n';
    }*/

    /*
    vector<vector<int>> state(matrix.size());
    for(auto& neighbors : state){
        neighbors = vector<int>((1 << matrix.size()) - 1, INT_MAX);
    
    }*/

    //cout << "minimum: " << tsp(matrix, 0, 1, state) << endl;


    GreedyFunction(matrix);
    cout << sum_distances << endl;
 
}