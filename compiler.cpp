#include "compiler.hpp"

Compiler::Compiler(){
    hexFile.open("testula.hex");
    hexFile.clear();

    hexMap = {
        {"umL", '0'},
        {"AonB", '1'},
        {"copiaA", '2'},
        {"nAxnB", '3'},
        {"AeBn", '4'},
        {"nA", '5'},
        {"AenB", '6'},
        {"nAonB", '7'},
        {"AxB", '8'},
        {"zeroL", '9'},
        {"copiaB", 'A'},
        {"AeB", 'B'},
        {"nB", 'C'},
        {"nAeBn", 'D'},
        {"AoB", 'E'},
        {"nAeB", 'F'}
    };
}

Compiler::~Compiler(){
    hexFile.close();
}

void Compiler::write(std::string operation){
    std::string resp = "";
    resp += x;
    resp += y;
    resp += hexMap[operation];

    hexFile << resp << "\n";

}

void Compiler::read(std::string var, std::string operation){

    switch (var.at(0))
    {
    case 'X':
        x = operation.at(0);
        break;
    case 'Y':
        y = operation.at(0);
        break;
    case 'W':
        write(operation);
        break;
    default:
        break;
    }
}