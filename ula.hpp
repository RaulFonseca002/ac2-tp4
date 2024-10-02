#include <stdlib.h>
#include <string>
#include <map>

class ula {
    private:
        char16_t* mem;
        std::map<char, char> hexMap;
        int lastAdress;

        char16_t operate(char op);
    public:
        ula(int memSize);
        ~ula();

        bool setMem(std::string fileName);
        bool run();
        void printMem(int current);

};

