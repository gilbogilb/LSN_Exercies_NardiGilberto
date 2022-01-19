#!/bin/bash
#bash gas0.sh
#bash gasn.sh
#bash gasn.sh
#bash gasn.sh
#bash gasn.sh
#bash gasn.sh
#bash gasn.sh
#bash gasn.sh
#bash gasn.sh
#bash gasfinal.sh

#mv outputs/*.0 outputs/gas

bash liquid0.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh
bash liquidn.sh
bash liquidfinal.sh

mv outputs/*.0 outputs/liquid

bash solid0.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh
bash solidn.sh
bash solidfinal.sh

mv outputs/*.0 outputs/solid
