#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

#define NUM_OF_ARRAYS 3

std::string readInputData(std::string fileName);
void formatString(std::string str, int array[], int size, std::string delimiter);
void writeInCSV(std::string fileName, std::string data, bool lastElement);
void cleanOuputFiles();

#endif
