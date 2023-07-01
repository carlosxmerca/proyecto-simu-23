#include <iostream>
#include <sys/stat.h>

using namespace std;

#include "geometry/mesh.hpp"                         // Include header file for mesh geometry
#include "math_utilities/matrix_operations.hpp"      // Include header file for matrix operations
#include "mef_utilities/mef_process.hpp"             // Include header file for MEF (Finite Element Method) process
#include "gid/input_output.hpp"                      // Include header file for GID (GiD) input/output

// Function to check if a directory exists
bool directoryExists(const string& directoryName) {
    struct stat buffer;
    return (stat(directoryName.c_str(), &buffer) == 0);
}

int main (int argc, char** argv) {
    // Check if the program is used correctly with a filename argument
    if (argc != 2) {
        cout << "Incorrect use of the program, it must be: mef filename\n";
        exit(EXIT_FAILURE);
    }

    const string directoryName = "time_report";    // Directory name for time reports
    string filename(argv[1]);                      // Input filename
    string timesFilename(directoryName + "/" + filename + ".txt");  // Time report filename

    // Check if the directory for time reports exists, if not, create it
    if (!directoryExists(directoryName)) {
        // If the system where the program is running is Windows, erase parameters /0755
        int createDirectoryStatus = mkdir(directoryName.c_str(), 0755);
        if (createDirectoryStatus != 0) {
            cout << "Failed to create the directory." << endl;
            exit(EXIT_FAILURE);
        }
    }

    ofstream timesFile(timesFilename, ios::app);    // Open the time report file for appending

    if (!timesFile) {
        cout << "Error opening the output file." << endl;
        exit(EXIT_FAILURE);
    }

    Mesh M;    // Create a Mesh object

    timesFile << "[" << getCurrentTimestamp() << "] Reading geometry and mesh data...\n\n";
    cout << "Reading geometry and mesh data...\n\n";

    read_input(filename, &M);    // Read the input geometry and mesh data from file
    M.insert_nodes_in_max_heap();    // Insert nodes into a max heap for efficient access
    M.report();    // Report mesh information

    // Create global system matrices and vectors
    int num_nodes = M.get_quantity(NUM_NODES);
    int num_elements = M.get_quantity(NUM_ELEMENTS);
    Matrix K(num_nodes, num_nodes), local_Ks[num_elements];
    Vector b(num_nodes), local_bs[num_elements];

    timesFile << "[" << getCurrentTimestamp() << "] Creating local systems...\n\n";
    cout << "Creating local systems...\n\n";
    create_local_systems(local_Ks, local_bs, num_elements, &M);    // Create local systems

    timesFile << "[" << getCurrentTimestamp() << "] Performing Assembly...\n\n";
    cout << "Performing Assembly...\n\n";
    assembly(&K, &b, local_Ks, local_bs, num_elements, &M);    // Assemble the global system

    timesFile << "[" << getCurrentTimestamp() << "] Applying Neumann Boundary Conditions...\n\n";
    cout << "Applying Neumann Boundary Conditions...\n\n";
    apply_neumann_boundary_conditions(&b, &M);    // Apply Neumann boundary conditions

    //b.show();

    timesFile << "[" << getCurrentTimestamp() << "] Applying Dirichlet Boundary Conditions...\n\n";
    cout << "Applying Dirichlet Boundary Conditions...\n\n";
    apply_dirichlet_boundary_conditions(&K, &b, &M);    // Apply Dirichlet boundary conditions

    //K.show(); b.show();

    timesFile << "[" << getCurrentTimestamp() << "] Solving global system...\n\n";
    cout << "Solving global system...\n\n";
    Vector T(b.get_size()), T_full(num_nodes);
    solve_system(&K, &b, &T);   // Solve the global system
    //T.show();
    
    timesFile << "[" << getCurrentTimestamp() << "] Preparing results...\n\n";
    cout << "Preparing results...\n\n";
    merge_results_with_dirichlet(&T, &T_full, num_nodes, &M);   // Merge results with Dirichlet boundary conditions
    //T_full.show();

    timesFile << "[" << getCurrentTimestamp() << "] Writing output file...\n\n";
    cout << "Writing output file...\n\n";
    write_output(filename, &T_full);   // Write the output file

    timesFile.close();   // Close the time report file

    return 0;
}
