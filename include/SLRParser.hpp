/*
** EPITECH PROJECT, 2024
** bottom-up-parser
** File description:
** SLRParser
*/

#ifndef SLRPARSER_HPP_
#define SLRPARSER_HPP_

#include <stack>
#include <vector>
#include <unordered_map>
#include <queue>
#include <numeric>

#include "debug.hpp"
#include "Config.hpp"
#include "CFG.hpp"
#include "ParseTreeNode.hpp"


namespace buparser {

    class SLRParser {
        public:
            SLRParser(CFG *cfg);
            ~SLRParser();

            /**
             * @brief Takes a queue of tokenStrings and validates them
             * 
             * @param input 
             */
            void validate(std::queue<std::string> input);

        protected:
        private:
            std::stack<int> _states;
            int _currentIndex = 0;
            CFG *_cfg;
            // Initialized as PROGRAM (corresponding to S' in a CFG with S' -> S)
            ParseTreeNode _parseTree {NONTERMINAL::PROGRAM};

            /**
             * @brief Generates a report for the exception
             * 
             * @param state 
             * @param tokenString 
             * @return std::string 
             */
            std::string generateReport(int state, std::string tokenString);
    };
}

#endif /* !SLRPARSER_HPP_ */
