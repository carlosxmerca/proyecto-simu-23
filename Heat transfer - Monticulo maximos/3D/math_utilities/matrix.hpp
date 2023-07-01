#include <stdio.h>

class Matrix {
    private:
        int nrows, ncols;
        float** data;

        // Function to allocate memory for the matrix
        void create(){
            data = (float**) malloc(sizeof(float*) * nrows);
            for(int r = 0; r < nrows; r++)
                data[r] = (float*) malloc(sizeof(float) * ncols);
        }

    public:
        Matrix(){}

        // Constructor to create a matrix with specified rows and columns
        Matrix(int rows, int cols){
            nrows = rows;
            ncols = cols;
            create();
        }

        // Destructor to release memory
        ~Matrix(){
            for(int r = 0; r < nrows; r++)
                free(data[r]);
            free(data);
        }

        // Function to initialize the matrix with zeros
        void init(){
            for(int r = 0; r < nrows; r++)
                for(int c = 0; c < ncols; c++)
                    data[r][c] = 0;
        }

        // Function to set the size of the matrix
        void set_size(int rows, int cols){
            nrows = rows;
            ncols = cols;
            create();
        }

        // Function to get the number of rows in the matrix
        int get_nrows(){
            return nrows;
        }

        // Function to get the number of columns in the matrix
        int get_ncols(){
            return ncols;
        }

        // Function to set a value at a specific position in the matrix
        void set(float value, int row, int col){
            data[row][col] = value;
        }

        // Function to add a value to a specific position in the matrix
        void add(float value, int row, int col){
            data[row][col] += value;
        }

        // Function to get the value at a specific position in the matrix
        float get(int row, int col){
            return data[row][col];
        }

        // Function to remove a row from the matrix
        void remove_row(int row){
            int neo_index = 0;
            float** neo_data = (float**) malloc(sizeof(float*) * (nrows-1));
            for(int i = 0; i < nrows; i++)
                if(i != row){
                    neo_data[neo_index] = data[i];
                    neo_index++;
                }
            free(data[row]);
            free(data);
            data = neo_data;
            nrows--;
        }

        // Function to remove a column from the matrix
        void remove_column(int col){
            int neo_index = 0;
            float** neo_data = (float**) malloc(sizeof(float*) * nrows);
            for(int r = 0; r < nrows; r++)
                neo_data[r] = (float*) malloc(sizeof(float) * (ncols-1));

            for(int r = 0; r < nrows; r++){
                for(int c = 0; c < ncols; c++)
                    if(c != col){
                        neo_data[r][neo_index] = data[r][c];
                        neo_index++;
                    }
                neo_index = 0;
            }
            for(int r = 0; r < nrows; r++)
                free(data[r]);
            free(data);
            data = neo_data;
            ncols--;
        }

        // Function to clone the matrix into another matrix
        void clone(Matrix* other){
            for(int r = 0; r < nrows; r++)
                for(int c = 0; c < ncols; c++)
                    other->set(data[r][c],r,c);
        }

        // Function to display the matrix
        void show(){
            cout << "[ ";
            for(int r = 0; r < nrows; r++){
                cout << "[ " << data[r][0];
                for(int c = 1; c < ncols; c++){
                    cout << ", " << data[r][c];
                }
                cout << " ] ";
            }
            cout << " ]\n\n";
        }
};
