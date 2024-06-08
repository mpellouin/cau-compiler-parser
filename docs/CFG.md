# CFG

## Provided CFG

```
CODE → VDECL CODE | FDECL CODE | ε
VDECL → vtype id semi | vtype ASSIGN semi
ASSIGN → id assign RHS
RHS → EXPR | literal | character | boolstr
EXPR → EXPR addsub EXPR | EXPR multdiv EXPR
EXPR → lparen EXPR rparen | id | num
FDECL → vtype id lparen ARG rparen lbrace BLOCK RETURN rbrace
ARG → vtype id MOREARGS | ε
MOREARGS → comma vtype id MOREARGS | ε
BLOCK → STMT BLOCK | ε
STMT → VDECL | ASSIGN semi
STMT → if lparen COND rparen lbrace BLOCK rbrace ELSE
STMT → while lparen COND rparen lbrace BLOCK rbrace
COND → COND comp COND | boolstr
ELSE → else lbrace BLOCK rbrace | ε
RETURN → return RHS semi
```

## SLR Grammar

Due to the provided LR table builder specifications, the CFG needs to be modified to a SLR grammar with some modifications:
- ε becomes ''
- since the | operator is counted as a terminal, change to multiple rules

With those modifications, the CFG becomes:

```
CODE -> VDECL CODE
CODE -> FDECL CODE
CODE -> ''
VDECL -> vtype id semi
VDECL -> vtype ASSIGN semi
ASSIGN -> id assign RHS
RHS -> EXPR
RHS -> literal
RHS -> character
RHS -> boolstr
EXPR -> EXPR addsub EXPR
EXPR -> EXPR multdiv EXPR
EXPR -> lparen EXPR rparen
EXPR -> id
EXPR -> num
FDECL -> vtype id lparen ARG rparen lbrace BLOCK RETURN rbrace
ARG -> vtype id MOREARGS
ARG -> ''
MOREARGS -> comma vtype id MOREARGS
MOREARGS -> ''
BLOCK -> STMT BLOCK
BLOCK -> ''
STMT -> VDECL
STMT -> ASSIGN semi
STMT -> if lparen COND rparen lbrace BLOCK rbrace ELSE
STMT -> while lparen COND rparen lbrace BLOCK rbrace
COND -> COND comp COND
COND -> boolstr
ELSE -> else lbrace BLOCK rbrace
ELSE -> ''
RETURN -> return RHS semi
```

However for multiple reasons, starting from the ambiguity, the CFG needs to be updated so that our algorithm can be performed smoothly.


## Updated SLR Grammar and CFG

Here is how my research on the CFG changes went:

Firstly, I wanted to check if the classic dangling else problem existed in this CFG. However since the corresponding rule (STMT -> if lparen COND rparen lbrace BLOCK rbrace ELSE) contains braces around the if statement, there is no ambiguity form such as `if a then if b then c else d`.

The second thing that I saw were the `A -> A SOMETHING A | SOMETHING_ELSE` rules. Those need to be changed
because you can get different parse trees for a same input. Let's take the example of `boolstr comp boolstr comp boolstr`. The parse tree tree can either be:

```
    COND --------
      |  \       \
    COND  comp COND
    / |  \         \
COND comp COND   boolstr
  |         \
boolstr     boolstr
``` 

or

```
    COND -------
      |  \      \
    COND comp COND----
    /         |  \    \
boolstr     COND comp COND
            /          \
        boolstr     boolstr
```

To avoid this, we can just rewrite these rules with other rules. A good example is the MOREARGS rule already
present in the CFG. If it had not been created, ARG would look like `ARG -> ARG comma ARG`.

Based on this, I decided to change the COND rule by creating a `MORECOND` rule.

```
COND -> COND comp COND
COND -> boolstr

      |
      v

COND -> boolstr MORECOND
MORECOND -> comp boolstr MORECOND
MORECOND -> ''
```

The same goes for the EXPR rule which I divided into two categories, the expressions and the terms. 
The expression will be `EXPR -> EXPR addsub EXPR` and `EXPR -> EXPR multdiv EXPR` while the terms are `
EXPR -> lparen EXPR rparen;
EXPR -> id;
EXPR -> num`.

```
EXPR -> EXPR addsub EXPR
EXPR -> EXPR multdiv EXPR

        |
        v

EXPR -> EXPR addsub MOREEXPR
EXPR -> MOREEXPR
MOREEXPR -> MOREEXPR multdiv TERM
MOREEXPR -> TERM
TERM -> lparen EXPR rparen
TERM -> id
TERM -> num
```

The final tweak I made was to create the dummy rule. I decided to name it `PROGRAM`.

Here is the final CFG:

```
PROGRAM -> CODE
CODE -> VDECL CODE
CODE -> FDECL CODE
CODE -> ''
VDECL -> vtype id semi
VDECL -> vtype ASSIGN semi
ASSIGN -> id assign RHS
RHS -> EXPR
RHS -> literal
RHS -> character
RHS -> boolstr
FDECL -> vtype id lparen ARG rparen lbrace BLOCK RETURN rbrace
ARG -> vtype id MOREARGS
ARG -> ''
MOREARGS -> comma vtype id MOREARGS
MOREARGS -> ''
BLOCK -> STMT BLOCK
BLOCK -> ''
STMT -> VDECL
STMT -> ASSIGN semi
STMT -> if lparen COND rparen lbrace BLOCK rbrace ELSE
STMT -> while lparen COND rparen lbrace BLOCK rbrace
ELSE -> else lbrace BLOCK rbrace
ELSE -> ''
RETURN -> return RHS semi
COND -> boolstr MORECOND
MORECOND -> comp boolstr MORECOND
MORECOND -> ''
EXPR -> EXPR addsub MOREEXPR
EXPR -> MOREEXPR
MOREEXPR -> MOREEXPR multdiv TERM
MOREEXPR -> TERM
TERM -> lparen EXPR rparen
TERM -> id
TERM -> num
```


## LR Table

From this CFG, we built the next non-very readable table, if you wish to see it as a screenshot, you can find it in `docs/LR_table.png`:

| State | vtype | id  | semi | assign | literal | character | boolstr | lparen | rparen | lbrace | rbrace | comma | if  | while | else | return | comp | addsub | multdiv | num | $ | PROGRAM | CODE | VDECL | ASSIGN | RHS | FDECL | ARG | MOREARGS | BLOCK | STMT | ELSE | RETURN | COND | MORECOND | EXPR | MOREEXPR | TERM |
| ----- |  ----- | --- | ---- | ------ | ------- | --------- | ------- | ------ | ------ | ------ | ------ | ----- | --- | ----- | ---- | ------ | ---- | ------ | ------- | --- | - | ------- | ---- | ----- | ------ | --- | ----- | --- | -------- | ----- | ---- | ---- | ------ | ---- | -------- | ---- | -------- | ---- |
| 0     | s4     |      |       |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        | r3      |     | 1 | 2       |      |       | 3      |     |       |     |          |       |      |      |        |      |          |      |
| 1     |        |      |       |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        | acc     |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 2     | s4     |      |       |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        | r3      |     | 5 | 2       |      |       | 3      |     |       |     |          |       |      |      |        |      |          |      |
| 3     | s4     |      |       |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        | r3      |     | 6 | 2       |      |       | 3      |     |       |     |          |       |      |      |        |      |          |      |
| 4     |        | s7   |       |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         | 8    |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 5     |        |      |       |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        | r1      |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 6     |        |      |       |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        | r2      |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 7     |        |      | s9    | s11 |      |        |         | s10       |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 8     |        |      | s12   |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 9     | r4     | r4   |       |     |      |        |         |           |         |        | r4     |        | r4     | r4    |     | r4    |      |        |      |        | r4      |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 10    | s14    |      |       |     |      |        |         |           | r13     |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        | 13  |       |     |          |       |      |      |        |      |          |      |
| 11    |        | s23  |       |     | s17  | s18    | s19     | s22       |         |        |        |        |        |       |     |       |      |        |      | s24    |         |     |   |         |      | 15    |        |     |       |     |          |       |      |      |        | 16   | 20       | 21   |
| 12    | r5     | r5   |       |     |      |        |         |           |         |        | r5     |        | r5     | r5    |     | r5    |      |        |      |        | r5      |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 13    |        |      |       |     |      |        |         |           | s25     |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 14    |        | s26  |       |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 15    |        |      | r6    |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 16    |        |      | r7    |     |      |        |         |           |         |        |        |        |        |       |     |       |      | s27    |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 17    |        |      | r8    |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 18    |        |      | r9    |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 19    |        |      | r10   |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 20    |        |      | r29   |     |      |        |         |           | r29     |        |        |        |        |       |     |       |      | r29    | s28  |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 21    |        |      | r31   |     |      |        |         |           | r31     |        |        |        |        |       |     |       |      | r31    | r31  |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 22    |        | s23  |       |     |      |        |         | s22       |         |        |        |        |        |       |     |       |      |        |      | s24    |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        | 29   | 20       | 21   |
| 23    |        |      | r33   |     |      |        |         |           | r33     |        |        |        |        |       |     |       |      | r33    | r33  |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 24    |        |      | r34   |     |      |        |         |           | r34     |        |        |        |        |       |     |       |      | r34    | r34  |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 25    |        |      |       |     |      |        |         |           |         | s30    |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 26    |        |      |       |     |      |        |         |           | r15     |        |        | s32    |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     | 31    |     |          |       |      |      |        |      |          |      |
| 27    |        | s23  |       |     |      |        |         | s22       |         |        |        |        |        |       |     |       |      |        |      | s24    |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      | 33       | 21   |
| 28    |        | s23  |       |     |      |        |         | s22       |         |        |        |        |        |       |     |       |      |        |      | s24    |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          | 34   |
| 29    |        |      |       |     |      |        |         |           | s35     |        |        |        |        |       |     |       |      | s27    |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 30    | s42    | s43  |       |     |      |        |         |           |         |        | r17    |        | s40    | s41   |     | r17   |      |        |      |        |         |     |   | 38      | 39   |       |        |     |       | 36  | 37       |       |      |      |        |      |          |      |
| 31    |        |      |       |     |      |        |         |           | r12     |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 32    | s44    |      |       |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 33    |        |      | r28   |     |      |        |         |           | r28     |        |        |        |        |       |     |       |      | r28    | s28  |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 34    |        |      | r30   |     |      |        |         |           | r30     |        |        |        |        |       |     |       |      | r30    | r30  |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 35    |        |      | r32   |     |      |        |         |           | r32     |        |        |        |        |       |     |       |      | r32    | r32  |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 36    |        |      |       |     |      |        |         |           |         |        |        |        |        |       |     | s46   |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       | 45   |      |        |      |          |      |
| 37    | s42    | s43  |       |     |      |        |         |           |         |        | r17    |        | s40    | s41   |     | r17   |      |        |      |        |         |     |   | 38      | 39   |       |        |     |       | 47  | 37       |       |      |      |        |      |          |      |
| 38    | r18    | r18  |       |     |      |        |         |           |         |        | r18    |        | r18    | r18   |     | r18   |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 39    |        |      | s48   |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 40    |        |      |       |     |      |        |         | s49       |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 41    |        |      |       |     |      |        |         | s50       |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 42    |        | s51  |       |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         | 8    |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 43    |        |      |       | s11 |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 44    |        | s52  |       |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 45    |        |      |       |     |      |        |         |           |         |        | s53    |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 46    |        | s23  |       |     | s17  | s18    | s19     | s22       |         |        |        |        |        |       |     |       |      |        |      | s24    |         |     |   |         |      | 54    |        |     |       |     |          |       |      |      |        | 16   | 20       | 21   |
| 47    |        |      |       |     |      |        |         |           |         |        | r16    |        |        |       |     | r16   |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 48    | r19    | r19  |       |     |      |        |         |           |         |        | r19    |        | r19    | r19   |     | r19   |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 49    |        |      |       |     |      |        | s56     |           |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      | 55   |        |      |          |      |
| 50    |        |      |       |     |      |        | s56     |           |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      | 57   |        |      |          |      |
| 51    |        |      | s9    | s11 |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 52    |        |      |       |     |      |        |         |           | r15     |        |        | s32    |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     | 58    |     |          |       |      |      |        |      |          |      |
| 53    | r11    |      |       |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        | r11     |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 54    |        |      | s59   |     |      |        |         |           |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 55    |        |      |       |     |      |        |         |           | s60     |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 56    |        |      |       |     |      |        |         |           | r27     |        |        |        |        |       |     |       | s62  |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      | 61     |      |          |      |
| 57    |        |      |       |     |      |        |         |           | s63     |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 58    |        |      |       |     |      |        |         |           | r14     |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 59    |        |      |       |     |      |        |         |           |         |        | r24    |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 60    |        |      |       |     |      |        |         |           |         | s64    |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 61    |        |      |       |     |      |        |         |           | r25     |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 62    |        |      |       |     |      |        | s65     |           |         |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 63    |        |      |       |     |      |        |         |           |         | s66    |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 64    | s42    | s43  |       |     |      |        |         |           |         |        | r17    |        | s40    | s41   |     | r17   |      |        |      |        |         |     |   | 38      | 39   |       |        |     |       | 67  | 37       |       |      |      |        |      |          |      |
| 65    |        |      |       |     |      |        |         |           | r27     |        |        |        |        |       |     |       | s62  |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      | 68     |      |          |      |
| 66    | s42    | s43  |       |     |      |        |         |           |         |        | r17    |        | s40    | s41   |     | r17   |      |        |      |        |         |     |   | 38      | 39   |       |        |     |       | 69  | 37       |       |      |      |        |      |          |      |
| 67    |        |      |       |     |      |        |         |           |         |        | s70    |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 68    |        |      |       |     |      |        |         |           | r26     |        |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 69    |        |      |       |     |      |        |         |           |         |        | s71    |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 70    | r23    | r23  |       |     |      |        |         |           |         |        | r23    |        | r23    | r23   | s73 | r23   |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          | 72    |      |      |        |      |          |      |
| 71    | r21    | r21  |       |     |      |        |         |           |         |        | r21    |        | r21    | r21   |     | r21   |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 72    | r20    | r20  |       |     |      |        |         |           |         |        | r20    |        | r20    | r20   |     | r20   |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 73    |        |      |       |     |      |        |         |           |         | s74    |        |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 74    | s42    | s43  |       |     |      |        |         |           |         |        | r17    |        | s40    | s41   |     | r17   |      |        |      |        |         |     |   | 38      | 39   |       |        |     |       | 75  | 37       |       |      |      |        |      |          |      |
| 75    |        |      |       |     |      |        |         |           |         |        | s76    |        |        |       |     |       |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |
| 76    | r22    | r22  |       |     |      |        |         |           |         |        | r22    |        | r22    | r22   |     | r22   |      |        |      |        |         |     |   |         |      |       |        |     |       |     |          |       |      |      |        |      |          |      |