#include "ILS.h"
#include "cup_matrix.h"


using namespace std;



int main(int argc, char *argv[ ]) {

    string instancies[] = {"./instancias_teste/P-n16-k8.txt","./instancias_teste/P-n19-k2.txt","./instancias_teste/P-n20-k2.txt",
                        "./instancias_teste/P-n23-k8.txt","./instancias_teste/P-n55-k7.txt","./instancias_teste/P-n51-k10.txt",
                        "./instancias_teste/P-n50-k10.txt", "./instancias_teste/P-n45-k5.txt"};

    clock_t Ticks[2];
    double meta_time[8]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
    double constr_time[8]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
    

    int great_sol_instancies[] = {450,212,216,529,510,696,741,568};
    bool type = atoi(argv[1]);
    int ils_iterations = atoi(argv[2]);
    double code_iterations = atoi(argv[3]);


    int sum_route=INT_MAX, temp_sum_route=0;
    float media_instance_meta[8]={0}, gap_meta[8]={0}, temp_sum_meta[8]={0}, final_sum_meta[8], sum_media_meta[8]={0};
    float gap_constr[8]={0}, media_instance_constr[8]={0}, temp_sum_constr[8]={0}, final_sum_constr[8],sum_media_constr[8]={0};

    for (int y = 0; y < 8; y++)
    {
    
       final_sum_meta[y] = INT_MAX;
       final_sum_constr[y] = INT_MAX;
    }
    
    vector<vector<int>> vnd_solution;
    vector<vector<int>> swap_solution;
    vector<vector<int>> twoOpt_solution;
    vector<vector<int>> inverter_solution;
    vector<vector<int>> greedy_solution;

    vector<vector<int>> final_solution;
    vector<vector<int>> temp_final_solution;

    vector<vector<int> > matrix;

    int n_files = 0;
    vector<int> greedy_distance;
    vector<int> final_route;
    vector<int> best_final_route;
    vector<vector<int>> coordinates;
    int sum_distances = 0;
    
    string buffer;
    char linha[50];
    char delimiter[3] = ": ", *sC = {0}, *sV = {0}, *sD = {0}, buf[100] = {0}, *pch = {0}, *dem = {0};

    vector<int> demand_section;
    int i = 0, dimension = 0, vehicles = 0, capacity = 0, l = -1, c = 0, j = -1, k = 0, valor, s = 0;

    if(type == 0){
        n_files=1;
    }else if(type == 1){
        n_files=8;
    }

    

    

    for (int l=0; l < n_files; l++){

        for (int it = 0; it < code_iterations; it++){

            Ticks[0] = clock();
            
            ifstream arq_instancies(instancies[l]);
            ifstream arq_cvrpcup(argv[4]);
            
            if(type==0){
                if (arq_cvrpcup) {

                    while (getline(arq_cvrpcup, buffer)) {

                        if (i == 1) {
                            strcpy(linha, buffer.c_str());
                            sD = strchr(linha, ' ');
                            sD++;
                            dimension = atoi(sD);


                        } else if (i == 2) {
                            strcpy(linha, buffer.c_str());
                            sV = strchr(linha, ' ');
                            sV++;
                            vehicles = atoi(sV);

                        } else if (i == 3) {
                            strcpy(linha, buffer.c_str());
                            sC = strchr(linha, ' ');
                            sC++;
                            capacity = atoi(sC);

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
                    matrix = Transpose(coordinates, dimension);

                }else
                {
                    system("clear || cls");
                    cout << endl << "FILE NOT FOUND. ->" <<argv[4]<< endl << endl;
                    return 0;
                }
            }    
            else if(type == 1){
            
                if (arq_instancies) {

                    while (getline(arq_instancies, buffer)) {

                        if (i == 1) {
                            strcpy(linha, buffer.c_str());
                            sD = strchr(linha, ' ');
                            sD++;
                            dimension = atoi(sD);


                        } else if (i == 2) {
                            strcpy(linha, buffer.c_str());
                            sV = strchr(linha, ' ');
                            sV++;
                            vehicles = atoi(sV);

                        } else if (i == 3) {
                            strcpy(linha, buffer.c_str());
                            sC = strchr(linha, ' ');
                            sC++;
                            capacity = atoi(sC);

                        } else if (i >= 5 && i < (dimension + 5)) {
                
                            strcpy(linha, buffer.c_str());
                            dem = strchr(linha, ' ');
                            dem++;
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
                    matrix = coordinates;
                }else
                {
                    system("clear || cls");
                    cout << endl << "FILE NOT FOUND: " <<argv[4]<<endl << endl;
                    return 0;
                }
                

            }


            vehicles = 0;
           
            
            temp_final_solution = ILS(greedy_distance, final_route, vnd_solution, dimension, matrix, vehicles, ils_iterations,
                                capacity, demand_section, swap_solution, twoOpt_solution,
                                inverter_solution, greedy_solution, code_iterations, it+1, constr_time, l+1, n_files);
           

            
           
            if(it == 0){
                final_solution = temp_final_solution;
                best_final_route = final_route;
            }

           

            if (type == 1)
            {

                for (int h = 0; h < final_route.size(); h++){             
                    temp_sum_meta[l] += final_route[h];
                    temp_sum_constr[l] += greedy_distance[h];
                }
                    
                sum_media_meta[l] += temp_sum_meta[l];
                sum_media_constr[l] += temp_sum_constr[l];

                if (temp_sum_meta[l] < final_sum_meta[l])
                    final_sum_meta[l] = temp_sum_meta[l];
                
                if(temp_sum_constr[l]<final_sum_constr[l])
                    final_sum_constr[l]=temp_sum_constr[l];

                 

            }
            else if(type == 0){

                for (int h = 0; h < final_route.size(); h++)             
                    temp_sum_route += final_route.at(h);
                

                if (temp_sum_route < sum_route)
                {
                    final_solution = temp_final_solution;
                    sum_route = temp_sum_route;
                    best_final_route = final_route;
                }
                
                
                
                
            }

            temp_sum_constr[l] = 0;
            temp_sum_meta[l] = 0;

            Ticks[1] = clock();

            meta_time[l] += (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;

        }
    }

    cout<<endl;
    cout<<endl;
    cout<<endl;

    if (type == 1)
    {

        for (int i = 0; i < n_files; i++)
        {   
            meta_time[i] = meta_time[i]/code_iterations;
            gap_meta[i] = (((final_sum_meta[i]-great_sol_instancies[i])/great_sol_instancies[i])*100); 
            media_instance_meta[i] = sum_media_meta[i]/code_iterations;

            constr_time[i] = constr_time[i]/code_iterations;
            gap_constr[i] = (((final_sum_constr[i]-great_sol_instancies[i])/great_sol_instancies[i])*100);
            media_instance_constr[i] = sum_media_constr[i]/code_iterations;

            
          

        }

        ofstream myfile;
        myfile.open ("cvrp-output.txt");
        myfile << "\t\t\t\t\t\t\t HEURISTICA CONSTRUTIVA\t\t\t\tMETA-HEURISTICA\n";
        myfile << "\t\t\t\t\t    -----------------------------------\t  -----------------------------------\n";
        myfile << "\t\t\t\tOTIMO    MEDIA     MELHOR     MEDIA     GAP     MEDIA     MELHOR     MEDIA    GAP\n";
        myfile << "\t\t\t\t        SOLUCAO    SOLUCAO    TEMPO            SOLUCAO    SOLUCAO    TEMPO \n";
          myfile << "-------------------------------------------------------------------------------------------------\n";
        for (i = 0; i < n_files; i++)
        { 
            myfile << "INSTANCIA[" <<i<<"]:     " << great_sol_instancies[i]<< "      " << media_instance_constr[i]<< "         " << final_sum_constr[i]<< "    " 
                   << constr_time[i] <<"      "<< gap_constr[i] <<"      " << media_instance_meta[i]<< "         " << final_sum_meta[i]<< "      "<<meta_time[i] << "      " <<gap_meta[i] << endl;
        }
        

        cout << endl <<"TABELA GERADA." << endl;
        
        myfile.close();

    }else if(type == 0){  

    
        cout<< endl;
        cout << "\t\t\t\tILS-METAHEURISTIC" << endl;
        cout << "-----------------------------------------------------------------------------" <<endl;

        int distance = 0;
        int sum=0, n, m;    

    for (m = 0; m < final_solution.size(); m++)
        {
            for (n = 0; n < final_solution.at(m).size()-1; n++)
            {
                distance += matrix[final_solution.at(m).at(n)][final_solution.at(m).at(n+1)];
                cout << final_solution[m][n] << ", ";
            }
            cout << final_solution[m][n];
            sum += best_final_route.at(m);
            cout << "; " << endl;
        }
        cout << "Distance Travelled: " << distance << endl;
        cout << "SOLUTION SIZE (NUMBER OF ROUTES): " << final_solution.size() << endl;
    }   





    return 0;
}   