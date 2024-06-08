# How does our Bottom-Up parser work?

## Overview

In order to run smoothly and to divide the work between three main units represented by 3 classes. Those are namely `CFG`, `TokenParser` and `SLRParser`. Each one of these classes has its own responsibility which I will describe later in this document.

## Implementation specificities

Our initial idea was to go further than the boundaries of the subject by creating a globally working syntax analyzer that would work with any given CFG and set of token. However due to finals approaching, we decided to revise our expectations and focus on the project requirements.

Some traces of our initial remain in our code since we still belive those are good practices: as an example we tried to make sure that the main components of the syntax analyzer were wrapped up in a buparser namespace to avoid any conflicts with other libraries in case of future use.

However going back to the subject requirement meant a lesser modulable code, being traduced by a config file containing both the CFG and the tokens. This is a drawback as it means that changing the CFG forces us to change the terminal/non terminals, the cfg (logical) but also fill the lr table with the updated actions / states (very time consuming).

# Token Parser

The goal of the `TokenParser` class is to get the tokens from the file given as a parameter during the constructor phase. The default constructor does not exist, but a constructor accepting a filepath as a parameter is available.

Once the `TokenParser` is created it's only method to be run by the developer is `parse()`

## TokenParser::parse()

This is a rather classic C++ parsing method. By calling the private method `_isFileValid()` we are checking if the file provided suits the need of the program, that is existing and being a file. In case of error an error is thrown by that subsequent method while, if no error, it returns a `std::ifstream` object.

We then read each line from the `std::ifstream` using `std::getline()` and we then proceed to tokenize this line using istringstreams (`std::istringstream`) in the `_parseLine()` method. istringstreams allow easy parsing using the '>>' operator.

These tokens are then pushed in a queue of `std::string` that is returned by the method.

# CFG

The `CFG` class role is to hold the CFG and be available to provide informations about its productions. Therefore it contains two pieces of data:

- a `std::vector` containing `Production` objects, a custom class that I will discuss later on, and
- a pointer to a `Config` class, which is where my CFG (as a text) is stored and where my terminal and non terminals identifiers are stored.

The CFG will build its productions on construction by transforming the Config's rule from a `std::vector` of `std::pair` of strings to a Productions which are comprised of a lhs (typed as a `NONTERMINAL`) and rhs which is a `std::queue` of either `NONTERMINAL` or `TERMINAL` thanks to the `std::variant` template introduced in C++17. 

We used this `std::variant` a lot as it provides an easy way to have a "either A or B" type without the need to use IClasses 

## Constructor

In order to build the productions, we have an easy process:

- Iterate through every rules of the config,
- Get the next token using `_getNextToken()`, this will split the first token from the rest of the string (delimited by the first whitespace) and return it,
- Try to get this token as a `NONTERMINAL` using config's utility function `getNonTerminal`. If this is a match, then push the token to a queue of token we created, and continue in the loop
- Else, try to get it as a `TERMINAL` and do the same stuff,
- Once the rhs string of the rules is empty, create a new `Production`, with the `NONTERMINAL` lhs from the given rule and our queue as the rhs, and push it to the vector

## CFG::getProductionLHS(int index)

This method is rather simple, it allows to get the LHS of a `Production`, identified by an index.

This is particularly useful for the building of our parse tree as during reductions, we will need to keep track of the things we are replacing, and by what we are replacing them.

## CFG::getProductionRHSSize(int index)

Just as the method before, this allows to get info about a Production by providing it's index. The size of the production will help us to build the parse tree and to keep track of the state during the slr parsing algorithm, especially during reductions.

# SLRParser (& Algorithm!)

Our SLRParser is where everything is done. The parser will get the token queue from the previously mentionned `TokenParser`, and both the `CFG`'s productions and config to be able to validate the sequence and build the parse tree or refute it and print an error report.

## ParseTreeNode

The `ParseTreeNode` class is used to represent our parse tree. It is containing a `std::variant` of either a `NONTERMINAL` or a `TERMINAL` and a vector of `ParseTreeNode` which are the children of the node.

It also includes a couple of methods to add children, print the tree and pop the n last children, which will be useful for our algorithm.

As for the printing of the tree, we decided to print it recursively, with each level of depth adding a margin to the left of the node.

cf

```
CODE
  VDECL
    vtype
    id
    semi
  CODE
    FDECL
      vtype
      id
      lparen
      ARG
        Ɛ
      rparen
      lbrace
      BLOCK
        STMT
          ASSIGN
            id
            assign
            RHS
              EXPR
                EXPR
                  MOREEXPR
                    TERM
                      id
                addsub
                MOREEXPR
                  TERM
                    id
          semi
        BLOCK
          STMT
            if
            lparen
            COND
              boolstr
              MORECOND
                Ɛ
            rparen
            lbrace
            BLOCK
              STMT
                ASSIGN
                  id
                  assign
                  RHS
                    EXPR
                      MOREEXPR
                        TERM
                          id
                semi
              BLOCK
                Ɛ
            rbrace
            ELSE
              else
              lbrace
              BLOCK
                STMT
                  ASSIGN
                    id
                    assign
                    RHS
                      character
                  semi
                BLOCK
                  Ɛ
              rbrace
          BLOCK
            Ɛ
      RETURN
        return
        RHS
          EXPR
            MOREEXPR
              TERM
                id
        semi
      rbrace
    CODE
      Ɛ
```

We do believe that it could be better represented but, at the same time, there is no need to have a perfect  graphical representation of the tree as in real life applications, the tree would be passed to the semantic analyzer and not outputed to the console in any kind of way.

Do note that despite epsilons being ignored in the CFG, they are still represented in the tree as a `Ɛ` node. We made sure to display them both to show the most accurately the parse tree and to prevent any confusion when seeing a nonterminal with no children.

## Data Structure of the SLRTABLE

We decided to take time to design the SLR table in a way so that it would be effortless during the validation of the sequence.

In order to achieve that, it was fairly easy to say that we would represent the table as a `std::vector` of `std::unordered_map`, as it would allow us to access the actions and states effortlessly, by just providing the state and terminal/non-terminal as indices.

Therefore, here was another time our `std::variant` came in handy, simplifying the access to the table, for both Non-Terminals and Terminals, as we used it as the key of the map.

For the value however we needed to transmit multiple pieces of data, which were what was the actionType (to differentiate s24 and r24) and the state linked to the action. We stored those two in a `std::pair`.

Having created that `std::vector<std::unordered_map<std::variant<NONTERMINAL, TERMINAL>, std::pair<ActionType, int>>`, this allowed us to easily access the table the following way:

```cpp
TERMINAL vtype = TERMINAL::VTYPE;
int initialState = 0;
auto action = slrTable[initialState][vtype];
```

## Algorithm

Thanks to the table, we were able to implement the SLR algorithm in a very simple way. The algorithm is as follows:

- Loop while the token queue is not empty
- Get the first token of the queue (do not pop it)
- Retrieve the token from the tokenString by checking if it is a terminal or a non-terminal (or generate an UnknownToken error if neither)
- Check whether there is an associated action in the table for the current state and token, if not generate a SyntaxError,
- else, get the action-state pair from the slr table and depending on the action type, enter the corresponding case:
  - if we are shifting, create a new `ParseTreeNode` with the token and push it as the last child of the main tree, then push the state to the stateStack and pop the token from the inputQueue
  - if we are accepting, display the main tree and return
  - if we are reducing,
    - get the `NONTERMINAL A` corresponding to the left hand side of the production at index `i` (the associated state in the slr table)
    - get the size of the production's right hand side at index `i`
    - pop the last `size` children from the main tree and add them as children of a new `ParseTreeNode` with the `NONTERMINAL A` as the value
    - push the new node as the last child of the main tree
    - pop the last `size` states from the stateStack
    - perform the goto operation by accessing the slr table with the new top state and the `NONTERMINAL A` and push the corrsponding state to the stateStack

As we are deliberately adding the eof token at the end of the token queue, we are sure that the algorithm will end, either by accepting or by generating a syntax error.

## Error Report

As for the error report, I decided to create two types of errors: an unknown token error which is thrown whenever we try to get a token as a terminal or non-terminal but it is not found in the config, and a syntax error which is thrown when there is an unexpected token in the sequence. I also added in this report the position of the token in the queue, and in case of the syntax error, the expected tokens, separated by the | symbol.

The error report uses exceptions wrapped in a try catch block in the main function, and the error is caught and printed in the catch block.

`Syntax Error (token 47): Expected: rbrace but got: lbrace.`

# debug.hpp and DEBUG_MSG

The debug.hpp file is a simple file containing the DEBUG_MSG macro which is used to print debug messages in the console. As you can see in the provided binary, or by running `make`, no debug message is printed.

However if you want to see the debug messages, running `make re DEBUG_FLAG=1` will enable the preprocessor directive and the debug messages will be printed in the console.

We decided to let those messages in the code as I would keep them in a project, only for development and debugging purposes.