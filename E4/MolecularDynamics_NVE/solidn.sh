#!/bin/bash
#rm outputs/*.dat
cp outputs/config.final inputs/config.0
cp outputs/config.old inputs/old.0
cp inputs/solid.restart inputs/input.dat
./MolDyn_NVE.exe

#solid phase restarting from a previously simulated configuration