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

#include "debug.hpp"
#include "Config.hpp"
#include "CFG.hpp"


namespace buparser {

    class SLRParser {
        public:
            SLRParser(CFG *cfg);
            ~SLRParser();

            void validate(std::queue<std::string> input);

        protected:
        private:
            std::stack<int> _states;
            int _currentIndex = 0;
            CFG *_cfg;

    };
}

#endif /* !SLRPARSER_HPP_ */
