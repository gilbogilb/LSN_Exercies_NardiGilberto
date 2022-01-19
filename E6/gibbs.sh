#!/bin/bash

rm outputs/C.dat outputs/X.dat outputs/M.dat outputs/U.dat
echo 0000 0000 0000 0001 > seed.in
cp inputs/gibbs0.dat inputs/input.dat
./Monte_Carlo_ISING_1D.exe
cp inputs/gibbsN.dat inputs/input.dat
cp seed.out seed.in
./Monte_Carlo_ISING_1D.exe
