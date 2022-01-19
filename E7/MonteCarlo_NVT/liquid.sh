#!/bin/bash

cp input/liquid.dat input/input.dat
cp input/config.fcc input/config.0
./Monte_Carlo_NVT.exe
mv output/raw.dat output/liquidraw.dat