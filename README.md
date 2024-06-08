
# Bottom-Up Parser

Our submission for 김효수's Compiler class' final term project: the realization of a bottom-up parser.



## Authors

- [Maxence Pellouin (50231606)](https://www.github.com/mpellouin)
- [Nolann Sabre (50231611)](https://www.github.com/sarrooo)

## Installation

The source files can easily be compiled using [make](https://www.gnu.org/software/make/)
```
make
```

if you ever need to recompile the software from scratch, you can just use:
```
make re
```
## Documentation

The docs are available in the docs sub-directory.

Moreover we made sure to provide comments and Doxygen declaration to functions for ease of development/maintenance.


## Running Tests

30 input sequences are available in the `sample` directory and are available to run tests. Running these tests with make will perform functional tests, checking if the return value is the one expected. 

```bash
  make test
```


## Usage/Examples

To run the syntax analyzer on an input sequence, create a file containing a sequence of token and run the following command

```bash
./syntax_analyzer [path_to_input_file]
}
```

If the input is accepted, the program will return EXIT_SUCCESS (0) and display the parse tree of the input sequence.

Parse tree example:
```txt
CODE
  DECLINIT
    vtype
    id
    DECLTYPE
      VDECL
        VDECLVAL
          ASSIGN
            assign
            RHS
              literal
        semi
  CODE
    DECLINIT
      vtype
      id
      DECLTYPE
        FDECL
          lparen
          ARG
            Ɛ
          rparen
          lbrace
          BLOCK
            STMT
              id
              ASSIGN
                assign
                RHS
                  EXPR
                    EXPR
                      TERM
                        FACTOR
                          id
                    addsub
                    TERM
                      FACTOR
                        id
              semi
            BLOCK
              Ɛ
          RETURN
            return
            RHS
              EXPR
                TERM
                  FACTOR
                    id
            semi
          rbrace
    CODE
      Ɛ


```

On the other hand, if it is not, an error report will be printed alongside the program return EXIT_FAILURE (1).

Error report example:

```txt
Syntax Error (token 364): Expected: addsub | rparen but got: semi.
```
## Improvements

One of the easy way to improve this program would be by generating the LR parsing table on our own, meaning that provided a CFG, this program would work universally.

This would imply some changes however since the enums would not contain the same terminal and non-terminals anymore.

Creating a clearer view of the parse tree would globally improve this parser.