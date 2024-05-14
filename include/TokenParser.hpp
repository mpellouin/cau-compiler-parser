//
// Created by mpellouin on 14/05/24.
//

#ifndef BOTTOM_UP_PARSER_TOKENPARSER_HPP
#define BOTTOM_UP_PARSER_TOKENPARSER_HPP

#include <string>
#include <queue>
#include <sstream>
#include <fstream>

#include "debug.hpp"

namespace buparser {

    class TokenParser {
        public:
            TokenParser(std::string filepath);
            std::queue<std::string> parse();

    private:
        std::string _filepath;
        std::queue<std::string> _tokens = {};

        std::ifstream isFilepathValid();
        void parseLine(std::string line);




    };

} // buparser

#endif //BOTTOM_UP_PARSER_TOKENPARSER_HPP
