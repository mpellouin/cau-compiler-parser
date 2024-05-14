//
// Created by mpellouin on 14/05/24.
//

#include "TokenParser.hpp"

buparser::TokenParser::TokenParser(std::string filepath) : _filepath(filepath)
{
    DEBUG_MSG("buparser::TokenParser::TokenParser(" << filepath << ")");
}

std::queue<std::string> buparser::TokenParser::parse()
{
    std::ifstream file = this->isFilepathValid();
    std::string line;
    int line_number = 0;

    while (std::getline(file, line)) {
        DEBUG_MSG("bustream::TokenParser::parse() -> Line " << line_number << ": " << line);
        this->parseLine(line);
        line_number++;
    }
    return this->_tokens;
}

std::ifstream buparser::TokenParser::isFilepathValid()
{
    std::ifstream file(this->_filepath);
    if (!file) {
        throw std::invalid_argument("Invalid filepath");
    }
    DEBUG_MSG("bustream::TokenParser::isFilepathValid() -> " << this->_filepath << " is valid");
    return file;
}

void buparser::TokenParser::parseLine(std::string line)
{
    std::istringstream iss(line);
    std::string token;
    while (iss >> token) {
        DEBUG_MSG("bustream::TokenParser::parseLine() -> New token: " << token);
        this->_tokens.push(token);
    }
}