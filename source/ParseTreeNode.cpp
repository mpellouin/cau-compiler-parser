/*
** EPITECH PROJECT, 2024
** bottom-up-parser
** File description:
** ParseTree
*/

#include "ParseTreeNode.hpp"

ParseTreeNode::ParseTreeNode(std::variant<NONTERMINAL, TERMINAL> self) : self(self)
{
}

ParseTreeNode::~ParseTreeNode()
{
}

void ParseTreeNode::addChild(ParseTreeNode child)
{
    children.push_back(child);
}

void ParseTreeNode::displayParseTree(int depth, Config *c)
{
    // Increment the margin if we are going deeper in the tree
    for (int i = 0; i < depth; i++)
        std::cout << "  ";

    // Check wether self is a terminal or a non terminal
    if (std::holds_alternative<NONTERMINAL>(self))
        // Display the string representation of the non terminal
        std::cout << (c->nonTerminalsStrings[std::get<NONTERMINAL>(self)]) << std::endl;
    else
        // Display the string representation of the terminal
        std::cout << (c->terminalsStrings[std::get<TERMINAL>(self)]) << std::endl;
    
    // Iterate over children, starting by the leftmost one
    for (auto it = children.rbegin(); it != children.rend(); ++it)
        it->displayParseTree(depth + 1, c);
}

std::queue<ParseTreeNode> ParseTreeNode::popNNextNodes(int n)
{
    std::queue<ParseTreeNode> nodes;
    for (int i = 0; i < n; i++)
    {
        // Pop the rightmost child and push it in the queue
        nodes.push(children[children.size() - 1]);
        children.pop_back();
        DEBUG_MSG("Node popped, new size: " << children.size());
    }
    return nodes;
}

void ParseTreeNode::acceptTree(Config *c, NONTERMINAL cfgStartSymbol)
{
    DEBUG_MSG("ParseTreeNode::acceptTree()");
    // Display the tree starting from the root
    this->self = cfgStartSymbol;
    displayParseTree(0, c);
    DEBUG_MSG("ParseTreeNode::acceptTree() - Displayed");
}