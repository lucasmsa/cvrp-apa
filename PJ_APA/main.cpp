#include "ILS.h"
#include "cup_matrix.h"


using namespace std;

char archive[] = "./cvrp-cup/cvrp3.txt";


// Tem a carga, que toda vez que um veículo passa pela cidade ele tem a carga
// diminuída pela demanda da cidade

//Na função greedyconstruction termeos um tmelhor que será o valor retornado
//pela greedyfunction



int main() {


    vector<vector<int>> vnd_solution;
    vector<vector<int>> swap_solution;
    vector<vector<int>> twoOpt_solution;
    vector<vector<int>> inverter_solution;
    vector<vector<int>> greedy_solution;

    vector<int> greedy_distance;
    vector<int> final_route;
    vector<vector<int>> coordinates;
    int sum_distances = 0;
    ifstream arq(archive);
    string buffer;
    char linha[50];
    char delimiter[3] = ": ", *sC = {0}, *sV = {0}, *sD = {0}, buf[100] = {0}, *pch = {0}, *dem = {0};

    vector<int> demand_section;
    int i = 0, dimension = 0, vehicles = 0, capacity = 0, l = -1, c = 0, j = -1, k = 0, valor, s = 0;


    if (arq) {

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

                strcpy(linha, buffer.c_str());
                dem = strchr(linha, ' ');
                dem++;
                demand_section.push_back(atoi(dem));
            } else if (i >= (dimension + 7) && i < (dimension * 2) + 7) {

                coordinates.push_back(vector<int>());

                stringstream split(buffer);

                while (split >> valor)
                    coordinates.back().push_back(valor);

            }
            i++;
        }
    }
    vehicles = 0;
    cout << coordinates.at(1).at(2);
    srand(time(0));
    seed = rand() % 10000;

    vector<vector<int> > matrix = Transpose(coordinates, dimension);
    vector<vector<int>> final_solution = ILS(greedy_distance, final_route, vnd_solution, dimension, matrix, vehicles, 7750000,
                                             capacity, demand_section, swap_solution, twoOpt_solution,
                                             inverter_solution, greedy_solution);
//
//    float sum_all_routes = 0;
//    cout<< endl;
//    cout << "\t\t\t\tILS-METAHEURISTIC" << endl;
//    cout << "-----------------------------------------------------------------------------" <<endl;
//
//   /* cout << "[ ";
//    for (int m = 0; m < greedy_solution.size(); m++)
//    {
//        //cout << "[ ";
//        for (int n = 0; n < final_solution.at(m).size(); n++)
//        {
//            if(n == final_solution.at(m).size()-1) {
//                cout << final_solution[m][n];
//                break;
//            }
//            cout << final_solution[m][n] << ", ";
//
//        }
//        cout << "; " << endl;
//        //cout << "Best solution: " << final_route[m] << ", vehicle: " << m << endl;
//        sum_all_routes += final_route[m];
//        //cout << "---------------------------" << endl;
//    }*/
//    cout << " ]" << endl;
//    cout << "All routes were summed and we've obtained: " << sum_all_routes << endl;
    return 0;
}   