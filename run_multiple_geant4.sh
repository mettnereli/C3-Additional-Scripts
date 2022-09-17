#!/bin/bash



echo "Arguments are: $1 $2"
ARGONE="pairs_230385_${1}.dat"
source /cvmfs/sft.cern.ch/lcg/views/LCG_101/x86_64-centos7-gcc11-opt/setup.sh
xrdcp root://cmseos.fnal.gov//store/user/emettner/C3/geant4/input/DD4hep.tar.gz .
tar -xf DD4hep.tar.gz
rm DD4hep.tar.gz
cd DD4hep
export DD4hepExamplesINSTALL=$(pwd)
cd ..
xrdcp root://cmseos.fnal.gov//store/user/emettner/C3/geant4/input/lcgeo.tar.gz .
tar -xf lcgeo.tar.gz
rm lcgeo.tar.gz
cd lcgeo
mkdir build install && cd build
cmake -DCMAKE_CXX_STANDARD="17" -DCMAKE_INSTALL_PREFIX=../install ..
make -j $(nproc) install
cd ../..
FILEDIRECTORY="root://cmseos.fnal.gov//store/user/emettner/C3/geant4/input/$ARGONE"
OUTDIRECTORY="root://cmseos.fnal.gov//store/user/emettner/C3/geant4/output/pTTests/${1}"
xrdcp root://cmseos.fnal.gov//store/user/emettner/C3/geant4/input/C3_G4guineapig.py .
xrdcp root://cmseos.fnal.gov//store/user/emettner/C3/geant4/input/CLICSid.py .
xrdcp root://cmseos.fnal.gov//store/user/emettner/C3/geant4/input/env.sh .
xrdcp $FILEDIRECTORY .
source env.sh
cut_old=0
sed -i "s@fname = './pairs_230385_0.dat'@fname = './pairs_230385_${1}.dat'@g" C3_G4guineapig.py
#Now that everything is set up, time to run different seeds
seed_old=1
seed=$2
echo $seed
sed -i "s/setupRandom('R1', seed=$seed_old/setupRandom('R1', seed=$seed/g" C3_G4guineapig.py 
sed -i "s/geant4.setupROOTOutput('ROOTOutput', 'C3SiD_$seed_old')/geant4.setupROOTOutput('ROOTOutput', 'C3SiD_$seed')/g" C3_G4guineapig.py
python C3_G4guineapig.py batch
xrdcp -f C3SiD_${seed}.root $OUTDIRECTORY/C3Sid_${seed}_${1}.root
rm C3SiD_${seed}.root
#sed -i "s/fname =$seed_old/fname = $seed/g" C3_G4guineapig.py
rm CLICSid.py
rm env.sh
rm C3_G4guineapig.py 
echo "DONE!"
exit $exitcode
