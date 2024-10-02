#include "ula.hpp"

#define PC mem[0]
#define W mem[1]
#define X mem[2]
#define Y mem[3]


ula::ula(int memSize){
    mem = new char16_t[memSize];
}

ula::~ula(){
    delete[] mem;
}

char charToHex(char ch){

    char resp = 0;

    if(ch > 0x2F && ch < 0x3A){
        resp = ch - 0x30;
    }else if(ch > 0x40 && ch < 0x47){
        resp = ch - 0x41 + 10;
    }
    
    return resp;
}

bool ula::setMem(std::string fileName){

    FILE* file;
    char* inputBuffer;
    int memPointer = 4;
    size_t lineSize;
    char16_t var = 0;

    try {
        file = fopen(fileName.c_str(), "r");

    } catch(std::exception e) {
        printf("invalid file path");
        return false;

    }

    while(getline(&inputBuffer, &lineSize, file) != -1){

        var += charToHex(inputBuffer[0]) << 8;
        var += charToHex(inputBuffer[1]) << 4;
        var += charToHex(inputBuffer[2]);

        mem[memPointer] = var;

        var = 0;
        memPointer++;
    }

    PC = 4;
    mem[memPointer] = 0xF << 12;
    lastAdress = memPointer;

    fclose(file);
    return true;
}

void ula::printMem(int current){

    std::string str;

    for(int c = 0; c < lastAdress; c++){

        printf(" | %X", mem[c]);
        if(c == current) 
            printf("*|");
        else 
            printf(" |");

    }

    printf("\n");
}

bool ula::run(){

    char16_t aux;

    aux = mem[PC];


    while((aux & (0xF << 12)) != 0xF000){

        X = (aux & 0x0F00) >> 8;
        Y = (aux & 0x00F0) >> 4;
        W = operate(aux & 0x000F);

        printMem(PC);
        PC++;
        aux = mem[PC];
    }

    return true;

}


char16_t ula::operate(char op){

    char16_t resp;

    switch (op){
        case 0x0:
            resp = 0xFFFF;
            break;
        case 0x1:
            resp = X + !Y;
            break;
        case 0x2:
            resp = X;
            break;
        case 0x3:
            resp = !X ^ !Y;
            break;
        case 0x4:
            resp = !(X & Y);
            break;
        case 0x5:
            resp = !X;
            break;
        case 0x6:
            resp = X & !Y;
            break;
        case 0x7:
            resp = !X | !Y;
            break;
        case 0x8:
            resp = X ^ Y;
            break;
        case 0x9:
            resp = 0x0000;
            break;
        case 0xA:
            resp = Y;
            break;
        case 0xB:
            resp = X & Y;
            break;
        case 0xC:
            resp = !Y;
            break;
        case 0xD:
            resp = !(!X | Y);
            break;
        case 0xE:
            resp = X | Y;
            break;
        case 0xF:
            resp = !X & Y;
            break;
    }

    return resp;
}
