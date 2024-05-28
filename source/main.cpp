//
// Created by mpellouin on 14/05/24.
//

#include <iostream>
#include "TokenParser.hpp"
#include "Config.hpp"
#include "CFG.hpp"
#include "SLRParser.hpp"

int main(int ac, char **argv)
{
    // If user did not provide a filepath or entered the help flags, print a mini usage
    if (ac != 2 || (ac == 2 && (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")))
    {
        std::cerr << "Usage: " << argv[0] << " <filepath>" << std::endl;
        return EXIT_FAILURE;
    }

    try
    {
        Config config;
        buparser::CFG cfg(&config);
        buparser::TokenParser tokenParser(argv[1]);
        buparser::SLRParser slrParser(&cfg);

        // Get the tokens from the file
        std::queue<std::string> tokens = tokenParser.parse();

        // Validate the token sequence
        slrParser.validate(tokens);
    }
    catch (std::exception &e)
    {
        // Error report is printed to stderr
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    // If everything went well, return success
    return EXIT_SUCCESS;
}