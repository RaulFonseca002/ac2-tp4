#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <map>

class Compiler{
    private:
        char x;
        char y;
        std::ofstream hexFile;
        
        std::map<std::string, char> hexMap;

    public:
        void read(std::string var, std::string operation);
        void write(std::string operation);
        Compiler();
        ~Compiler();
};