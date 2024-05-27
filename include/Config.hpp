/*
** EPITECH PROJECT, 2024
** bottom-up-parser
** File description:
** config
*/

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <string>
#include <utility>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <variant>

#include "debug.hpp"

enum class ActionType {
    SHIFT, REDUCE, ACCEPT, GOTO
};

enum NONTERMINAL
{
    CODE,
    DECLINIT,
    DECLTYPE,
    VDECL,
    VDECLVAL,
    ASSIGN,
    RHS,
    FDECL,
    ARG,
    MOREARGS,
    BLOCK,
    STMT,
    ELSE,
    RETURN,
    COND,
    MORECOND,
    EXPR,
    TERM,
    FACTOR,
};
enum TERMINAL
{
    VTYPE,
    ID,
    SEMI,
    TERM_ASSIGN,
    LITERAL,
    CHARACTER,
    BOOLSTR,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    COMMA,
    IF,
    WHILE,
    TERM_ELSE,
    TERM_RETURN,
    COMP,
    ADDSUB,
    MULTDIV,
    NUM,
    $,
};

class Config {
public:
    Config();
    ~Config();
    TERMINAL getTerminal(std::string terminal);
    NONTERMINAL getNonTerminal(std::string nt);
    std::string terminalsStrings[21] = {
        "vtype",
        "id",
        "semi",
        "assign",
        "literal",
        "character",
        "boolstr",
        "lparen",
        "rparen",
        "lbrace",
        "rbrace",
        "comma",
        "if",
        "while",
        "else",
        "return",
        "comp",
        "addsub",
        "multdiv",
        "num",
        "EOF",
    };

    std::string nonTerminalsStrings[19] = {
        "CODE",
        "DECLINIT",
        "DECLTYPE",
        "VDECL",
        "VDECLVAL",
        "ASSIGN",
        "RHS",
        "FDECL",
        "ARG",
        "MOREARGS",
        "BLOCK",
        "STMT",
        "ELSE",
        "RETURN",
        "COND",
        "MORECOND",
        "EXPR",
        "TERM",
        "FACTOR",
    };

    std::vector<std::pair<std::string, std::string>> productions = {
        {"CODE", "DECLINIT CODE"},
        {"CODE", ""},
        {"DECLINIT", "vtype id DECLTYPE"},
        {"DECLTYPE", "VDECL"},
        {"DECLTYPE", "FDECL"},
        {"VDECL", "VDECLVAL semi"},
        {"VDECLVAL", "ASSIGN"},
        {"VDECLVAL", ""},
        {"ASSIGN", "assign RHS"},
        {"RHS", "EXPR"},
        {"RHS", "literal"},
        {"RHS", "character"},
        {"RHS", "boolstr"},
        {"FDECL", "lparen ARG rparen lbrace BLOCK RETURN lbrace"},
        {"ARG", "vtype id MOREARGS"},
        {"ARG", ""},
        {"MOREARGS", "comma vtype id MOREARGS"},
        {"MOREARGS", ""},
        {"BLOCK", "STMT BLOCK"},
        {"BLOCK", ""},
        {"STMT", "vtype id VDECL"},
        {"STMT", "id ASSIGN semi"},
        {"STMT", "if lparen COND rparen lbrace BLOCK rbrace ELSE"},
        {"STMT", "while lparen COND rparen lbrace BLOCK rbrace"},
        {"ELSE", "else lbrace BLOCK rbrace"},
        {"ELSE", ""},
        {"RETURN", "return RHS semi"},
        {"COND", "boolstr MORECOND"},
        {"MORECOND", "comp boolstr MORECOND"},
        {"MORECOND", ""},
        {"EXPR", "EXPR addsub TERM"},
        {"EXPR", "TERM"},
        {"TERM", "TERM multdiv FACTOR"},
        {"TERM", "FACTOR"},
        {"FACTOR", "lparen EXPR rparen"},
        {"FACTOR", "id"},
        {"FACTOR", "num"}
    };

    std::vector<std::unordered_map<std::variant<NONTERMINAL, TERMINAL>, std::pair<ActionType, int>>> slrTable =
    {
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 2}},
            {NONTERMINAL::DECLINIT, {ActionType::GOTO, 1}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 2}},
            {TERMINAL::$, {ActionType::REDUCE, 1}},
            {NONTERMINAL::CODE, {ActionType::GOTO, 3}},
            {NONTERMINAL::DECLINIT, {ActionType::GOTO, 1}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 4}},
        },
        {
            {TERMINAL::$, {ActionType::ACCEPT, 0}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 7}},
            {TERMINAL::TERM_ASSIGN, {ActionType::SHIFT, 11}},
            {TERMINAL::LPAREN, {ActionType::SHIFT, 9}},
            {NONTERMINAL::VDECLVAL, {ActionType::GOTO, 8}},
            {NONTERMINAL::ASSIGN, {ActionType::GOTO, 10}},
            {NONTERMINAL::DECLTYPE, {ActionType::GOTO, 5}},
            {NONTERMINAL::VDECL, {ActionType::GOTO, 6}},
            {NONTERMINAL::FDECL, {ActionType::GOTO, 7}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 2}},
            {TERMINAL::$, {ActionType::REDUCE, 2}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 3}},
            {TERMINAL::$, {ActionType::REDUCE, 3}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 4}},
            {TERMINAL::$, {ActionType::REDUCE, 4}},
        },
        {
            {TERMINAL::SEMI, {ActionType::SHIFT, 12}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 14}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 15}},
            {NONTERMINAL::ARG, {ActionType::GOTO, 13}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 6}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 23}},
            {TERMINAL::LITERAL, {ActionType::SHIFT, 17}},
            {TERMINAL::CHARACTER, {ActionType::SHIFT, 18}},
            {TERMINAL::BOOLSTR, {ActionType::SHIFT, 19}},
            {TERMINAL::LPAREN, {ActionType::SHIFT, 22}},
            {TERMINAL::NUM, {ActionType::SHIFT, 24}},
            {NONTERMINAL::RHS, {ActionType::GOTO, 15}},
            {NONTERMINAL::EXPR, {ActionType::GOTO, 16}},
            {NONTERMINAL::TERM, {ActionType::GOTO, 20}},
            {NONTERMINAL::FACTOR, {ActionType::GOTO, 21}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 5}},
            {TERMINAL::ID, {ActionType::REDUCE, 5}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 5}},
            {TERMINAL::IF, {ActionType::REDUCE, 5}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 5}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 5}},
            {TERMINAL::$, {ActionType::REDUCE, 5}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::SHIFT, 25}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 26}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 8}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 9}},
            {TERMINAL::ADDSUB, {ActionType::SHIFT, 27}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 10}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 11}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 12}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 31}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 31}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 31}},
            {TERMINAL::MULTDIV, {ActionType::SHIFT, 28}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 33}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 33}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 33}},
            {TERMINAL::MULTDIV, {ActionType::REDUCE, 33}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 23}},
            {TERMINAL::LPAREN, {ActionType::SHIFT, 22}},
            {TERMINAL::NUM, {ActionType::SHIFT, 24}},
            {NONTERMINAL::EXPR, {ActionType::GOTO, 29}},
            {NONTERMINAL::TERM, {ActionType::GOTO, 20}},
            {NONTERMINAL::FACTOR, {ActionType::GOTO, 21}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 35}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 35}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 35}},
            {TERMINAL::MULTDIV, {ActionType::REDUCE, 35}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 36}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 36}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 36}},
            {TERMINAL::MULTDIV, {ActionType::REDUCE, 36}},
        },
        {
            {TERMINAL::LBRACE, {ActionType::SHIFT, 30}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 17}},
            {TERMINAL::COMMA, {ActionType::SHIFT, 32}},
            {NONTERMINAL::MOREARGS, {ActionType::GOTO, 31}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 23}},
            {TERMINAL::LPAREN, {ActionType::SHIFT, 22}},
            {TERMINAL::NUM, {ActionType::SHIFT, 24}},
            {NONTERMINAL::TERM, {ActionType::GOTO, 33}},
            {NONTERMINAL::FACTOR, {ActionType::GOTO, 21}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 23}},
            {TERMINAL::LPAREN, {ActionType::SHIFT, 22}},
            {TERMINAL::NUM, {ActionType::SHIFT, 24}},
            {NONTERMINAL::FACTOR, {ActionType::GOTO, 34}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::SHIFT, 35}},
            {TERMINAL::ADDSUB, {ActionType::SHIFT, 27}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 38}},
            {TERMINAL::ID, {ActionType::SHIFT, 39}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 19}},
            {TERMINAL::IF, {ActionType::SHIFT, 40}},
            {TERMINAL::WHILE, {ActionType::SHIFT, 41}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 19}},
            {NONTERMINAL::BLOCK, {ActionType::GOTO, 36}},
            {NONTERMINAL::STMT, {ActionType::GOTO, 37}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 14}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 42}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 30}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 30}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 30}},
            {TERMINAL::MULTDIV, {ActionType::SHIFT, 28}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 32}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 32}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 32}},
            {TERMINAL::MULTDIV, {ActionType::REDUCE, 32}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 34}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 34}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 34}},
            {TERMINAL::MULTDIV, {ActionType::REDUCE, 34}},
        },
        {
            {TERMINAL::TERM_RETURN, {ActionType::SHIFT, 44}},
            {NONTERMINAL::RETURN, {ActionType::GOTO, 43}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 38}},
            {TERMINAL::ID, {ActionType::SHIFT, 39}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 19}},
            {TERMINAL::IF, {ActionType::SHIFT, 40}},
            {TERMINAL::WHILE, {ActionType::SHIFT, 41}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 19}},
            {NONTERMINAL::BLOCK, {ActionType::GOTO, 45}},
            {NONTERMINAL::STMT, {ActionType::GOTO, 37}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 46}},
        },
        {
            {TERMINAL::TERM_ASSIGN, {ActionType::SHIFT, 11}},
            {NONTERMINAL::ASSIGN, {ActionType::GOTO, 47}},
        },
        {
            {TERMINAL::LPAREN, {ActionType::SHIFT, 48}},
        },
        {
            {TERMINAL::LPAREN, {ActionType::SHIFT, 49}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 50}},
        },
        {
            {TERMINAL::RBRACE, {ActionType::SHIFT, 51}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 23}},
            {TERMINAL::LITERAL, {ActionType::SHIFT, 17}},
            {TERMINAL::CHARACTER, {ActionType::SHIFT, 18}},
            {TERMINAL::BOOLSTR, {ActionType::SHIFT, 19}},
            {TERMINAL::LPAREN, {ActionType::SHIFT, 22}},
            {TERMINAL::NUM, {ActionType::SHIFT, 24}},
            {NONTERMINAL::RHS, {ActionType::GOTO, 52}},
            {NONTERMINAL::EXPR, {ActionType::GOTO, 16}},
            {NONTERMINAL::TERM, {ActionType::GOTO, 20}},
            {NONTERMINAL::FACTOR, {ActionType::GOTO, 21}},
        },
        {
            {TERMINAL::RBRACE, {ActionType::REDUCE, 18}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 18}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 7}},
            {TERMINAL::TERM_ASSIGN, {ActionType::SHIFT, 11}},
            {NONTERMINAL::VDECL, {ActionType::GOTO, 53}},
            {NONTERMINAL::VDECLVAL, {ActionType::GOTO, 8}},
            {NONTERMINAL::ASSIGN, {ActionType::GOTO, 10}},
        },
        {
            {TERMINAL::SEMI, {ActionType::SHIFT, 54}},
        },
        {
            {TERMINAL::BOOLSTR, {ActionType::SHIFT, 56}},
            {NONTERMINAL::COND, {ActionType::GOTO, 55}},
        },
        {
            {TERMINAL::BOOLSTR, {ActionType::SHIFT, 56}},
            {NONTERMINAL::MORECOND, {ActionType::GOTO, 57}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 17}},
            {TERMINAL::COMMA, {ActionType::SHIFT, 32}},
            {NONTERMINAL::MOREARGS, {ActionType::GOTO, 58}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 13}},
            {TERMINAL::$, {ActionType::REDUCE, 13}},
        },
        {
            {TERMINAL::SEMI, {ActionType::SHIFT, 59}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 20}},
            {TERMINAL::ID, {ActionType::REDUCE, 20}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 20}},
            {TERMINAL::IF, {ActionType::REDUCE, 20}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 20}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 20}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 21}},
            {TERMINAL::ID, {ActionType::REDUCE, 21}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 21}},
            {TERMINAL::IF, {ActionType::REDUCE, 21}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 21}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 21}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::SHIFT, 60}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 29}},
            {TERMINAL::COMP, {ActionType::SHIFT, 62}},
            {NONTERMINAL::MORECOND, {ActionType::GOTO, 61}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::SHIFT, 63}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 16}},
        },
        {
            {TERMINAL::RBRACE, {ActionType::REDUCE, 26}},
        },
        {
            {TERMINAL::LBRACE, {ActionType::SHIFT, 64}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 27}},
        },
        {
            {TERMINAL::BOOLSTR, {ActionType::SHIFT, 65}},
        },
        {
            {TERMINAL::LBRACE, {ActionType::SHIFT, 66}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 38}},
            {TERMINAL::ID, {ActionType::SHIFT, 39}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 19}},
            {TERMINAL::IF, {ActionType::SHIFT, 40}},
            {TERMINAL::WHILE, {ActionType::SHIFT, 41}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 19}},
            {NONTERMINAL::BLOCK, {ActionType::GOTO, 67}},
            {NONTERMINAL::STMT, {ActionType::GOTO, 37}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 29}},
            {TERMINAL::COMP, {ActionType::SHIFT, 62}},
            {NONTERMINAL::MORECOND, {ActionType::GOTO, 68}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 38}},
            {TERMINAL::ID, {ActionType::SHIFT, 39}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 19}},
            {TERMINAL::IF, {ActionType::SHIFT, 40}},
            {TERMINAL::WHILE, {ActionType::SHIFT, 41}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 19}},
            {NONTERMINAL::BLOCK, {ActionType::GOTO, 69}},
            {NONTERMINAL::STMT, {ActionType::GOTO, 37}},
        },
        {
            {TERMINAL::RBRACE, {ActionType::SHIFT, 70}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 28}}
        },
        {
            {TERMINAL::RBRACE, {ActionType::SHIFT, 71}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 25}},
            {TERMINAL::ID, {ActionType::REDUCE, 25}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 25}},
            {TERMINAL::IF, {ActionType::REDUCE, 25}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 25}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 25}},
            {TERMINAL::TERM_ELSE, {ActionType::SHIFT, 73}},
            {NONTERMINAL::ELSE, {ActionType::GOTO, 72}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 23}},
            {TERMINAL::ID, {ActionType::REDUCE, 23}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 23}},
            {TERMINAL::IF, {ActionType::REDUCE, 23}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 23}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 23}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 22}},
            {TERMINAL::ID, {ActionType::REDUCE, 22}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 22}},
            {TERMINAL::IF, {ActionType::REDUCE, 22}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 22}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 22}},
        },
        {
            {TERMINAL::LBRACE, {ActionType::SHIFT, 74}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 38}},
            {TERMINAL::ID, {ActionType::SHIFT, 39}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 19}},
            {TERMINAL::IF, {ActionType::SHIFT, 40}},
            {TERMINAL::WHILE, {ActionType::SHIFT, 41}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 19}},
            {NONTERMINAL::BLOCK, {ActionType::GOTO, 75}},
            {NONTERMINAL::STMT, {ActionType::GOTO, 37}},
        },
        {
            {TERMINAL::RBRACE, {ActionType::SHIFT, 76}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 24}},
            {TERMINAL::ID, {ActionType::REDUCE, 24}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 24}},
            {TERMINAL::IF, {ActionType::REDUCE, 24}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 24}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 24}},
        }
    };



private:
};
#endif /* !CONFIG_HPP_ */
