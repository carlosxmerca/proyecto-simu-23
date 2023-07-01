#include <stdio.h>

class Matrix {
    private:
        int nrows, ncols;
        float** data;

        void create(){
            // Allocating memory for the matrix data
            data = (float**) malloc(sizeof(float*) * nrows);
            for(int r = 0; r < nrows; r++)
                data[r] = (float*) malloc(sizeof(float) * ncols);
        }

    public:
        Matrix(){}
        Matrix(int rows, int cols){
            nrows = rows;
            ncols = cols;
            create();
        }
        ~Matrix(){
            // Freeing the allocated memory for the matrix data
            for(int r = 0; r < nrows; r++)
                free(data[r]);
            free(data);
        }

        void init(){
            // Initializing all elements of the matrix to 0
            for(int r = 0; r < nrows; r++)
                for(int c = 0; c < ncols; c++)
                    data[r][c] = 0;
        }

        void set_size(int rows, int cols){
            // Changing the size of the matrix and reallocating memory
            nrows = rows;
            ncols = cols;
            create();
        }
        int get_nrows(){
            // Returning the number of rows in the matrix
            return nrows;
        }
        int get_ncols(){
            // Returning the number of columns in the matrix
            return ncols;
        }

        void set(float value, int row, int col){
            // Setting the value of a specific element in the matrix
            data[row][col] = value;
        }
        void add(float value, int row, int col){
            // Adding a value to a specific element in the matrix
            data[row][col] += value;
        }
        float get(int row, int col){
            // Getting the value of a specific element in the matrix
            return data[row][col];
        }

        void remove_row(int row){
            // Removing a row from the matrix
            int neo_index = 0;
            float** neo_data = (float**) malloc(sizeof(float*) * (nrows-1));
            for(int i = 0; i < nrows; i++)
                if(i != row){
                    neo_data[neo_index] = data[i];
                    neo_index++;
                }
            // Freeing memory for the removed row and the old matrix data
            free(data[row]);
            free(data);
            // Updating the matrix data with the new row-removed data
            data = neo_data;
            nrows--;
        }

        void remove_column(int col){
            // Removing a column from the matrix
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
            // Freeing memory for the removed column and the old matrix data
            for(int r = 0; r < nrows; r++)
                free(data[r]);
            free(data);
            // Updating the matrix data with the new column-removed data
            data = neo_data;
            ncols--;
        }

        void clone(Matrix* other){
            // Cloning the matrix into another matrix object
            for(int r = 0; r < nrows; r++)
                for(int c = 0; c < ncols; c++)
                    other->set(data[r][c],r,c);
        }

        void show(){
            // Displaying the matrix elements
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
