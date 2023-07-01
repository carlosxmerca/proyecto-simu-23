#include <fstream>

// Function to read input data from a file and populate the Mesh object
void read_input(string filename, Mesh* M){
    string line;
    float k, Q, T_bar, T_hat;
    int num_nodes, num_elements, num_dirichlet, num_neumann;
    ifstream dat_file(filename+".dat");

    // Read problem data and quantities from the file
    dat_file >> k >> Q >> T_bar >> T_hat >> num_nodes >> num_elements >> num_dirichlet >> num_neumann;
    
    // Set problem data and quantities in the Mesh object
    M->set_problem_data(k,Q);
    M->set_quantities(num_nodes,num_elements,num_dirichlet,num_neumann);

    // Initialize arrays in the Mesh object
    M->init_arrays();

    dat_file >> line;

    // Read node data and insert nodes into the Mesh object
    for(int i = 0; i < num_nodes; i++){
        int id;
        float x, y, z;
        dat_file >> id >> x >> y >> z;
        M->insert_node(new Node(id,x,y,z), i);
    }

    dat_file >> line >> line;

    // Read element data and insert elements into the Mesh object
    for(int i = 0; i < num_elements; i++){
        int id, node1_id, node2_id, node3_id, node4_id;
        dat_file >> id >> node1_id >> node2_id >> node3_id >> node4_id;
        M->insert_element(new Element(id, M->get_node(node1_id-1), M->get_node(node2_id-1), M->get_node(node3_id-1), M->get_node(node4_id-1)), i);
    }

    dat_file >> line >> line;

    // Read Dirichlet boundary conditions and insert them into the Mesh object
    for(int i = 0; i < num_dirichlet; i++){
        int id;
        dat_file >> id;
        M->insert_dirichlet_condition(new Condition(M->get_node(id-1), T_bar), i);
    }

    dat_file >> line >> line;

    // Read Neumann boundary conditions and insert them into the Mesh object
    for(int i = 0; i < num_neumann; i++){
        int id;
        dat_file >> id;
        M->insert_neumann_condition(new Condition(M->get_node(id-1), T_hat), i);
    }

    dat_file.close();
}

// Function to write output data to a file
void write_output(string filename, Vector* T){
    ofstream res_file(filename+".post.res");
    
    // Write file header
    res_file << "GiD Post Results File 1.0\n";

    int n = T->get_size();

    // Write result data
    res_file << "Result \"Temperature\" \"Load Case 1\" " << 1 << " Scalar OnNodes\n";
    res_file << "ComponentNames \"T\"\n";
    res_file << "Values\n";

    // Write temperature values for each node
    for(int i = 0; i < n; i++)
        res_file << i+1 << "     " << T->get(i) << "\n";

    res_file << "End values\n";

    res_file.close();
}
