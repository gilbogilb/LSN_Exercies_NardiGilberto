#!/bin/bash
#rm outputs/*.dat
cp inputs/config.fcc inputs/config.0
cp inputs/liquid.initial inputs/input.dat
./MolDyn_NVE.exe

#run 0 (generated velocities) liquid phase
