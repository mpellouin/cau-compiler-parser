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
    std::vector<std::pair<std::string, std::string>> rules = config->productions;
    for (std::pair<std::string, std::string> rule : rules) {
        DEBUG_MSG("Rule: " << rule.first << " -> " << rule.second);
        std::queue<std::variant<NONTERMINAL, TERMINAL>> rhs;
        std::string token = this->_getNextToken(rule.second);
        while (token.empty() == false) {
            DEBUG_MSG("\tToken: " << token << " remaining: " << rule.second);
            try {
             NONTERMINAL nt = config->getNonTerminal(token);
             DEBUG_MSG("\t\tFound non-terminal " << token); 
             rhs.push(nt);
             token = this->_getNextToken(rule.second);
             continue;
            } catch(const std::exception& e) {
                DEBUG_MSG("\t\tCould not find non-terminal " << token << " trying terminal...");
            }

            try {
              TERMINAL t = config->getTerminal(token);
              rhs.push(t);
              token = this->_getNextToken(rule.second);
            } catch(const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
           
        }
        DEBUG_MSG("Pushing production:" << rule.first);
        _productions.push_back(Production(config->getNonTerminal(rule.first), rhs));
    }

    for (Production p : _productions) {
        DEBUG_MSG("Production: " << config->nonTerminalsStrings[p.lhs] << " -> ");
        std::queue<std::variant<NONTERMINAL, TERMINAL>> rhs = p.rhs;
        while (!rhs.empty()) {
            std::variant<NONTERMINAL, TERMINAL> token = rhs.front();
            rhs.pop();
            if (std::holds_alternative<NONTERMINAL>(token)) {
                DEBUG_MSG("\tNon-terminal: " << config->nonTerminalsStrings[std::get<NONTERMINAL>(token)]);
            } else {
                DEBUG_MSG("\tTerminal: " << config->terminalsStrings[std::get<TERMINAL>(token)]);
            }
        }
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
    std::getline(ss, token, ' ');
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