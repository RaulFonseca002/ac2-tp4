#include "compiler.hpp"
#include "ula.hpp"
#include <iostream>
#include <fstream>
#include <regex>


#define START_FLAG "inicio:"
#define END_FLAG "fim."

int main(int argc, char const *argv[])
{
    std::regex re(R"((\w+)\s*=\s*(\w+);)");
    std::smatch match;

    std::ifstream inputFile("testula.ula");
    std::string inputBuffer;

    Compiler c;
    ula u(100);
    int lineCounter = 0;

    while(inputBuffer != START_FLAG){
        lineCounter++;
        getline(inputFile, inputBuffer);
    }

    while(getline(inputFile, inputBuffer)){

        lineCounter++;

        if(inputBuffer == END_FLAG) break;

        if(std::regex_match(inputBuffer, match, re)){
            lineCounter++;
            
            c.read(match[1].str(), match[2].str());

        }else{
            printf("error found in line: %i", lineCounter);
        }

    }

    u.setMem("testula.hex");
    u.run();

    return 0;
}
