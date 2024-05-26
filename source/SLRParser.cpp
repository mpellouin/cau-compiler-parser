/*
** EPITECH PROJECT, 2024
** bottom-up-parser
** File description:
** SLRParser
*/

#include "SLRParser.hpp"

buparser::SLRParser::SLRParser(CFG *cfg) : _cfg(cfg)
{
    DEBUG_MSG("buparser::SLRParser::SLRParser()");
    _states.push(0);
}

buparser::SLRParser::~SLRParser()
{
    DEBUG_MSG("buparser::SLRParser::~SLRParser()");
}

void buparser::SLRParser::validate(std::queue<std::string> input)
{
    DEBUG_MSG("buparser::SLRParser::validate()");
    DEBUG_MSG("Input size: " << input.size());
    int state = 0;
    while (!input.empty()) {
        std::variant<NONTERMINAL, TERMINAL> token;


        std::string tokenString = input.front();

        try {
            token = _cfg->config->getTerminal(tokenString);
        } catch (std::domain_error &e) {
            try {
                token = _cfg->config->getNonTerminal(tokenString);
            } catch (std::domain_error &e) {
                throw std::domain_error(tokenString + ": unknown token");
            }
        }

        DEBUG_MSG("Token: " << tokenString);

        if (_cfg->config->slrTable[state].count(token) != 1) {
            throw std::domain_error("No transition for state " + std::to_string(state) + " and token " + tokenString);
        } else {
            std::pair<ActionType, int> action = _cfg->config->slrTable[state][token];
            DEBUG_MSG("Action: " << int(action.first) << " to " << action.second);
            if (action.first == ActionType::SHIFT) {
                _states.push(action.second);
                input.pop();
                state = action.second;
            } else if (action.first == ActionType::REDUCE) {
                size_t productionSize = _cfg->getProductionRHSSize(action.second);
                NONTERMINAL lhs = _cfg->getProductionLHS(action.second);
                DEBUG_MSG("Reduce: " << _cfg->config->nonTerminalsStrings[lhs] << " -> " << productionSize << " tokens");
                for (int i = 0; i < productionSize; i++) {
                    _states.pop();
                }
                _states.push(_cfg->config->slrTable[_states.top()][lhs].second);
                state = _states.top();
            } else if (action.first == ActionType::ACCEPT) {
                DEBUG_MSG("Accepted");
                return;
            } else if (action.first == ActionType::GOTO) {
                _states.push(action.second);
            }
        }
        DEBUG_MSG("Stack :");
        std::stack<int> tmp = _states;
        while (!tmp.empty()) {
            DEBUG_MSG(tmp.top());
            tmp.pop();
        }
    }
}