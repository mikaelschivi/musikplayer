#pragma once

#include <iostream>
#include <fstream>

class File
{
private:
    int fuck_you;

public:
    char* readBinaryFile(const std::string& filePath, const int byteAmount);
    void deleteData(char* data);
    void printBinaryFromData(char* data, int amountOfBytes);
};