# Eqns-solver
A program that solves linear equations.

It is required to develop a program to solve linear equations. The programs
reads first an integer n which is the number of equations.
Then the program reads n lines containing the equations.
Equation proper form​ : Any operation should first convert every equation to
the proper form. The equation proper should have the following properties
1. variables are ordered alphabetically from left to right
3x2+2x1+4x3=16
Should be
2x1+3x2+4x3=16
2. Any variable should appears only one time
4x1+3x2-2x1+4x3=16
Should be
2x1+3x2+4x3=16
3. Only one constant term should appear in the equation and it should be
on the right hand side
2x1+3x2+5+4x3-11=10
Should be
2x1+3x2+4x3=16
4. Coefficient when equals to one or -1 the digit 1 is optional
1x1+3x2-1x3=10
Can be input as be
x1+3x2-x3=10
In the program, after reading the equations the program reads one or more
commands from user and program should print the results of each operations
and read another operation till the program read the operation quit which
ends the program. ​ Any result printed should be based on the ​ proper ​ form of
equations.

Level operation Meaning
1 num_vars Print the
number of
variables
Print equation
number i (i is
integer)
Print the
column of
coefficients of
variable (x2)
equation i
column x2
2
add 1 3 Add equation 1
and equation 3
and print the
result equation
subtract 1 3 Subtract
equation 1
minus equation
3 and print the
result equation
Page 3​ of 10
Action Required from the
Program
Print the number of
variables in the equations.
Print equation of the
equation number i
Print the vector of
coefficients of the given
variable name. (x2 can be
replaced by any variable
name)
Print the result equation
from adding equation 1
and equation 3. (1 and 3
can be any integer
numbers from 1 to n).
Print the result equation
from subtracting equation
1 and equation 3. (1 and 3
can be any integer
numbers from 1 to n).substitute x2 1 3
3
D
D x1
D_value
solve
Substitutes the
variable x2 in
equation 1 by
its equation in
equation 3 and
print the result
equation
Cramer’s
Coefficient
matrix
Cramer’s
Coefficient
matrix of
variable x1
Cramer’s
coefficient
matrix
determinant
value
Print the
solution of the
equations
Remove the variable x2
from equation 1 by
substituting it with
equation 3 and print the
result equation
Prints the Cramer’s
coefficients matrix.
Prints the Cramer’s
coefficients matrix with
answer-column values in x1
columns values
Prints the value of the
determinant of the
Coefficient matrix.
Prints the value of each
variable that solves the
solution
I no solution, the program
should print “No Solution”
