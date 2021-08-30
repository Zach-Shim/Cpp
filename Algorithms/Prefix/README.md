## Prefix
This program has the following functinoality:
1. Evaluates a given prefix expression and outputs the answer
2. Outputs a postfix expression equivalent to a given prefix expression
3. Outputs a infix expression equivalent to a given prefix expression

# Assumptions
Assumptions: 
1. Each expression is given in a txt file and is a validly formatted prefix expression where the operands consist of just one digit and the operators are either + ,- , *, / . 
2. Only valid integer are read and evaluated for simplicity. Meaning, the program can only performs integer arithmetic (answer is an int). E.g., (3+4)/2 which is /+342 in prefix notation results in the answer of 3 and is 34+2/ in postfix notation.

# Definitions
Definitions:

An infix expression is defined as the following: leftOperand operator rightOperand 
e.g., a+b (leftOp operator rightOp). 

A prefix expression is defined as the following: operator leftOperand rightOperand 
e.g., a+b becomes +ab 

A postfix expression is defined as the following: leftOperand rightOperand operator
e.g., a+b becomes ab+ 

In prefix and postfix expressions, there is no need for parentheses to change the order of operations. The precedence of the operators is built into the expression. 
Humans prefer infix expressions, but computer programs prefer prefix or postfix expressions (so the expression can be easily scanned to figure out which operation to do first).
