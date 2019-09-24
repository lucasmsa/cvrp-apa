#ifndef PJ_FINAL_CUP_MATRIX_H
#define PJ_FINAL_CUP_MATRIX_H

#include "greedyfunction.h"
#include "neighborhood.h"

using namespace std;

vector<vector<int >> Transpose(vector<vector<int>> &matrix, int dimension) {
    int b = 0, a = 0, k = 0, o = 0;

    vector<vector<int >> transposed_matrix;
    for (k = 0; k < dimension; k++) {
        vector<int> p;
        for (o = 0; o < dimension; o++) {
            p.push_back(0.0);
        }
        transposed_matrix.push_back(p);
    }

    while (a < dimension) {
        if (a == 0) {
            b = 1;
        }
        while (b < dimension) {
            transposed_matrix.at(a).at(b) = int(
                    round(sqrt(pow(matrix[a][1] - matrix[b][1], 2) + pow(matrix[a][2] - matrix[b][2], 2))));
            transposed_matrix[b][a] = transposed_matrix[a][b];
            if (a == b)
                transposed_matrix[a][b] = 0;
            b += 1;
        }
        a += 1;
        b = 0;
    }

    return transposed_matrix;
}

#endif //PJ_FINAL_CUP_MATRIX_H
