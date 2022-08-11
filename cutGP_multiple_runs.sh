#Credit to Dmitris Ntounish for the majority of this file

#!/bin/bash

# Rules for seeds: 6 numbers, don't start with zero!
random_seeds=(123456 209443 495043   750831   973712  128982   284989   298484 328904 210974 324578 874192 )

#random_seeds=(344373 741332 967424 564369 989134 174207 629701 830198 514733 181397 275667 305186 400872 286937 394568 808272 437002)

#random_seeds=(787918)

seed_old=1


for element1 in "${random_seeds[@]}"
do

 seed=$element1
 echo $seed

 python run_cut.py .01 ../output_133_runs/pairs_rndm_seed_"$seed".dat ../output_cut/pairs_rndm_seed_cut_"$seed".dat

 seed_old=$seed
 



done
