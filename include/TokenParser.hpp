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
            ~TokenParser();

            /**
             * @brief Parse the file and returns a queue of tokenStrings
             * 
             * @return std::queue<std::string> 
             */
            std::queue<std::string> parse();

    private:
        std::string _filepath;
        std::queue<std::string> _tokens = {};

        /**
         * @brief Check if the filepath is valid and returns the ifstream or throw exception if not a file
         * 
         * @return std::ifstream 
         */
        std::ifstream isFilepathValid();

        /**
         * @brief Adds the tokens from the line to the token queue
         * 
         * @param line 
         */
        void parseLine(std::string line);




    };

} // buparser

#endif //BOTTOM_UP_PARSER_TOKENPARSER_HPP
