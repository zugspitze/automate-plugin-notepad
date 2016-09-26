#include <vector>
#include <fstream>
#include <string>
#include "Parser.h"


int main(int argc, char* argv[])
{
    std::vector<std::string> atmFile;
    std::ifstream atm_file(argv[1]);
    std::string line;

    while (std::getline(atm_file, line))
    {
        atmFile.push_back(line);
    }

    RText::Parser aParser(atmFile);
}
