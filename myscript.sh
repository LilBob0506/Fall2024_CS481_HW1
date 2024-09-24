#!/bin/bash
cd Fall2024_CS481_HW1
module load intel
icx -O -o gameoflife gameoflife1.c
./gameoflife <size> <max number of generations> 
