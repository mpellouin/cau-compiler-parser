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
    // If we have not found a match through the whole array, the string is not a terminal
    throw std::domain_error(terminal + ": unknown terminal");
}

NONTERMINAL Config::getNonTerminal(std::string nt)
{
    // We do not count the last element of the array as it is only here for displaying correctly the ParseTree
    for (int i = 0; i < 20; i++) {
        if (this->nonTerminalsStrings[i] == nt)
            return static_cast<NONTERMINAL>(i);
    }
    // If we have not found a match through the whole array, the string is not a non terminal
    throw std::domain_error(nt + ": unknown Non Terminal");
}