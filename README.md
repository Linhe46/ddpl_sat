# ddpl_sat
# A SAT solver based on naive DPLL algorithm

## usage
./build/main.exe <testbench.cnf>

## input/output
***input*** <testbench.cnf>  *DIMACS format CNF file*
*the header line* 'p cnf <variables> <clauses>\n' *can't be ignored*
*only one input at a time*

***output*** :
*if SAT*
SAT
1 -2 3 -4 ... *Giving a satisfiable configuration, where negative number means the variable is FALSE, positive number means the variable is TRUE*

*if UNSAT*
UNSAT