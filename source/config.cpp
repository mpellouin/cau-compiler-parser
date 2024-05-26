/*
** EPITECH PROJECT, 2024
** bottom-up-parser
** File description:
** config
*/

#include "Config.hpp"

Config::Config()
{
}

Config::~Config()
{
}

TERMINAL Config::getTerminal(std::string terminal)
{
    for (int i = 0; i < 21; i++) {
        if (this->terminalsStrings[i] == terminal)
            return static_cast<TERMINAL>(i);
    }
    throw std::domain_error(terminal + ": unknown terminal");
}

NONTERMINAL Config::getNonTerminal(std::string nt)
{
    for (int i = 0; i < 19; i++) {
        if (this->nonTerminalsStrings[i] == nt)
            return static_cast<NONTERMINAL>(i);
    }
    throw std::domain_error(nt + ": unknown Non Terminal");
}