#include <cmath>
#include <fstream>
#include <ctime>

// Function to get the current timestamp as a string
string getCurrentTimestamp() {
    time_t now = time(nullptr);
    char timestamp[80];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(timestamp);
}

#include "vector.hpp"
#include "matrix.hpp"

// Function to calculate the product of a scalar and a matrix
void product_scalar_by_matrix(float scalar, Matrix* M, int n, int m, Matrix* R) {
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            R->set(scalar * M->get(r, c), r, c);
}

// Function to calculate the product of a matrix and a vector
void product_matrix_by_vector(Matrix* M, Vector* V, int n, int m, Vector* R) {
    for (int r = 0; r < n; r++) {
        float acc = 0;
        for (int c = 0; c < n; c++)
            acc += M->get(r, c) * V->get(c);
        R->set(acc, r);
    }
}

// Function to calculate the product of two matrices
void product_matrix_by_matrix(Matrix* A, Matrix* B, Matrix* R) {
    int n = A->get_nrows(), m = A->get_ncols(), p = B->get_nrows(), q = B->get_ncols();
    if (m == p) {
        R->set_size(n, q);
        R->init();

        for (int r = 0; r < n; r++)
            for (int c = 0; c < q; c++)
                for (int i = 0; i < m; i++)
                    R->add(A->get(r, i) * B->get(i, c), r, c);
    } else {
        cout << "Incompatibilidad de dimensiones al multiplicar matrices.\n\nAbortando...\n";
        exit(EXIT_FAILURE);
    }
}

void transpose(Matrix* M, int n, int m, Matrix* T) {
    for (int r = 0; r < n; r++)
        for (int c = 0; c < m; c++)
            T->set(M->get(r, c), c, r);
}

// Function to calculate the inverse of a matrix using the Cholesky method
void calculate_inverse(Matrix* A, int n, Matrix* X) {
    Matrix L(n, n), Y(n, n);
    float acum;
    ofstream timesFile("time_report/calculate_inverse.txt", ios::app);

    cout << "\t\tCalculating L...\n\n";
    timesFile << "[" << getCurrentTimestamp() << "] Calculating L...\n\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                acum = 0;
                for (int k = 0; k < j; k++) {
                    acum += pow(L.get(j, k), 2);
                }
                L.set(sqrt(A->get(j, j) - acum), j, j);
            } else {
                if (i > j) {
                    acum = 0;
                    for (int k = 0; k < j; k++) {
                        acum += L.get(i, k) * L.get(j, k);
                    }
                    L.set((1 / L.get(j, j)) * (A->get(i, j) - acum), i, j);
                } else {
                    L.set(0, i, j);
                }
            }
        }
    }

    cout << "\t\tCalculating Y...\n\n";
    timesFile << "[" << getCurrentTimestamp() << "] Calculating Y...\n\n";

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                Y.set(1 / L.get(i, i), i, i);
            } else {
                if (i > j) {
                    acum = 0;
                    for (int k = j; k < i; k++) {
                        acum += L.get(i, k) * Y.get(k, j);
                    }
                    Y.set(-(1 / L.get(i, i)) * acum, i, j);
                } else {
                    Y.set(0, i, j);
                }
            }
        }
    }

    cout << "\t\tCalculating X...\n\n";
    timesFile << "[" << getCurrentTimestamp() << "] Calculating X...\n\n";

    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            acum = 0;
            for (int k = i + 1; k < n; k++) {
                acum += L.get(k, i) * X->get(k, j);
            }
            X->set((1 / L.get(i, i)) * (Y.get(i, j) - acum), i, j);
        }
    }
}
