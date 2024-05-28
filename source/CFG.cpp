/*
** EPITECH PROJECT, 2024
** bottom-up-parser
** File description:
** CFG
*/

#include "CFG.hpp"

buparser::CFG::CFG(Config *config) : config(config)
{
    DEBUG_MSG("CFG constructor");
    //Get the rules from the config class
    std::vector<std::pair<std::string, std::string>> rules = config->productions;

    // For each rule, create a Production
    for (std::pair<std::string, std::string> rule : rules) {
        DEBUG_MSG("Rule: " << rule.first << " -> " << rule.second);
        std::queue<std::variant<NONTERMINAL, TERMINAL>> rhs;

        // Gets the first token of the rule's RHS
        std::string token = this->_getNextToken(rule.second);
        while (token.empty() == false) {
            DEBUG_MSG("\tToken: " << token << " remaining: " << rule.second);

            // As this is a building phase, we cannot use std::holds_alternative directly
            // TODO: Improve this
            try {
                // Try to get the non-terminal and push it to the rhs queue
             NONTERMINAL nt = config->getNonTerminal(token);
             DEBUG_MSG("\t\tFound non-terminal " << token); 
             rhs.push(nt);
             token = this->_getNextToken(rule.second);
             continue;
            } catch(const std::exception& e) {
                // If we did not find a non-terminal, we try to find a terminal
                DEBUG_MSG("\t\tCould not find non-terminal " << token << " trying terminal...");
            }

            try {
                // Try to get the terminal and push it to the rhs queue
              TERMINAL t = config->getTerminal(token);
              rhs.push(t);
              token = this->_getNextToken(rule.second);
            } catch(const std::exception& e) {
                // This time however, it means that the token is neither a terminal nor a non-terminal
                // Only display the error message as this is necessarily a Config error
                std::cerr << e.what() << std::endl;
            }
           
        }
        DEBUG_MSG("Pushing production:" << rule.first);
        // Once we added all the terms of the profuction, push it to the CFG productions vector
        _productions.push_back(Production(config->getNonTerminal(rule.first), rhs));
    }
}

buparser::CFG::~CFG()
{
    DEBUG_MSG("CFG destructor");
}


std::string buparser::CFG::_getNextToken(std::string &s)
{
    std::string token;
    std::stringstream ss(s);

    // Allows to split the string by space (onlt one token at a time)
    std::getline(ss, token, ' ');

    // Erase the token from the string to prevent infinite loop, and to update the string state
    s.erase(0, token.length() + 1);
    return token;
}

NONTERMINAL buparser::CFG::getProductionLHS(int index)
{
    return this->_productions[index].lhs;
}

size_t buparser::CFG::getProductionRHSSize(int index)
{
    DEBUG_MSG("getProductionRHSSize with index: " << index << " and size: " << this->_productions[index].rhs.size() << " tokens.");
    return this->_productions[index].rhs.size();
}