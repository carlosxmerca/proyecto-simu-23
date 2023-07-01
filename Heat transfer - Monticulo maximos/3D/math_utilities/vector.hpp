class Vector {
    private:
        int size;
        float* data;

        // Function to allocate memory for the vector
        void create(){
            data = (float*) malloc(sizeof(float) * size);
        }

    public:
        Vector(){}

        // Constructor to create a vector with specified size
        Vector(int data_qty){
            size = data_qty;
            create();
        }

        // Destructor to release memory
        ~Vector(){
            free(data);
        }

        // Function to initialize the vector with zeros
        void init(){
            for(int i = 0; i < size; i++)
                data[i] = 0;
        }

        // Function to set the size of the vector
        void set_size(int num_values){
            size = num_values;
            create();
        }

        // Function to get the size of the vector
        int get_size(){
            return size;
        }

        // Function to set a value at a specific position in the vector
        void set(float value, int position){
            data[position] = value;
        }

        // Function to add a value to a specific position in the vector
        void add(float value, int position){
            data[position] += value;
        }

        // Function to get the value at a specific position in the vector
        float get(int position){
            return data[position];
        }

        // Function to remove an element from the vector
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

        // Function to display the vector
        void show(){
            cout << "[ " << data[0];
            for(int i = 1; i < size; i++)
                cout << "; " << data[i];
            cout << " ]\n\n";
        }
};
