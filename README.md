# ddpl_sat
# A SAT solver based on naive DPLL algorithm

## Compile
in powershell/bash with MinGW GCC/G++ Compiler

```mkdir build```  
```cd build```  
```cmake -G "MinGW Makefiles" ..```  
```make```  
```cd ..```

then the output file ```main.exe``` will be written in ```./build/```

## Usage
```./build/main.exe <cnf_file_path>```

## Input/Output
### input 
```<cnf_file_path>``` *path of a DIMACS format CNF file*

- the header line ```p cnf <variables> <clauses>``` is optional, actual variables and clauses must match the number of variables and clauses declared in the header line
- comment line is optional, any line like ```c <string>``` is considered
- only one input .cnf file at a time
- any other illegeal behaviour will throw an error ( including mismatch of variables/clauses, illegal comment/header line, empty cnf input )

### output
#### *if SAT*

SAT  
1 -2 3 -4 ... (*Giving a satisfiable configuration, where negative number means the variable is FALSE, positive number means the variable is TRUE*)

#### *if UNSAT*:

UNSAT

## Example

#### UNSAT example

input:

```plaintext
c this is a cnf file  
p cnf 3 4  
-1 -2 0  
2 3 0  
-3 0  
1 0
```

output:  

```UNSAT```

#### SAT example

input:

```plaintext
c this is a cnf file
p cnf 3 4
1 -2 0
2 3 0
-3 0
1 0
```

output:

```plaintext
SAT
1 2 -3
```