/*
** EPITECH PROJECT, 2024
** bottom-up-parser
** File description:
** ParseTree
*/

#ifndef PARSETREE_HPP_
#define PARSETREE_HPP_

#include <queue>


#include "Config.hpp"

class ParseTreeNode {
    public:
        ParseTreeNode(std::variant<NONTERMINAL, TERMINAL> self);
        ~ParseTreeNode();

        std::vector<ParseTreeNode> children;
        std::variant<NONTERMINAL, TERMINAL> self;

        void addChild(ParseTreeNode child);
        std::queue<ParseTreeNode> popNNextNodes(int n);
        void acceptTree(Config *c, NONTERMINAL cfgStartSymbol);

    protected:
    private:
        void displayParseTree(int depth, Config *c);
};

#endif /* !PARSETREE_HPP_ */
