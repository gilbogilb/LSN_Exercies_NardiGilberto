#!/bin/bash
rm outputs/*.0
cp outputs/config.final inputs/config.0
cp outputs/config.old inputs/old.0
cp inputs/liquid.final inputs/input.dat
./MolDyn_NVE.exe