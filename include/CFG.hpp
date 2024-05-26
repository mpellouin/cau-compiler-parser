/*
** EPITECH PROJECT, 2024
** bottom-up-parser
** File description:
** CFG
*/

#ifndef CFG_HPP_
#define CFG_HPP_

#include <sstream>
#include <iostream>

#include "Production.hpp"
#include "debug.hpp"

namespace buparser {
    class CFG {
        public:
            CFG(Config *config);
            ~CFG();

            NONTERMINAL getProductionLHS(int index);
            size_t getProductionRHSSize(int index);
            Config *config;

        protected:
        private:
            std::vector<Production> _productions;
            std::string _getNextToken(std::string &s);
    };
}

#endif /* !CFG_HPP_ */
