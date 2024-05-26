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
EXPR -> EXPR addsub TERM
EXPR -> TERM
TERM -> TERM multdiv FACTOR
TERM -> FACTOR
FACTOR -> lparen EXPR rparen
FACTOR -> id
FACTOR -> num




EXPR -> EXPR addsub EXPR | EXPR multdiv EXPR
EXPR -> lparen EXPR rparen | id | num
COND -> COND comp COND | boolstr


CODE -> DECLINIT CODE 
CODE -> ''
DECLINIT -> vtype id DECLTYPE
DECLTYPE -> VDECL
DECLTYPE -> FDECL
VDECL -> VDECLVAL semi
VDECLVAL -> ASSIGN
VDECLVAL -> ''
ASSIGN -> assign RHS
RHS -> EXPR
RHS -> literal
RHS -> character
RHS -> boolstr
FDECL -> lparen ARG rparen lbrace BLOCK RETURN rbrace
ARG -> vtype id MOREARGS
ARG -> ''
MOREARGS -> comma vtype id MOREARGS
MOREARGS -> ''
BLOCK -> STMT BLOCK
BLOCK -> ''
STMT -> vtype id VDECL
STMT -> id ASSIGN semi
STMT -> if lparen COND rparen lbrace BLOCK rbrace ELSE
STMT -> while lparen COND rparen lbrace BLOCK rbrace
ELSE -> else lbrace BLOCK rbrace
ELSE -> ''
RETURN -> return RHS semi
COND -> boolstr MORECOND
MORECOND -> comp boolstr MORECOND
MORECOND -> ''
EXPR -> EXPR addsub TERM
EXPR -> TERM
TERM -> TERM multdiv FACTOR
TERM -> FACTOR
FACTOR -> lparen EXPR rparen
FACTOR -> id
FACTOR -> num