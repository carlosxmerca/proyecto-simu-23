class Vector {
    private:
        int size;
        float* data;

        void create(){
            // Allocating memory for the vector data
            data = (float*) malloc(sizeof(float) * size);
        }

    public:
        Vector(){}
        Vector(int data_qty){
            size = data_qty;
            create();
        }
        ~Vector(){
            // Freeing the allocated memory for the vector data
            free(data);
        }

        void init(){
            // Initializing all elements of the vector to 0
            for(int i = 0; i < size; i++)
                data[i] = 0;
        }

        void set_size(int num_values){
            // Changing the size of the vector and reallocating memory
            size = num_values;
            create();
        }
        int get_size(){
            // Returning the size of the vector
            return size;
        }

        void set(float value, int position){
            // Setting the value of a specific element in the vector
            data[position] = value;
        }
        void add(float value, int position){
            // Adding a value to a specific element in the vector
            data[position] += value;
        }
        float get(int position){
            // Getting the value of a specific element in the vector
            return data[position];
        }

        void remove_row(int row){
            // Removing an element from the vector
            int neo_index = 0;
            float* neo_data = (float*) malloc(sizeof(float) * (size-1));
            for(int i = 0; i < size; i++)
                if(i != row){
                    neo_data[neo_index] = data[i];
                    neo_index++;
                }
            // Freeing memory for the removed element and the old vector data
            free(data);
            // Updating the vector data with the new element-removed data
            data = neo_data;
            size--;
        }

        void show(){
            // Displaying the vector elements
            cout << "[ " << data[0];
            for(int i = 1; i < size; i++)
                cout << "; " << data[i];
            cout << " ]\n\n";
        }
};
