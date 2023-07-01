# Proyecto SIMU 3D

## Instrucciones de compilación
Para compilar el programa, se debe usar el siguiente comando
```bash
    g++ main.cpp -o mef
```
El comando g++ es un comando de invocación al compilador GNU c++, que se utiliza para preprocesar, compilar, ensamblar y enlazar código fuente para generar un archivo ejecutable.

## Uso del programa
Para utilizar el programa, el archivo .dat debe estar en el mismo directorio en el que se encuentra el ejecutable. **Importante** : Borrar el .dat al momento de utilizar el comando. Ejemplo:


Windows
```bash
.\mef porygon-l-mesh
.\mef porygon-s-mesh
```
Linux
```bash
./mef porygon-l-mesh
./mef porygon-s-mesh
```


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

