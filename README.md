# ddpl_sat
# A SAT solver based on naive DPLL algorithm

## usage
./build/main.exe <testbench.cnf>

## input/output
### input 
<testbench.cnf>  *DIMACS format CNF file*

- *the header line* 'p cnf \<variables> \<clauses>' *is optional, real clauses must match the # varaibles and clauses in the header line*
- *comment line is optional, any line like *'c \<string>'* is considered*
- *only one input .cnf file at a time*
- *any other illegeal behaviour will throw an error*

### output
#### *if SAT*

SAT
1 -2 3 -4 ... (*Giving a satisfiable configuration, where negative number means the variable is FALSE, positive number means the variable is TRUE*)

#### *if UNSAT*:

UNSAT