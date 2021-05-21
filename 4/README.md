# Assignmnet 4

Assume that in the assembly language discussed in the theory class, there is a statement -

DEFINE <name> <replace-pattern>

The meaning of the statement is that afterwards in the program wherever the pattern <name> occurs, it will be replaced by <replace-pattern>. For example if there is the statement DEFINE TRUE 1, then everywhere in the subsequent part in the program if there is the word TRUE, it will be replaced by 1. An input program may contain several such define statements. Write a program to implement this feature.