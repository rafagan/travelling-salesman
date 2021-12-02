/*
 * Nome completo: 
 * Registro acadêmico: 
*/

#include <iostream>
#include <string>
#include <filesystem>
#include "solver/TSPSolver.h"
#include "io/io.h"

using namespace std;

OutputData solveTravellingSalesman(InputData inputData, const char* outputPath) {
    std::filesystem::path p = outputPath;
    p.remove_filename();

    TSPSolver solver;
    OutputData outputData = solver.solveGreedily(inputData);
    solver.exportTree(string(p) + "/tree.txt");
    solver.exportCycle(string(p) + "/cycle.txt");

    return outputData;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        puts("Invalid inputs. Usage: \n.$ ./tsp /path/to/genpoints/input.txt");
        return 1;
    }

    char* path = argv[1];
    char* buffer = allocReadFileContent(path);
    InputData inputData = allocProcessInputData(buffer);
    
//    printf("Buffer: %s\n", buffer);
//    logInputData(inputData);

    OutputData outputData = solveTravellingSalesman(inputData, argv[0]);
    logOutputData(&outputData, false);

    freeInputDataPoints(inputData);
    free(buffer);

    return 0;
}