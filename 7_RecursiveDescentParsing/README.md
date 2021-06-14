# Assignmnet 7 Recursive Descent Parser

Imagine
the syntax of a programming language construct such as while-loop --

while ( condition )

begin

      statement ;

            :

end

where while,
begin, end are keywords; condition can be a single comparison
expression (such as x == 20, etc.); and statement is the
assignment to a location the result of a single arithmetic operation (eg., a
= 10 * b).

Write a recursive
descent parser for the above construct.

[Write a
context free grammar for the above construct, and ensure that the grammar meets
the criteria required for recursive descent parsing. Then write the routines
for the non-terminals.].