//
// Created by mpellouin on 14/05/24.
//

#include <iostream>
#include "TokenParser.hpp"
#include "Config.hpp"
#include "CFG.hpp"
#include "SLRParser.hpp"

int main(int ac, char **argv) {
    if (ac != 2 || (ac == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help"))) {
        std::cerr << "Usage: " << argv[0] << " <filepath>" << std::endl;
        return EXIT_FAILURE;
    }

    Config config;
    buparser::CFG cfg(&config);
    buparser::TokenParser tokenParser(argv[1]);
    buparser::SLRParser slrParser(&cfg);


    try {
        std::queue<std::string> tokens = tokenParser.parse();
        slrParser.validate(tokens);
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}