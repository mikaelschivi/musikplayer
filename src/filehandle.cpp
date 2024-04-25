#pragma once
#include <iostream>
#include <fstream>
// #include <string>

using namespace std;

namespace File
{
    char* readBinaryFile(const std::string& filePath, const int byteAmount)
    {
        std::ifstream byteStream(filePath, std::ios::binary);

        if (!byteStream.good()){
            cerr << "Can`t open " << filePath << " file" << endl;
            return nullptr;
        }

        char* buffer = new char[byteAmount];
        byteStream.read(buffer, byteAmount);
        byteStream.close();

        return buffer;
    }

    void deleteData(char* data)
    {
        delete[] data;
    }

    void printBinaryFromData(char* data, int amountOfBytes)
    {
        if (!data) {
            std::cerr << "data is fucked" << endl;
        }
        for (int i = 0; i < amountOfBytes; ++i) {
            for (int j = 7; j >= 0; --j) {
                std::cout << ((data[i] >> j) & 1);
            }
            std::cout << " ";
            if ((i + 1) % 16 == 0)
                std::cout << "| " << (i+1)/16 << std::endl;
        }
        std::cout << std::endl << "addr: "<< &data << std::endl;
    }
}