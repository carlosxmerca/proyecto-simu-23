class Node {
    private:
        // Each node has a unique ID
        int ID;
        // Properties used to store the coordinates in (x,y,z) of a Node
        float x_coordinate;
        float y_coordinate;
        float z_coordinate;

    public:
        // The Node constuctor sets the Id and the coordinates of the Node
        Node(int identifier, float x_value, float y_value, float z_value){
            ID = identifier;
            x_coordinate = x_value;
            y_coordinate = y_value;
            z_coordinate = z_value;
        }

        // Sets the value of the Node's ID
        void set_ID(int identifier){
            ID = identifier;
        }
        // Returns the value of the Node's ID
        int get_ID(){
            return ID;
        }

        // Sets the value of the Node's x coordinate
        void set_x_coordinate(float x_value){
            x_coordinate = x_value;
        }
        // Returns the value of the Node's x coordinate
        float get_x_coordinate(){
            return x_coordinate;
        }

        // Sets the value of the Node's y coordinate
        void set_y_coordinate(float y_value){
            y_coordinate = y_value;
        }
        // Returns the value of the Node's y coordinate
        float get_y_coordinate(){
            return y_coordinate;
        }

        // Sets the value of the Node's z coordinate
        void set_z_coordinate(float z_value){
            z_coordinate = z_value;
        }
        // Returns the value of the Node's z coordinate
        float get_z_coordinate(){
            return z_coordinate;
        }
};
