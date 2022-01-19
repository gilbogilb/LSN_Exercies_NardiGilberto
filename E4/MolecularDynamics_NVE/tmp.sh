#!/bin/bash
#for equilibration: output is not cancelled after the execution
bash gas0.sh
bash gasn.sh
bash gasn.sh
bash gasn.sh
bash gasn.sh
bash gasn.sh
bash gasn.sh
bash gasn.sh
bash gasn.sh
bash gasn.sh
bash gasn.sh
bash gasn.sh
bash gasn.sh
bash gasn.sh
bash gasn.sh

mv outputs/output_temp.dat outputs/equilibration/Tgas.dat
rm outputs/*.dat

bash liquid0.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh

mv outputs/output_temp.dat outputs/equilibration/Tliquid.dat
rm outputs/*.dat

bash solid0.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh

mv outputs/output_temp.dat outputs/equilibration/Tsolid.dat
rm outputs/*.dat
