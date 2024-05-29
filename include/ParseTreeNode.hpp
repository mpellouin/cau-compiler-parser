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

        /**
         * @brief Adds a child to the current node
         * 
         * @param child 
         */
        void addChild(ParseTreeNode child);

        /**
         * @brief Gets the n rightmost children from the current node, pop them and return them
         * 
         * @param n 
         * @return std::queue<ParseTreeNode> 
         */
        std::queue<ParseTreeNode> popNNextNodes(int n);

        /**
         * @brief Sets the start symbol of the CFG and displays the parse tree
         * 
         * @param c 
         * @param cfgStartSymbol 
         */
        void acceptTree(Config *c, NONTERMINAL cfgStartSymbol);

    protected:
    private:
        /**
         * @brief Displays the parse tree
         * 
         * @param depth - depth of the tree, used for recursion
         * @param c 
         */
        void displayParseTree(int depth, Config *c);
};

#endif /* !PARSETREE_HPP_ */
