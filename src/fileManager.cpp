#include "iostream"
#include <fstream>
#include <string.h>
#include "fileManager.h"

std::string readInputData(std::string fileName)
{
  std::ifstream dataFile(fileName);
  std::string data;

  if (dataFile.is_open())
  {
    while (std::getline(dataFile, data))
    {
    }
    dataFile.close();
  }
  else
    std::cout << "Unable to open file";

  return data;
}

void formatString(std::string str, int array[], int size, std::string delimiter)
{
  int i = 0;
  char *token = strtok((char *)str.c_str(), delimiter.c_str());

  while (token != NULL && i < size - 1)
  {
    array[i] = atol(token);
    token = strtok(NULL, delimiter.c_str());
    i++;
  }
}

void writeInCSV(std::string fileName, std::string data, bool lastElement)
{
  std::ofstream dataFile(fileName, std::ios_base::app);

  if (dataFile.is_open())
  {
    lastElement ? dataFile << data << std::endl : dataFile << data << ",";
    dataFile.close();
  }
  else
    std::cout << "Unable to open file";
}

void cleanOuputFiles()
{
  std::string file_names[4] = {"bubble_ops.csv", "bubble_time.csv", "quick_ops.csv", "quick_time.csv"};

  for (int i = 0; i < 4; i++)
  {
    std::ofstream dataFile("./results/" + file_names[i]);
    dataFile.close();
  }
}
