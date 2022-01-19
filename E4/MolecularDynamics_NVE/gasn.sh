#!/bin/bash
#rm outputs/*.dat
cp outputs/config.final inputs/config.0
cp outputs/config.old inputs/old.0
cp inputs/gas.restart inputs/input.dat
./MolDyn_NVE.exe

#gas phase restarting from a previously simulated configuration