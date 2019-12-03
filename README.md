# interpreter_cpp
# Project for ECE 30862 Object Oriented Programming
## Usage: 
### To build:
```
g++ -g -o main Interpreter.cpp Data.cpp main.cpp 
```
(Maybe make a Makefile later, idk)
### To run:
```
./main [exection-flag] [input-file]
```
- "-d" : debug mode: Exection with traces
- "-n" : normal mode: Exection without traces
### Caveat:
There's a MAX_RUN constant that act as a fail safe mechanisim to avoid infinite loop, increase this value in interpreter.h and recompile to change this value
