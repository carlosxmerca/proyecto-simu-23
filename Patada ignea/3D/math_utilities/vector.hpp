class Vector {
    private:
        int size;
        float* data;

        // Helper function to allocate memory for the vector data
        void create(){
            data = (float*) malloc(sizeof(float) * size);
        }

    public:
        Vector(){}
        
        // Constructor that allows specifying the size of the vector
        Vector(int data_qty){
            size = data_qty;
            create();
        }
        
        // Destructor to release dynamically allocated memory
        ~Vector(){
            free(data);
        }

        // Initialize all vector elements to zero
        void init(){
            for(int i = 0; i < size; i++)
                data[i] = 0;
        }

        // Change the size of the vector
        void set_size(int num_values){
            size = num_values;
            create();
        }
        
        // Get the size of the vector
        int get_size(){
            return size;
        }

        // Set the value of a specific vector element
        void set(float value, int position){
            data[position] = value;
        }
        
        // Add a value to a specific vector element
        void add(float value, int position){
            data[position] += value;
        }
        
        // Get the value of a specific vector element
        float get(int position){
            return data[position];
        }

        // Remove an element from the vector
        void remove_row(int row){
            int neo_index = 0;
            float* neo_data = (float*) malloc(sizeof(float) * (size-1));
            for(int i = 0; i < size; i++)
                if(i != row){
                    neo_data[neo_index] = data[i];
                    neo_index++;
                }
            free(data);
            data = neo_data;
            size--;
        }

        // Display the vector
        void show(){
            cout << "[ " << data[0];
            for(int i = 1; i < size; i++)
                cout << "; " << data[i];
            cout << " ]\n\n";
        }
};
