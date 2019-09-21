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
#include <random>
#include <time.h>
#include <limits.h>
#include <vector>
#include <algorithm>
using namespace std;


char archive = 'E:\\Universit\\P5\\APA\\pj_ew_c\\instancias_teste\\cvrp-cup\\cvrp1.txt';

int main(){

    char delimiter[3] = ": ", *sC = {0}, *sV = {0}, *sD = {0}, buf[100] = {0}, *pch = {0}, *dem = {0};
    char linha[50];
    string buffer;
    int i = 0;
    vector<vector<int>> matrix;
    ifstream arq(archive);

    if (arq)
    {

        while (getline(arq, buffer))
        {
            if (i == 1)
            {
                strcpy(linha, buffer.c_str());
                sD = strchr(linha, ' ');
                sD++;
                dimension = atoi(sD);
                cout << "Dimension: " << dimension << endl;
            }
            else if (i >= (dimension + 7) && i < (dimension * 2) + 7)
            {

                    matrix.push_back(vector<int>());

                    stringstream split(buffer);

                    while (split >> valor)
                        matrix.back().push_back(valor);
            }
            i++;
        }
    }
}