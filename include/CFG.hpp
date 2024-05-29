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

            /**
             * @brief Get the Production left-hand side NONTERMINAL
             * 
             * @param index - index of the production in the CFG
             * @return NONTERMINAL
             */
            NONTERMINAL getProductionLHS(int index);

            /**
             * @brief Get the Production right-hand side size (ie. number of tokens in the production)
             * 
             * @param index - index of the production in the CFG
             * @return size_t 
             */
            size_t getProductionRHSSize(int index);
            Config *config;

        protected:
        private:
            std::vector<Production> _productions;

            /**
             * @brief Gets the next token in the string and removes it from the string
             * 
             * @param s - updated after removing the token
             * @return std::string - the token
             */
            std::string _getNextToken(std::string &s);
    };
}

#endif /* !CFG_HPP_ */
