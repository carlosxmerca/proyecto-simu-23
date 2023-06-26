#include <iostream>
#include <sys/stat.h>

using namespace std;

#include "geometry/mesh.hpp"
#include "math_utilities/matrix_operations.hpp"
#include "mef_utilities/mef_process.hpp"
#include "gid/input_output.hpp"

bool directoryExists(const string& directoryName) {
    struct stat buffer;
    return (stat(directoryName.c_str(), &buffer) == 0);
}

int main (int argc, char** argv) {
    if(argc != 2){
        cout << "Incorrect use of the program, it must be: mef filename\n";
        exit(EXIT_FAILURE);
    }

    const string directoryName = "time_report";
    string filename(argv[1]);
    string timesFilename(directoryName + "/" + filename + ".txt");

    if (!directoryExists(directoryName)) {
        int createDirectoryStatus = mkdir(directoryName.c_str(), 0755);
        if (createDirectoryStatus != 0) {
            cout << "Failed to create the directory." << endl;
            exit(EXIT_FAILURE);
        }
    }

    ofstream timesFile(timesFilename, ios::app);

    if (!timesFile) {
        cout << "Error opening the output file." << endl;
        exit(EXIT_FAILURE);
    }

    Mesh M;

    timesFile << "[" << getCurrentTimestamp() << "] Reading geometry and mesh data...\n\n";
    cout << "Reading geometry and mesh data...\n\n";

    read_input(filename, &M);
    //M.report();

    int num_nodes = M.get_quantity(NUM_NODES);
    int num_elements = M.get_quantity(NUM_ELEMENTS);
    Matrix K(num_nodes,num_nodes), local_Ks[num_elements];
    Vector b(num_nodes),           local_bs[num_elements];

    timesFile << "[" << getCurrentTimestamp() << "] Creating local systems...\n\n";
    cout << "Creating local systems...\n\n";
    create_local_systems(local_Ks, local_bs, num_elements, &M);

    timesFile << "[" << getCurrentTimestamp() << "] Performing Assembly...\n\n";
    cout << "Performing Assembly...\n\n";
    assembly(&K, &b, local_Ks, local_bs, num_elements, &M);

    //K.show(); b.show();

    timesFile << "[" << getCurrentTimestamp() << "] Applying Neumann Boundary Conditions...\n\n";
    cout << "Applying Neumann Boundary Conditions...\n\n";
    apply_neumann_boundary_conditions(&b, &M);

    //b.show();

    timesFile << "[" << getCurrentTimestamp() << "] Applying Dirichlet Boundary Conditions...\n\n";
    cout << "Applying Dirichlet Boundary Conditions...\n\n";
    apply_dirichlet_boundary_conditions(&K, &b, &M);

    //K.show(); b.show();

    timesFile << "[" << getCurrentTimestamp() << "] Solving global system...\n\n";
    cout << "Solving global system...\n\n";
    Vector T(b.get_size()), T_full(num_nodes);
    solve_system(&K, &b, &T);
    //T.show();
    
    timesFile << "[" << getCurrentTimestamp() << "] Preparing results...\n\n";
    cout << "Preparing results...\n\n";
    merge_results_with_dirichlet(&T, &T_full, num_nodes, &M);
    //T_full.show();

    timesFile << "[" << getCurrentTimestamp() << "] Writing output file...\n\n";
    cout << "Writing output file...\n\n";
    write_output(filename, &T_full);

    timesFile.close();

    return 0;
}
