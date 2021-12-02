#ifndef __IO_H__
#define __IO_H__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

#include "math/math_util.h"

typedef struct InputData {
    unsigned int count;
    Point** points;
} InputData;

typedef struct OutputData {
    double timeSecs;
    double weightSum;
} OutputData;

static long calcFileSize(FILE* file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    return size;
}

static char* allocReadFileContent(const char* path) {
    FILE* file = fopen(path, "r");
    unsigned int stringSize = calcFileSize(file);
    char* buffer = (char*) malloc(sizeof(char) * stringSize + 1);
    unsigned int readSize = fread(buffer, sizeof(char), stringSize, file);
    buffer[stringSize] = '\0';

    if(stringSize != readSize) {
        free(buffer);
        buffer = nullptr;
    }

    fclose(file);
    return buffer;
}

static InputData allocProcessInputData(const char* input) {
    bool isFirstLine = true;
    bool isReadingX = true;
    char buffer[50] = {};
    
    int pointCount;
    Point** points = nullptr;
    Point* point = nullptr;

    double x, y;

    for(unsigned int i = 0, j = 0; input[i] != '\0'; i++) {
        char c = input[i];
        if(!isdigit(c) && c != '.') {
            if(isFirstLine) {
                pointCount = atoi(buffer);
                points = (Point**)malloc(sizeof(Point) * pointCount);
                isFirstLine = false;
            } else {
                if(isReadingX) {
                    x = strtod(buffer, nullptr);
                    isReadingX = false;
                } else {
                    y = strtod(buffer, nullptr);
                    isReadingX = true;

                    point = (Point*)malloc(sizeof(Point));
                    point->x = x;
                    point->y = y;
                    points[j++] = point;
                }
            }

            strcpy(buffer, "");
        } else {
            char tmp[2] = {input[i], '\0'};
            strcat(buffer, tmp);
        }
    }

    InputData data;
    data.count = pointCount;
    data.points = points;

    return data;
}

static void freeInputDataPoints(InputData inputData) {
    for(unsigned int i = 0; i < inputData.count; i++) {
        free(inputData.points[i]);
    }
}

static void logInputData(InputData data) {
    puts("Entrada :");
    for(unsigned int i = 0; i < data.count; i++) {
        Point* point = data.points[i];
        printf("\t%d:(%d, %d)\n", i, (int)point->x, (int)point->y);
    }
}

static void logOutputData(const OutputData* data, bool isVerbose) {
    if(isVerbose) {
        puts("Saída :");
        printf("\tTempo: %f\n", data->timeSecs);
        printf("\tCusto: %f\n", data->weightSum);
    } else {
        printf(
            "%.6f %.6f\n", 
            data->timeSecs,
            data->weightSum
        );
    }
}

#endif