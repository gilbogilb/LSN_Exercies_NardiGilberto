#!/bin/bash
bash solid.sh
mv output/*.0 output/solid
bash liquid.sh
mv output/*.0 output/liquid
bash gas.sh
mv output/*.0 output/gas

