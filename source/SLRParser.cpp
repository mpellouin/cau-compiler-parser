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

    // Initial state
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

        // Get the first string token
        std::string tokenString = input.front();

        try {
            // Try to get the token as a terminal
            // If it fails, it means that the token is a non-terminal or an unknown token
            token = _cfg->config->getTerminal(tokenString);
        } catch (std::domain_error &e) {
            try {
                token = _cfg->config->getNonTerminal(tokenString);
            } catch (std::domain_error &e) {
                throw std::domain_error(tokenString + ": unknown token");
            }
        }

        DEBUG_MSG("Token: " << tokenString);


        // Check on the transition table if there is an action recorded for the current state token combination
        if (_cfg->config->slrTable[state].count(token) != 1) {
            // Throw if there is no transition (or multiple transitions, which would be a config error)

            // However as this is unlikely, we can throw the following exception description
            throw std::domain_error("No transition for state " + std::to_string(state) + " and token " + tokenString);
        } else {
            // Get the action index pair from the slrTable
            std::pair<ActionType, int> action = _cfg->config->slrTable[state][token];
            DEBUG_MSG("Action: " << int(action.first) << " to " << action.second);

            // Check if action is switch
            if (action.first == ActionType::SHIFT) {

                // Create a ParseTreeNode with the token and add it to the ParseTree
                ParseTreeNode node(token);
                _parseTree.addChild(node);

                // Add the state to the stack and remove the token from the input queue
                _states.push(action.second);
                input.pop();
                state = action.second;
            } else if (action.first == ActionType::REDUCE) {
                // If the action is a reduce, we need to get the "productor" of the production and know how many tokens the "product" is composed of
                // This allows us to create a new ParseTreeNode with the lhs as the self value and pop the n last nodes from the ParseTree to add them as children to this new node
                // It is also useful as we will directly do the goto action with the lhs of the production

                // Get the size of the production and the lhs
                size_t productionSize = _cfg->getProductionRHSSize(action.second);
                NONTERMINAL lhs = _cfg->getProductionLHS(action.second);
                ParseTreeNode node(lhs);

                // Get the productionSize last nodes from _parseTree and add those as child of the new node
                std::queue<ParseTreeNode> children = _parseTree.popNNextNodes(productionSize);
                while (!children.empty()) {
                    node.addChild(children.front());
                    children.pop();
                }

                // Add the new node to the parse tree
                _parseTree.addChild(node);
                DEBUG_MSG("Reduce: " << _cfg->config->nonTerminalsStrings[lhs] << " -> " << productionSize << " tokens");
                DEBUG_MSG("ParseTreeNode Children length: " << _parseTree.children.size());

                // Remove the productionSize last states (going to be replaced by the goto-assigned state)
                for (int i = 0; i < productionSize; i++) {
                    _states.pop();
                }

                // Goto the state assigned with newState and shift rule lhs
                _states.push(_cfg->config->slrTable[_states.top()][lhs].second);
                state = _states.top();
            } else if (action.first == ActionType::ACCEPT) {
                DEBUG_MSG("Accepted");
                // If slrParsing is accepted accept the tree (display it)
                _parseTree.acceptTree(_cfg->config, _cfg->getProductionLHS(0));
                return;
            }
        }
    }
}