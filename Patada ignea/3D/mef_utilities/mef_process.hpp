#include <fstream>
#include <ctime>

// This function calculates the local volume of a Element
// Based in the coordinates (x,y,z) of the 4 nodes that conform the element
float calculate_local_volume(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4)
{
    float A = abs((x2 - x1) * (y3 - y1) * (z4 - z1) + (y2 - y1) * (z3 - z1) * (x4 - x1) + (x3 - x1) * (y4 - y1) * (z2 - z1) - (z2 - z1) * (y3 - y1) * (x4 - x1) - (y2 - y1) * (x3 - x1) * (z4 - z1) - (z3 - z1) * (y4 - y1) * (x2 - x1)) / 6;
    return ((A==0)?0.000001:A);
}

// This function calculates the local Jacobian of a Element
// Based in the coordinates (x,y,z) of the 4 nodes that conform the element
float calculate_local_jacobian(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4)
{
    float J = (x2 - x1) * (y3 - y1) * (z4 - z1) - (x2 - x1) * (y4 - y1) * (z3 - z1) - (x3 - x1) * (y2 - y1) * (z4 - z1) + (x3 - x1) * (y4 - y1) * (z2 - z1) + (x4 - x1) * (y2 - y1) * (z3 - z1) - (x4 - x1) * (y3 - y1) * (z2 - z1);
    return ((J==0)?0.000001:J);
}

// This function creates the Matrix A of a Element
// Based in the coordinates (x,y,z) of the 4 nodes that conform the element
void calculate_local_A(Matrix *A, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, float x4, float y4, float z4)
{

    A->set((y3 - y1) * (z4 - z1) - (y4 - y1) * (z3 - z1), 0, 0);
    A->set(-(x3 - x1) * (z4 - z1) + (x4 - x1) * (z3 - z1), 0, 1);
    A->set((x3 - x1) * (y4 - y1) - (x4 - x1) * (y3 - y1), 0, 2);
    A->set(-(y2 - y1) * (z4 - z1) + (y4 - y1) * (z2 - z1), 1, 0);
    A->set((x2 - x1) * (z4 - z1) - (x4 - x1) * (z2 - z1), 1, 1);
    A->set(-(x2 - x1) * (y4 - y1) + (x4 - x1) * (y2 - y1), 1, 2);
    A->set((y2 - y1) * (z3 - z1) - (y3 - y1) * (z2 - z1), 2, 0);
    A->set(-(x2 - x1) * (z3 - z1) + (x3 - x1) * (z2 - z1), 2, 1);
    A->set((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1), 2, 2);
}

// This function creates the Matrix B -> it will be the same to all elements
void calculate_B(Matrix *B)
{
    B->set(-1, 0, 0);
    B->set(1, 0, 1);
    B->set(0, 0, 2);
    B->set(0, 0, 3);
    B->set(-1, 1, 0);
    B->set(0, 1, 1);
    B->set(1, 1, 2);
    B->set(0, 1, 3);
    B->set(-1, 2, 0);
    B->set(0, 2, 1);
    B->set(0, 2, 2);
    B->set(1, 2, 3);
}

// This function creates the local K Matrix of dimens n x n of a Element
void create_local_K(Matrix *K, int element_id, Mesh *M)
{
    // Local K will always be 4x4 in 3D
    K->set_size(4, 4);

    // Get the value of Thermal Conductivity
    float x1 = M->get_element(element_id)->get_node1()->get_x_coordinate(), y1 = M->get_element(element_id)->get_node1()->get_y_coordinate(), z1 = M->get_element(element_id)->get_node1()->get_z_coordinate(),
          x2 = M->get_element(element_id)->get_node2()->get_x_coordinate(), y2 = M->get_element(element_id)->get_node2()->get_y_coordinate(), z2 = M->get_element(element_id)->get_node2()->get_z_coordinate(),
          x3 = M->get_element(element_id)->get_node3()->get_x_coordinate(), y3 = M->get_element(element_id)->get_node3()->get_y_coordinate(), z3 = M->get_element(element_id)->get_node3()->get_z_coordinate(),
          x4 = M->get_element(element_id)->get_node4()->get_x_coordinate(), y4 = M->get_element(element_id)->get_node4()->get_y_coordinate(), z4 = M->get_element(element_id)->get_node4()->get_z_coordinate();

    // Get local Volume of this element
    float J = calculate_local_jacobian(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);

    // In order of resolving the next stepts the function will need the B Matrix and the local A Matrix
    Matrix B(3, 4), A(3, 3);
    calculate_B(&B);
    calculate_local_A(&A, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
    // B.show(); A.show();

    // Also in order of resolving the next stepts the function will need the B transpose Matrix and the local A transpose Matrix
    Matrix Bt(4, 3), At(3, 3);
    transpose(&B, 3, 4, &Bt); // Create transpose of B matrix
    transpose(&A, 3, 3, &At); // Create transpose of A matrix
    // Bt.show(); At.show();

    // The next steps are the solution of this arithmetical and matrix operations
    // (1 /(J * 1260)) * Bt * At * A * B
    // Note: This will variate based in the phenomena being studied

    Matrix res1, res2, res3;
    // First calculate the product of (A x B) and store it in res1
    product_matrix_by_matrix(&A, &B, &res1);
    // Second calculate the product of (At x res1) and store it in res2
    product_matrix_by_matrix(&At, &res1, &res2);
    // Then calculate the product of (Bt x res2) and store it in res3
    product_matrix_by_matrix(&Bt, &res2, &res3);
    // Finally calculate the product of ((k*Volume/(J*J)) x res3) and store it in local K Matrix
    product_scalar_by_matrix(1 / (J * 1260), &res3, 4, 4, K);

    // cout << "\t\tLocal matrix created for Element " << element_id+1 << ": "; K->show(); cout << "\n";
}

// This function will create a local b vector for a particular element
void create_local_b(Vector *b, int element_id, Mesh *M)
{
    // The size of this vectors will always be 4 in 3D
    b->set_size(4);

    // Get the coordinates (x,y,z) of the 4 nodes that conform the element
    float x1 = M->get_element(element_id)->get_node1()->get_x_coordinate(), y1 = M->get_element(element_id)->get_node1()->get_y_coordinate(), z1 = M->get_element(element_id)->get_node1()->get_z_coordinate(),
          x2 = M->get_element(element_id)->get_node2()->get_x_coordinate(), y2 = M->get_element(element_id)->get_node2()->get_y_coordinate(), z2 = M->get_element(element_id)->get_node2()->get_z_coordinate(),
          x3 = M->get_element(element_id)->get_node3()->get_x_coordinate(), y3 = M->get_element(element_id)->get_node3()->get_y_coordinate(), z3 = M->get_element(element_id)->get_node3()->get_z_coordinate(),
          x4 = M->get_element(element_id)->get_node4()->get_x_coordinate(), y4 = M->get_element(element_id)->get_node4()->get_y_coordinate(), z4 = M->get_element(element_id)->get_node4()->get_z_coordinate();
    // Get local Jacobian of this element
    float J = calculate_local_jacobian(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);

    // The values that will be stored in the vector b will variate based in the phenomena being studied
    b->set(J / 252, 0);
    b->set(J / 252, 1);
    b->set((J * 11) / 840, 2);
    b->set(J / 252, 3);

    // cout << "\t\tLocal vector created for Element " << element_id+1 << ": "; b->show(); cout << "\n";
}

// This function is in charge of creating all the local system Ks and bs
void create_local_systems(Matrix *Ks, Vector *bs, int num_elements, Mesh *M)
{
    // It iterates over the elements of the mesh and for each element it creates a K and a b
    // This Matrix K is stored in Ks Array and Vector b in bs Array
    for (int e = 0; e < num_elements; e++)
    {
        cout << "\tCreating local system for Element " << e + 1 << "...\n\n";
        create_local_K(&Ks[e], e, M);
        create_local_b(&bs[e], e, M);
    }
}

// It will Assembly the K Matrix, for doing that this functions gets a local_K Matrix 
// and the indexes of the current element nodes, in order to assemby it gets the values of local_K
// and adds them to the Matrix K based in the relations of indexes provided.
// NOTE: Remember that a node ID has a relation with it's index
void assembly_K(Matrix *K, Matrix *local_K, int index1, int index2, int index3, int index4)
{
    K->add(local_K->get(0, 0), index1, index1);
    K->add(local_K->get(0, 1), index1, index2);
    K->add(local_K->get(0, 2), index1, index3);
    K->add(local_K->get(0, 3), index1, index4);
    K->add(local_K->get(1, 0), index2, index1);
    K->add(local_K->get(1, 1), index2, index2);
    K->add(local_K->get(1, 2), index2, index3);
    K->add(local_K->get(1, 3), index2, index4);
    K->add(local_K->get(2, 0), index3, index1);
    K->add(local_K->get(2, 1), index3, index2);
    K->add(local_K->get(2, 2), index3, index3);
    K->add(local_K->get(2, 3), index3, index4);
    K->add(local_K->get(3, 0), index4, index1);
    K->add(local_K->get(3, 1), index4, index2);
    K->add(local_K->get(3, 2), index4, index3);
    K->add(local_K->get(3, 3), index4, index4);
}

// It will Assembly the b Vector, for doing that this functions gets a local_b vector 
// and the indexes of the current element nodes, in order to assemby it gets the values of local_b
// and adds them to the Vector b based in the indexes provided.
// NOTE: Remember that a node ID has a relation with it's index
void assembly_b(Vector *b, Vector *local_b, int index1, int index2, int index3, int index4)
{
    b->add(local_b->get(0), index1);
    b->add(local_b->get(1), index2);
    b->add(local_b->get(2), index3);
    b->add(local_b->get(3), index4);
}

// This function is in charge of the assembly of local Ks into K Matrix
// and the assembly of local bs into b Vector
void assembly(Matrix *K, Vector *b, Matrix *Ks, Vector *bs, int num_elements, Mesh *M)
{
    K->init(); // Fills K matrix with 0s
    b->init(); // Fills b vector with 0s
    // K->show(); b->show();

    // Iterate over the elements of the system
    for (int e = 0; e < num_elements; e++)
    {
        cout << "\tAssembling for Element " << e + 1 << "...\n\n";
        // Get node's indexes of the current element
        int index1 = M->get_element(e)->get_node1()->get_ID() - 1;
        int index2 = M->get_element(e)->get_node2()->get_ID() - 1;
        int index3 = M->get_element(e)->get_node3()->get_ID() - 1;
        int index4 = M->get_element(e)->get_node4()->get_ID() - 1;

        // For each element this function will assembly it's local K into general Matrix K
        assembly_K(K, &Ks[e], index1, index2, index3, index4);
        // For each element this function will assembly it's local b into general Vector b
        assembly_b(b, &bs[e], index1, index2, index3, index4);
        // cout << "\t\t"; K->show(); cout << "\t\t"; b->show(); cout << "\n";
    }
}

// It will apply neumann conditions to general Vector b
void apply_neumann_boundary_conditions(Vector *b, Mesh *M)
{
    // Get the number of nodes that have a neuman condition
    int num_conditions = M->get_quantity(NUM_NEUMANN);

    // Iterate over the number of conditions
    for (int c = 0; c < num_conditions; c++)
    {
        Condition *cond = M->get_neumann_condition(c);
        // Get index of the element which has the condition
        int index = cond->get_node()->get_ID() - 1;

        // For each condition this function will add the value of the condition
        // to the General Vcetor b in the index of the element wich has the condition 
        b->add(cond->get_value(), index);
    }
    // cout << "\t\t"; b->show(); cout << "\n";
}

/* 
This function adds a particular column of the left side of the ecuation Matrix (K)
to the right side of the ecucation Vector (b) 

for example: it will get the value [0][col] (of the selected column) in matriz K 
and it will be added to the position [0] of the vector b
*/
void add_column_to_RHS(Matrix *K, Vector *b, int col, float T_bar)
{
    // Since it needs to add al the values of the column to Vector b
    // This for will iterate the rows of K and add all the values of the selected column
    for (int r = 0; r < K->get_nrows(); r++)
        b->add(-T_bar * K->get(r, col), r);
}

// Apply irichlet conditions, this function will crop the matrix K in order to create 
// a ecuation system with only the unknown node's values
void apply_dirichlet_boundary_conditions(Matrix *K, Vector *b, Mesh *M)
{
    // Get number of nodes with dirichlet conditions
    int num_conditions = M->get_quantity(NUM_DIRICHLET);
    // Count the removed columns and nodes
    int previous_removed = 0;

    // Iterate over the number of nodes with dirichlet conditions
    for (int c = 0; c < num_conditions; c++)
    {
        Condition *cond = M->get_dirichlet_condition(c);

        // Get each node's ID and condition value
        int index = cond->get_node()->get_ID() - 1 - previous_removed;
        float cond_value = cond->get_value();

        // K->show();
        // Remove row of the node's index from K matrix
        K->remove_row(index);
        
        // b->show();
        // Remove row of the node's index from b vector
        b->remove_row(index);
        // b->show();

        // Add the column that correspons with the removed row from K to b 
        add_column_to_RHS(K, b, index, cond_value);
        // b->show();

        // Remove column of the node's index from K matrix
        K->remove_column(index);
        // K->show();

        // Increment the number of removed columns and nodes
        previous_removed++;
    }
}

/*
This function is the responsible for solving solve the final ecuation system,
It also will print a time marks inside solve_system file.

First it created a Matrix Kinv of dimensions n:n to store the inverse of the K, to accomplish this it uses 
calculate_inverse function which uses Cholensky's method after using this function the previous Matrix Kinv
will store the K inverse.

Finally it does a procut of matrix by vector (Kinv x b) and it will populate the Vector b 
with the values of the ecuation system answers.
*/
void solve_system(Matrix *K, Vector *b, Vector *T)
{
    int n = K->get_nrows();

    Matrix Kinv(n, n);

    ofstream timesFile("time_report/solve_system.txt", ios::app);
    cout << "\tCalculating inverse of global matrix K...\n\n";
    calculate_inverse(K, n, &Kinv);

    timesFile << "[" << getCurrentTimestamp() << "] Performing final calculation...\n\n";
    cout << "\tPerforming final calculation...\n\n";
    product_matrix_by_vector(&Kinv, b, n, n, T);
}

/*
This function gets a Vector with the responses of the final ecuation system and
a  Vector of dimens n (number of nodes).

With this function whe want to get a Vector Tf with all the node's values, not only the ones 
that where solved by the ecuation system but with those that already had a value (Dirichlet condition).

Finally it will set Tf Vector with the values of T vector (ecuation system answers) and the nodes whose 
values where already known.
*/
void merge_results_with_dirichlet(Vector *T, Vector *Tf, int n, Mesh *M)
{
    int num_dirichlet = M->get_quantity(NUM_DIRICHLET);

    int cont_dirichlet = 0;
    int cont_T = 0;
    for (int i = 0; i < n; i++)
    {
        // If the node has a dirichlet condition then get that value and put it in Tf Vector
        if (M->does_node_have_dirichlet_condition(i + 1))
        {
            Condition *cond = M->get_dirichlet_condition(cont_dirichlet);
            cont_dirichlet++;

            float cond_value = cond->get_value();

            Tf->set(cond_value, i);
        }
        else
        {
            // If the node does not have a dirichlet condition then put the value 
            // of T (ecuation system answers) in Tf Vector
            Tf->set(T->get(cont_T), i);
            cont_T++;
        }
    }
}
