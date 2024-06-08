//
// Created by mpellouin on 14/05/24.
//

#include "TokenParser.hpp"

buparser::TokenParser::TokenParser(std::string filepath) : _filepath(filepath)
{
    DEBUG_MSG("buparser::TokenParser::TokenParser(" << filepath << ")");
}

buparser::TokenParser::~TokenParser()
{
    DEBUG_MSG("buparser::TokenParser::~TokenParser()");
}

std::queue<std::string> buparser::TokenParser::parse()
{
    // Check if the filepath is valid and get the ifstream if it is
    std::ifstream file = this->_isFilepathValid();
    std::string line;
    int line_number = 0;

    // Parse the file line by line (not necessary but this is extra input validation, + great for sequence debugging)
    while (std::getline(file, line)) {
        DEBUG_MSG("bustream::TokenParser::parse() -> Line " << line_number << ": " << line);
        // Parse the line
        this->_parseLine(line);
        line_number++;
    }

    // Push an EOF token to be able to use it in the slrParser
    this->_tokens.push("EOF");
    return this->_tokens;
}

std::ifstream buparser::TokenParser::_isFilepathValid()
{
    // Creates ifstream object from the filepath
    std::ifstream file(this->_filepath);
    
    // If it is nit a file, throw an exception
    if (!file) {
        throw std::invalid_argument("Invalid filepath");
    }
    DEBUG_MSG("bustream::TokenParser::isFilepathValid() -> " << this->_filepath << " is valid");
    return file;
}

void buparser::TokenParser::_parseLine(std::string line)
{
    std::istringstream iss(line);
    std::string token;

    // Easy parsing with stringstreams automatically splitting the token sequences by space
    // If for some reasons the CFG has rules such as E -> aB, this will not work but for our use case, it is enough
    while (iss >> token) {
        DEBUG_MSG("bustream::TokenParser::parseLine() -> New token: " << token);
        this->_tokens.push(token);
    }
}