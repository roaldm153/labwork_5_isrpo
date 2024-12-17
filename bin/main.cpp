#include "lib/ArgParser.h"


int main(int argc, char** argv) {
    ArgumentParser::ArgParser parser("My Parser");
    parser.AddIntArgument('p', "param1");
    parser.AddIntArgument("param2").MultiValue().Positional();
    parser.AddFlag('f', "flag");
    parser.Parse({"app", "-p", "-1", "-2", "-f", "-3", "-4", "-5"});

    std::cout << parser.GetFlag("flag") << std::endl;
    std::cout << parser.GetIntValue("param1") << std::endl;
    std::cout << parser.GetIntValue("param2", 0) << std::endl;
    std::cout << parser.GetIntValue("param2", 1) << std::endl;
    std::cout << parser.GetIntValue("param2", 2) << std::endl;
    std::cout << parser.GetIntValue("param2", 3) << std::endl;    
    
    return 0;
}
