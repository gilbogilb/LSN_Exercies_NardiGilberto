#!/bin/bash
#rm outputs/*.dat
cp outputs/config.final inputs/config.0
cp outputs/config.old inputs/old.0
cp inputs/liquid.restart inputs/input.dat
./MolDyn_NVE.exe

#liquid phase restarting from a previously simulated configuration