#include <stdio.h>

class Matrix {
    private:
        int nrows, ncols;
        float** data;

        // Helper function to allocate memory for the matrix data
        void create(){
            data = (float**) malloc(sizeof(float*) * nrows);
            for(int r = 0; r < nrows; r++)
                data[r] = (float*) malloc(sizeof(float) * ncols);
        }

    public:
        Matrix(){}
        
        // Constructor that allows specifying the number of rows and columns
        Matrix(int rows, int cols){
            nrows = rows;
            ncols = cols;
            create();
        }
        
        // Destructor to release dynamically allocated memory
        ~Matrix(){
            for(int r = 0; r < nrows; r++)
                free(data[r]);
            free(data);
        }

        // Initialize all matrix elements to zero
        void init(){
            for(int r = 0; r < nrows; r++)
                for(int c = 0; c < ncols; c++)
                    data[r][c] = 0;
        }

        // Change the size of the matrix
        void set_size(int rows, int cols){
            nrows = rows;
            ncols = cols;
            create();
        }
        
        // Get the number of rows
        int get_nrows(){
            return nrows;
        }
        
        // Get the number of columns
        int get_ncols(){
            return ncols;
        }

        // Set the value of a specific matrix element
        void set(float value, int row, int col){
            data[row][col] = value;
        }
        
        // Add a value to a specific matrix element
        void add(float value, int row, int col){
            data[row][col] += value;
        }
        
        // Get the value of a specific matrix element
        float get(int row, int col){
            return data[row][col];
        }

        // Remove a row from the matrix
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

        // Remove a column from the matrix
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

        // Clone the matrix into another Matrix object
        void clone(Matrix* other){
            for(int r = 0; r < nrows; r++)
                for(int c = 0; c < ncols; c++)
                    other->set(data[r][c],r,c);
        }

        // Display the matrix
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
