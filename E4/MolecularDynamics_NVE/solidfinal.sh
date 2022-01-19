#!/bin/bash
rm outputs/*.dat
cp outputs/config.final inputs/config.0
cp outputs/config.old inputs/old.0
cp inputs/solid.final inputs/input.dat
./MolDyn_NVE.exe