# Proyecto SIMU 3D

## Indicaciones especiales:
Asegurarse de eliminar el argumento "0755" a la creación del directorio (En el archivo "main.cpp", en la línea 31) cuando se ejecute el código en Windows. Sin embargo, este argumento es válido y no debe eliminarse si se ejecuta el código en Linux.
```c++
// Create the output directory if it doesn't exist, otherwise, append to the existing file
    if (!directoryExists(directoryName)) {
        // If the system where the program is running is Windows, erase parameters /0755
        int createDirectoryStatus = mkdir(directoryName.c_str(), 0755);
        if (createDirectoryStatus != 0) {
            cout << "Failed to create the directory." << endl;
            exit(EXIT_FAILURE);
        }
    }
```

