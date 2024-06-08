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
    VDECL,
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
    MOREEXPR,
    TERM,
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

    std::string nonTerminalsStrings[17] = {
        "PROGRAM",
        "CODE",
        "VDECL",
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
        "MOREEXPR",
        "TERM",
    };

    // The productions as written in the CFG.
    // Epsilon are represented by empty strings
    std::vector<std::pair<std::string, std::string>> productions = {
        {"PROGRAM", "CODE"},
        {"CODE", "VDECL CODE"},
        {"CODE", "FDECL CODE"},
        {"CODE", ""},
        {"VDECL", "vtype id semi"},
        {"VDECL", "vtype ASSIGN semi"},
        {"ASSIGN", "id assign RHS"},
        {"RHS", "EXPR"},
        {"RHS", "literal"},
        {"RHS", "character"},
        {"RHS", "boolstr"},
        {"FDECL", "vtype id lparen ARG rparen lbrace BLOCK RETURN lbrace"},
        {"ARG", "vtype id MOREARGS"},
        {"ARG", ""},
        {"MOREARGS", "comma vtype id MOREARGS"},
        {"MOREARGS", ""},
        {"BLOCK", "STMT BLOCK"},
        {"BLOCK", ""},
        {"STMT", "VDECL"},
        {"STMT", "ASSIGN semi"},
        {"STMT", "if lparen COND rparen lbrace BLOCK rbrace ELSE"},
        {"STMT", "while lparen COND rparen lbrace BLOCK rbrace"},
        {"ELSE", "else lbrace BLOCK rbrace"},
        {"ELSE", ""},
        {"RETURN", "return RHS semi"},
        {"COND", "boolstr MORECOND"},
        {"MORECOND", "comp boolstr MORECOND"},
        {"MORECOND", ""},
        {"EXPR", "EXPR addsub MOREEXPR"},
        {"EXPR", "MOREEXPR"},
        {"MOREEXPR", "MOREEXPR multdiv TERM"},
        {"MOREEXPR", "TERM"},
        {"TERM", "lparen EXPR rparen"},
        {"TERM", "id"},
        {"TERM", "num"}
    };

    // The representation of the SLR table
    // One vector corresponding to each state, containing a map of the transitions possible with the corresponding actions
    std::vector<std::unordered_map<std::variant<NONTERMINAL, TERMINAL>, std::pair<ActionType, int>>> slrTable =
    {
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 4}},
            {TERMINAL::$, {ActionType::REDUCE, 3}},
            {NONTERMINAL::CODE, {ActionType::GOTO, 1}},
            {NONTERMINAL::VDECL, {ActionType::GOTO, 2}},
            {NONTERMINAL::FDECL, {ActionType::GOTO, 3}},
        },
        {
            {TERMINAL::$, {ActionType::ACCEPT, 0}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 4}},
            {TERMINAL::$, {ActionType::REDUCE, 3}},
            {NONTERMINAL::CODE, {ActionType::GOTO, 5}},
            {NONTERMINAL::VDECL, {ActionType::GOTO, 2}},
            {NONTERMINAL::FDECL, {ActionType::GOTO, 3}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 4}},
            {TERMINAL::$, {ActionType::REDUCE, 3}},
            {NONTERMINAL::CODE, {ActionType::GOTO, 6}},
            {NONTERMINAL::VDECL, {ActionType::GOTO, 2}},
            {NONTERMINAL::FDECL, {ActionType::GOTO, 3}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 7}},
            {NONTERMINAL::ASSIGN, {ActionType::GOTO, 8}},
        },
        {
            {TERMINAL::$, {ActionType::REDUCE, 1}},
        },
        {
            {TERMINAL::$, {ActionType::REDUCE, 2}},
        },
        {
            {TERMINAL::SEMI, {ActionType::SHIFT, 9}},
            {TERMINAL::TERM_ASSIGN, {ActionType::SHIFT, 11}},
            {TERMINAL::LPAREN, {ActionType::SHIFT, 10}},
        },
        {
            {TERMINAL::SEMI, {ActionType::SHIFT, 12}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 4}},
            {TERMINAL::ID, {ActionType::REDUCE, 4}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 4}},
            {TERMINAL::IF, {ActionType::REDUCE, 4}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 4}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 4}},
            {TERMINAL::$, {ActionType::REDUCE, 4}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 14}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 13}},
            {NONTERMINAL::ARG, {ActionType::GOTO, 13}},
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
            {NONTERMINAL::MOREEXPR, {ActionType::GOTO, 20}},
            {NONTERMINAL::TERM, {ActionType::GOTO, 21}},
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
            {TERMINAL::SEMI, {ActionType::REDUCE, 6}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 7}},
            {TERMINAL::ADDSUB, {ActionType::SHIFT, 27}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 8}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 9}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 10}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 29}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 29}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 29}},
            {TERMINAL::MULTDIV, {ActionType::SHIFT, 28}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 31}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 31}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 31}},
            {TERMINAL::MULTDIV, {ActionType::REDUCE, 31}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 23}},
            {TERMINAL::LPAREN, {ActionType::SHIFT, 22}},
            {TERMINAL::NUM, {ActionType::SHIFT, 24}},
            {NONTERMINAL::EXPR, {ActionType::GOTO, 29}},
            {NONTERMINAL::MOREEXPR, {ActionType::GOTO, 20}},
            {NONTERMINAL::TERM, {ActionType::GOTO, 21}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 33}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 33}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 33}},
            {TERMINAL::MULTDIV, {ActionType::REDUCE, 33}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 34}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 34}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 34}},
            {TERMINAL::MULTDIV, {ActionType::REDUCE, 34}},
        },
        {
            {TERMINAL::LBRACE, {ActionType::SHIFT, 30}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 15}},
            {TERMINAL::COMMA, {ActionType::SHIFT, 32}},
            {NONTERMINAL::MOREARGS, {ActionType::GOTO, 31}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 23}},
            {TERMINAL::LPAREN, {ActionType::SHIFT, 22}},
            {TERMINAL::NUM, {ActionType::SHIFT, 24}},
            {NONTERMINAL::MOREEXPR, {ActionType::GOTO, 33}},
            {NONTERMINAL::TERM, {ActionType::GOTO, 21}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 23}},
            {TERMINAL::LPAREN, {ActionType::SHIFT, 22}},
            {TERMINAL::NUM, {ActionType::SHIFT, 24}},
            {NONTERMINAL::TERM, {ActionType::GOTO, 34}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::SHIFT, 35}},
            {TERMINAL::ADDSUB, {ActionType::SHIFT, 27}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 42}},
            {TERMINAL::ID, {ActionType::SHIFT, 43}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 17}},
            {TERMINAL::IF, {ActionType::SHIFT, 40}},
            {TERMINAL::WHILE, {ActionType::SHIFT, 41}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 17}},
            {NONTERMINAL::VDECL, {ActionType::GOTO, 38}},
            {NONTERMINAL::ASSIGN, {ActionType::GOTO, 39}},
            {NONTERMINAL::BLOCK, {ActionType::GOTO, 36}},
            {NONTERMINAL::STMT, {ActionType::GOTO, 37}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 12}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 44}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 28}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 28}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 28}},
            {TERMINAL::MULTDIV, {ActionType::SHIFT, 28}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 30}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 30}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 30}},
            {TERMINAL::MULTDIV, {ActionType::REDUCE, 30}},
        },
        {
            {TERMINAL::SEMI, {ActionType::REDUCE, 32}},
            {TERMINAL::RPAREN, {ActionType::REDUCE, 32}},
            {TERMINAL::ADDSUB, {ActionType::REDUCE, 32}},
            {TERMINAL::MULTDIV, {ActionType::REDUCE, 32}},
        },
        {
            {TERMINAL::TERM_RETURN, {ActionType::SHIFT, 46}},
            {NONTERMINAL::RETURN, {ActionType::GOTO, 45}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 42}},
            {TERMINAL::ID, {ActionType::SHIFT, 43}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 17}},
            {TERMINAL::IF, {ActionType::SHIFT, 40}},
            {TERMINAL::WHILE, {ActionType::SHIFT, 41}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 17}},
            {NONTERMINAL::VDECL, {ActionType::GOTO, 38}},
            {NONTERMINAL::ASSIGN, {ActionType::GOTO, 39}},
            {NONTERMINAL::BLOCK, {ActionType::GOTO, 47}},
            {NONTERMINAL::STMT, {ActionType::GOTO, 37}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 18}},
            {TERMINAL::ID, {ActionType::REDUCE, 18}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 18}},
            {TERMINAL::IF, {ActionType::REDUCE, 18}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 18}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 18}},
        },
        {
            {TERMINAL::SEMI, {ActionType::SHIFT, 48}},
        },
        {
            {TERMINAL::LPAREN, {ActionType::SHIFT, 49}},
        },
        {
            {TERMINAL::LPAREN, {ActionType::SHIFT, 50}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 51}},
            {NONTERMINAL::ASSIGN, {ActionType::GOTO, 8}},
        },
        {
            {TERMINAL::TERM_ASSIGN, {ActionType::SHIFT, 11}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 52}},
        },
        {
            {TERMINAL::RBRACE, {ActionType::SHIFT, 53}},
        },
        {
            {TERMINAL::ID, {ActionType::SHIFT, 23}},
            {TERMINAL::LITERAL, {ActionType::SHIFT, 17}},
            {TERMINAL::CHARACTER, {ActionType::SHIFT, 18}},
            {TERMINAL::BOOLSTR, {ActionType::SHIFT, 19}},
            {TERMINAL::LPAREN, {ActionType::SHIFT, 22}},
            {TERMINAL::NUM, {ActionType::SHIFT, 24}},
            {NONTERMINAL::RHS, {ActionType::GOTO, 54}},
            {NONTERMINAL::EXPR, {ActionType::GOTO, 16}},
            {NONTERMINAL::MOREEXPR, {ActionType::GOTO, 20}},
            {NONTERMINAL::TERM, {ActionType::GOTO, 21}},
        },
        {
            {TERMINAL::RBRACE, {ActionType::REDUCE, 16}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 16}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 19}},
            {TERMINAL::ID, {ActionType::REDUCE, 19}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 19}},
            {TERMINAL::IF, {ActionType::REDUCE, 19}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 19}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 19}},
        },
        {
            {TERMINAL::BOOLSTR, {ActionType::SHIFT, 56}},
            {NONTERMINAL::COND, {ActionType::GOTO, 55}},
        },
        {
            {TERMINAL::BOOLSTR, {ActionType::SHIFT, 56}},
            {NONTERMINAL::COND, {ActionType::GOTO, 57}},
        },
        {
            {TERMINAL::SEMI, {ActionType::SHIFT, 9}},
            {TERMINAL::TERM_ASSIGN, {ActionType::SHIFT, 11}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 15}},
            {TERMINAL::COMMA, {ActionType::SHIFT, 32}},
            {NONTERMINAL::MOREARGS, {ActionType::GOTO, 58}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 11}},
            {TERMINAL::$, {ActionType::REDUCE, 11}},
        },
        {
            {TERMINAL::SEMI, {ActionType::SHIFT, 59}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::SHIFT, 60}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 27}},
            {TERMINAL::COMP, {ActionType::SHIFT, 62}},
            {NONTERMINAL::MORECOND, {ActionType::GOTO, 61}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::SHIFT, 63}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 14}},
        },
        {
            {TERMINAL::RBRACE, {ActionType::REDUCE, 24}},
        },
        {
            {TERMINAL::LBRACE, {ActionType::SHIFT, 64}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 25}},
        },
        {
            {TERMINAL::BOOLSTR, {ActionType::SHIFT, 65}},
        },
        {
            {TERMINAL::LBRACE, {ActionType::SHIFT, 66}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 42}},
            {TERMINAL::ID, {ActionType::SHIFT, 43}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 17}},
            {TERMINAL::IF, {ActionType::SHIFT, 40}},
            {TERMINAL::WHILE, {ActionType::SHIFT, 41}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 17}},
            {NONTERMINAL::VDECL, {ActionType::GOTO, 38}},
            {NONTERMINAL::ASSIGN, {ActionType::GOTO, 39}},
            {NONTERMINAL::BLOCK, {ActionType::GOTO, 67}},
            {NONTERMINAL::STMT, {ActionType::GOTO, 37}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 27}},
            {TERMINAL::COMP, {ActionType::SHIFT, 62}},
            {NONTERMINAL::MORECOND, {ActionType::GOTO, 68}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 42}},
            {TERMINAL::ID, {ActionType::SHIFT, 43}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 17}},
            {TERMINAL::IF, {ActionType::SHIFT, 40}},
            {TERMINAL::WHILE, {ActionType::SHIFT, 41}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 17}},
            {NONTERMINAL::VDECL, {ActionType::GOTO, 38}},
            {NONTERMINAL::ASSIGN, {ActionType::GOTO, 39}},
            {NONTERMINAL::BLOCK, {ActionType::GOTO, 69}},
            {NONTERMINAL::STMT, {ActionType::GOTO, 37}},
        },
        {
            {TERMINAL::RBRACE, {ActionType::SHIFT, 70}},
        },
        {
            {TERMINAL::RPAREN, {ActionType::REDUCE, 26}},
        },
        {
            {TERMINAL::RBRACE, {ActionType::SHIFT, 71}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 23}},
            {TERMINAL::ID, {ActionType::REDUCE, 23}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 23}},
            {TERMINAL::IF, {ActionType::REDUCE, 23}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 23}},
            {TERMINAL::TERM_ELSE, {ActionType::SHIFT, 73}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 23}},
            {NONTERMINAL::ELSE, {ActionType::GOTO, 72}},
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
            {TERMINAL::VTYPE, {ActionType::REDUCE, 20}},
            {TERMINAL::ID, {ActionType::REDUCE, 20}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 20}},
            {TERMINAL::IF, {ActionType::REDUCE, 20}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 20}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 20}},
        },
        {
            {TERMINAL::LBRACE, {ActionType::SHIFT, 74}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::SHIFT, 42}},
            {TERMINAL::ID, {ActionType::SHIFT, 43}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 17}},
            {TERMINAL::IF, {ActionType::SHIFT, 40}},
            {TERMINAL::WHILE, {ActionType::SHIFT, 41}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 17}},
            {NONTERMINAL::VDECL, {ActionType::GOTO, 38}},
            {NONTERMINAL::ASSIGN, {ActionType::GOTO, 39}},
            {NONTERMINAL::BLOCK, {ActionType::GOTO, 75}},
            {NONTERMINAL::STMT, {ActionType::GOTO, 37}},
        },
        {
            {TERMINAL::RBRACE, {ActionType::SHIFT, 76}},
        },
        {
            {TERMINAL::VTYPE, {ActionType::REDUCE, 22}},
            {TERMINAL::ID, {ActionType::REDUCE, 22}},
            {TERMINAL::RBRACE, {ActionType::REDUCE, 22}},
            {TERMINAL::IF, {ActionType::REDUCE, 22}},
            {TERMINAL::WHILE, {ActionType::REDUCE, 22}},
            {TERMINAL::TERM_RETURN, {ActionType::REDUCE, 22}},
        }

    };



private:
};
#endif /* !CONFIG_HPP_ */
