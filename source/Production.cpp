/*
** EPITECH PROJECT, 2024
** bottom-up-parser
** File description:
** Production
*/

#include "Production.hpp"

buparser::Production::Production(NONTERMINAL lhs, std::queue<std::variant<NONTERMINAL, TERMINAL>> rhs) : lhs(lhs), rhs(rhs)
{
}

buparser::Production::~Production()
{
}
