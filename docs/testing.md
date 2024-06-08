# Functional Testing

For this project, we mainly used functional testing as we wanted to test the software as a whole. We generated some input sequences from the grammar and tested the software on them. For fair testing, we also added some invalid input sequences to make sure the software was able to detect them.

All of the samples are available in the `sample` directory. The software is able to run all of them and return the expected value, which is `EXIT_SUCCESS` for valid input sequences and `EXIT_FAILURE` for invalid ones.

For automation, we created the `functional_test.sh` script that runs syntax_analyzer on all the samples and checks if the return value is the one we expected.

To run the functional tests, you can use the following command:

```bash
./functional_test.sh
```

This should recompile the binary and run the tests. If everything is working as expected, you should see the following output:

```txt
❯ ./functional_tests.sh                                                                                          ─╯
Removing object files.
Removing binary file.
+---------------------------------------------------------+
|█▀ █▄█ █▄░█ ▀█▀ ▄▀█ ▀▄▀   ▄▀█ █▄░█ ▄▀█ █░░ █▄█ ▀█ █▀  █▀█|
|▄█ ░█░ █░▀█ ░█░ █▀█ █░█   █▀█ █░▀█ █▀█ █▄▄ ░█░ █▄ ██▄ █▀▄|
+---------------------------------------------------------+
Compiling [build/Production.o]
Compiling [build/main.o]
Compiling [build/TokenParser.o]
Compiling [build/CFG.o]
Compiling [build/SLRParser.o]
Compiling [build/config.o]
Compiling [build/ParseTreeNode.o]
syntax_analyzer linking success
Makefile compilation successful
sample/empty.txt returned 0, expected 0: testing succeeded
sample/input10.txt returned 0, expected 0: testing succeeded
sample/input11.txt returned 0, expected 0: testing succeeded
sample/input12.txt returned 0, expected 0: testing succeeded
sample/input13.txt returned 0, expected 0: testing succeeded
sample/input1.txt returned 0, expected 0: testing succeeded
sample/input2.txt returned 0, expected 0: testing succeeded
sample/input3.txt returned 0, expected 0: testing succeeded
sample/input4.txt returned 0, expected 0: testing succeeded
sample/input5.txt returned 0, expected 0: testing succeeded
sample/input6.txt returned 0, expected 0: testing succeeded
sample/input7.txt returned 0, expected 0: testing succeeded
sample/input8.txt returned 0, expected 0: testing succeeded
sample/input9.txt returned 0, expected 0: testing succeeded
sample/long/l10.txt returned 0, expected 0: testing succeeded
sample/long/l1.txt returned 0, expected 0: testing succeeded
sample/long/l2.txt returned 0, expected 0: testing succeeded
sample/long/l3.txt returned 0, expected 0: testing succeeded
sample/long/l4.txt returned 0, expected 0: testing succeeded
sample/long/l5.txt returned 0, expected 0: testing succeeded
sample/long/l6.txt returned 0, expected 0: testing succeeded
sample/long/l7.txt returned 0, expected 0: testing succeeded
sample/long/l8.txt returned 0, expected 0: testing succeeded
sample/long/l9.txt returned 0, expected 0: testing succeeded
sample/fail/input_stream.txt returned 1, expected 1: testing succeeded
sample/fail/newline_input_stream.txt returned 1, expected 1: testing succeeded
sample/fail/unknown_token_and_mismatched.txt returned 1, expected 1: testing succeeded
sample/fail/unknown_token.txt returned 1, expected 1: testing succeeded
sample/fail/unmatched_paren.txt returned 1, expected 1: testing succeeded
sample/fail/unmatched_then_unknown.txt returned 1, expected 1: testing succeeded
30 files succesfully tested
```