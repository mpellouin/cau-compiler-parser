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
    PROGRAM,
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

    /**
     * @brief Get the Terminal from its corresponding string
     * 
     * @param terminal: the string to convert
     * @return TERMINAL 
     */
    TERMINAL getTerminal(std::string terminal);

    /**
     * @brief Get the Non Terminal from its corresponding string
     * 
     * @param nt: the string to convert
     * @return NONTERMINAL 
     */
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

    std::string nonTerminalsStrings[20] = {
        "PROGRAM",
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

    // The productions as written in the CFG.
    // Epsilon are represented by empty strings
    std::vector<std::pair<std::string, std::string>> productions = {
        {"PROGRAM", "CODE"},
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

    // The representation of the SLR table
    // One vector corresponding to each state, containing a map of the transitions possible with the corresponding actions
    std::vector<std::unordered_map<std::variant<NONTERMINAL, TERMINAL>, std::pair<ActionType, int>>> slrTable =
    {
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 3}},
            {TERMINAL::$, {ActionType::REDUCE, 2}},
            {NONTERMINAL::CODE, {ActionType::GOTO, 1}},
            {NONTERMINAL::DECLINIT, {ActionType::GOTO, 2}},
        },
        {
            {TERMINAL::$, {ActionType::ACCEPT, 0}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 3}},
            {TERMINAL::$, {ActionType::REDUCE, 2}},
            {NONTERMINAL::CODE, {ActionType::GOTO, 4}},
            {NONTERMINAL::DECLINIT, {ActionType::GOTO, 2}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 5}},
        },
        {
            {TERMINAL::$, {ActionType::REDUCE, 1}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 8}},
            {TERMINAL::TERM_ASSIGN, {ActionType::SHIFT, 12}},
            {TERMINAL::LPAREN, {ActionType::SHIFT, 10}},
            {NONTERMINAL::VDECLVAL, {ActionType::GOTO, 9}},
            {NONTERMINAL::ASSIGN, {ActionType::GOTO, 11}},
            {NONTERMINAL::DECLTYPE, {ActionType::GOTO, 6}},
            {NONTERMINAL::VDECL, {ActionType::GOTO, 7}},
            {NONTERMINAL::FDECL, {ActionType::GOTO, 8}},
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
            {TERMINAL::VTYPE, {ActionType::REDUCE, 5}},
            {TERMINAL::$, {ActionType::REDUCE, 5}},
        },
        {
            {TERMINAL::SEMI, {ActionType::SHIFT, 13}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 15}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 16}},
            {NONTERMINAL::ARG, {ActionType::GOTO, 14}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 7}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 24}},
            {TERMINAL::LITERAL, {ActionType::SHIFT, 18}},
            {TERMINAL::CHARACTER, {ActionType::SHIFT, 19}},
            {TERMINAL::BOOLSTR, {ActionType::SHIFT, 20}},
            {TERMINAL::LPAREN, {ActionType::SHIFT, 23}},
            {TERMINAL::NUM, {ActionType::SHIFT, 25}},
            {NONTERMINAL::RHS, {ActionType::GOTO, 16}},
            {NONTERMINAL::EXPR, {ActionType::GOTO, 17}},
            {NONTERMINAL::TERM, {ActionType::GOTO, 21}},
            {NONTERMINAL::FACTOR, {ActionType::GOTO, 22}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 6}},
            {TERMINAL::ID, {ActionType::REDUCE, 6}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 6}},
            {TERMINAL::IF, {ActionType::REDUCE, 6}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 6}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 6}},
            {TERMINAL::$, {ActionType::REDUCE, 6}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::SHIFT, 26}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 27}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 9}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 10}},
            {TERMINAL::ADDSUB, {ActionType::SHIFT, 28}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 11}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 12}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 13}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 32}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 32}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 32}},
            {TERMINAL::MULTDIV, {ActionType::SHIFT, 29}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 34}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 34}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 34}},
            {TERMINAL::MULTDIV, {ActionType::REDUCE, 34}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 24}},
            {TERMINAL::LPAREN, {ActionType::SHIFT, 23}},
            {TERMINAL::NUM, {ActionType::SHIFT, 25}},
            {NONTERMINAL::EXPR, {ActionType::GOTO, 30}},
            {NONTERMINAL::TERM, {ActionType::GOTO, 21}},
            {NONTERMINAL::FACTOR, {ActionType::GOTO, 22}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 36}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 36}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 36}},
            {TERMINAL::MULTDIV, {ActionType::REDUCE, 36}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 37}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 37}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 37}},
            {TERMINAL::MULTDIV, {ActionType::REDUCE, 37}},
        },
        {
            {TERMINAL::LBRACE, {ActionType::SHIFT, 31}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 18}},
            {TERMINAL::COMMA, {ActionType::SHIFT, 33}},
            {NONTERMINAL::MOREARGS, {ActionType::GOTO, 32}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 24}},
            {TERMINAL::LPAREN, {ActionType::SHIFT, 23}},
            {TERMINAL::NUM, {ActionType::SHIFT, 25}},
            {NONTERMINAL::TERM, {ActionType::GOTO, 34}},
            {NONTERMINAL::FACTOR, {ActionType::GOTO, 22}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 24}},
            {TERMINAL::LPAREN, {ActionType::SHIFT, 23}},
            {TERMINAL::NUM, {ActionType::SHIFT, 25}},
            {NONTERMINAL::FACTOR, {ActionType::GOTO, 35}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::SHIFT, 36}},
            {TERMINAL::ADDSUB, {ActionType::SHIFT, 28}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 39}},
            {TERMINAL::ID, {ActionType::SHIFT, 40}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 20}},
            {TERMINAL::IF, {ActionType::SHIFT, 41}},
            {TERMINAL::WHILE, {ActionType::SHIFT, 42}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 20}},
            {NONTERMINAL::BLOCK, {ActionType::GOTO, 37}},
            {NONTERMINAL::STMT, {ActionType::GOTO, 38}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 15}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 43}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 31}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 31}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 31}},
            {TERMINAL::MULTDIV, {ActionType::SHIFT, 29}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 33}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 33}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 33}},
            {TERMINAL::MULTDIV, {ActionType::REDUCE, 33}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 35}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 35}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 35}},
            {TERMINAL::MULTDIV, {ActionType::REDUCE, 35}},
        },
        {
            {TERMINAL::TERM_RETURN, {ActionType::SHIFT, 45}},
            {NONTERMINAL::RETURN, {ActionType::GOTO, 44}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 39}},
            {TERMINAL::ID, {ActionType::SHIFT, 40}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 20}},
            {TERMINAL::IF, {ActionType::SHIFT, 41}},
            {TERMINAL::WHILE, {ActionType::SHIFT, 42}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 20}},
            {NONTERMINAL::BLOCK, {ActionType::GOTO, 46}},
            {NONTERMINAL::STMT, {ActionType::GOTO, 38}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 47}},
        },
        {
            {TERMINAL::TERM_ASSIGN, {ActionType::SHIFT, 12}},
            {NONTERMINAL::ASSIGN, {ActionType::GOTO, 48}},
        },
        {
            {TERMINAL::LPAREN, {ActionType::SHIFT, 49}},
        },
        {
            {TERMINAL::LPAREN, {ActionType::SHIFT, 50}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 51}},
        },
        {
            {TERMINAL::RBRACE, {ActionType::SHIFT, 52}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 24}},
            {TERMINAL::LITERAL, {ActionType::SHIFT, 18}},
            {TERMINAL::CHARACTER, {ActionType::SHIFT, 19}},
            {TERMINAL::BOOLSTR, {ActionType::SHIFT, 20}},
            {TERMINAL::LPAREN, {ActionType::SHIFT, 23}},
            {TERMINAL::NUM, {ActionType::SHIFT, 25}},
            {NONTERMINAL::RHS, {ActionType::GOTO, 53}},
            {NONTERMINAL::EXPR, {ActionType::GOTO, 17}},
            {NONTERMINAL::TERM, {ActionType::GOTO, 21}},
            {NONTERMINAL::FACTOR, {ActionType::GOTO, 22}},
        },
        {
            {TERMINAL::RBRACE, {ActionType::REDUCE, 19}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 19}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 8}},
            {TERMINAL::TERM_ASSIGN, {ActionType::SHIFT, 12}},
            {NONTERMINAL::VDECL, {ActionType::GOTO, 54}},
            {NONTERMINAL::VDECLVAL, {ActionType::GOTO, 9}},
            {NONTERMINAL::ASSIGN, {ActionType::GOTO, 11}},
        },
        {
            {TERMINAL::SEMI, {ActionType::SHIFT, 55}},
        },
        {
            {TERMINAL::BOOLSTR, {ActionType::SHIFT, 57}},
            {NONTERMINAL::COND, {ActionType::GOTO, 56}},
        },
        {
            {TERMINAL::BOOLSTR, {ActionType::SHIFT, 57}},
            {NONTERMINAL::COND, {ActionType::GOTO, 58}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 18}},
            {TERMINAL::COMMA, {ActionType::SHIFT, 33}},
            {NONTERMINAL::MOREARGS, {ActionType::GOTO, 59}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 14}},
            {TERMINAL::$, {ActionType::REDUCE, 14}},
        },
        {
            {TERMINAL::SEMI, {ActionType::SHIFT, 60}},
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
            {TERMINAL::VTYPE, {ActionType::REDUCE, 22}},
            {TERMINAL::ID, {ActionType::REDUCE, 22}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 22}},
            {TERMINAL::IF, {ActionType::REDUCE, 22}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 22}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 22}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::SHIFT, 61}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 30}},
            {TERMINAL::COMP, {ActionType::SHIFT, 63}},
            {NONTERMINAL::MORECOND, {ActionType::GOTO, 62}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::SHIFT, 64}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 17}},
        },
        {
            {TERMINAL::RBRACE, {ActionType::REDUCE, 27}},
        },
        {
            {TERMINAL::LBRACE, {ActionType::SHIFT, 65}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 28}},
        },
        {
            {TERMINAL::BOOLSTR, {ActionType::SHIFT, 66}},
        },
        {
            {TERMINAL::LBRACE, {ActionType::SHIFT, 67}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 39}},
            {TERMINAL::ID, {ActionType::SHIFT, 40}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 20}},
            {TERMINAL::IF, {ActionType::SHIFT, 41}},
            {TERMINAL::WHILE, {ActionType::SHIFT, 42}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 20}},
            {NONTERMINAL::BLOCK, {ActionType::GOTO, 68}},
            {NONTERMINAL::STMT, {ActionType::GOTO, 38}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 30}},
            {TERMINAL::COMP, {ActionType::SHIFT, 63}},
            {NONTERMINAL::MORECOND, {ActionType::GOTO, 69}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 39}},
            {TERMINAL::ID, {ActionType::SHIFT, 40}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 20}},
            {TERMINAL::IF, {ActionType::SHIFT, 41}},
            {TERMINAL::WHILE, {ActionType::SHIFT, 42}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 20}},
            {NONTERMINAL::BLOCK, {ActionType::GOTO, 70}},
            {NONTERMINAL::STMT, {ActionType::GOTO, 38}},
        },
        {
            {TERMINAL::RBRACE, {ActionType::SHIFT, 71}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 29}}
        },
        {
            {TERMINAL::RBRACE, {ActionType::SHIFT, 72}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 26}},
            {TERMINAL::ID, {ActionType::REDUCE, 26}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 26}},
            {TERMINAL::IF, {ActionType::REDUCE, 26}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 26}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 26}},
            {TERMINAL::TERM_ELSE, {ActionType::SHIFT, 74}},
            {NONTERMINAL::ELSE, {ActionType::GOTO, 73}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 24}},
            {TERMINAL::ID, {ActionType::REDUCE, 24}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 24}},
            {TERMINAL::IF, {ActionType::REDUCE, 24}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 24}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 24}},
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
            {TERMINAL::LBRACE, {ActionType::SHIFT, 75}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 39}},
            {TERMINAL::ID, {ActionType::SHIFT, 40}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 20}},
            {TERMINAL::IF, {ActionType::SHIFT, 41}},
            {TERMINAL::WHILE, {ActionType::SHIFT, 42}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 20}},
            {NONTERMINAL::BLOCK, {ActionType::GOTO, 76}},
            {NONTERMINAL::STMT, {ActionType::GOTO, 38}},
        },
        {
            {TERMINAL::RBRACE, {ActionType::SHIFT, 77}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 25}},
            {TERMINAL::ID, {ActionType::REDUCE, 25}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 25}},
            {TERMINAL::IF, {ActionType::REDUCE, 25}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 25}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 25}},
        }
    };



private:
};
#endif /* !CONFIG_HPP_ */
