/*
** EPITECH PROJECT, 2024
** bottom-up-parser
** File description:
** Production
*/

#ifndef PRODUCTION_HPP_
#define PRODUCTION_HPP_

#include <variant>
#include <queue>

#include "Config.hpp"

namespace buparser {
    class Production {
        public:
            Production(NONTERMINAL lhs, std::queue<std::variant<NONTERMINAL, TERMINAL>> rhs);
            ~Production();

            NONTERMINAL lhs;
            std::queue<std::variant<NONTERMINAL, TERMINAL>> rhs;


        protected:
        private:
    };
}

#endif /* !PRODUCTION_HPP_ */
