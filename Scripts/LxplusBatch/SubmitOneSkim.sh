#!/bin/sh

echo "[Making PFGtuple] Currect directory : " 
pwd 
echo "\n" 

echo "[Making PFGtuple] Set env and move back to the batch node : " 
cd /afs/cern.ch/user/j/jaehyeok/work/HCAL/PFGtuple/CMSSW_7_4_12/src/HCALPFG 
eval `scramv1 runtime -sh`
cd -

echo "[Making PFGtuple] Currect directory : " 
pwd 
echo " " 

cp /afs/cern.ch/user/j/jaehyeok/work/HCAL/PFGtuple/CMSSW_7_4_12/src/HCALPFG/HcalTupleMaker/test/skim.C .
/afs/cern.ch/project/eos/installation/0.3.84-aquamarine/bin/eos.select cp $1/$2 .

root -b -q skim.C++\(\"$2\"\)

echo "[Making PFGtuple] Check if skimmed file has been generated : " 
ls -lrt 

SKIMPFGTUPLE=`echo $2 | sed 's/.root/_skim.root/g' `
RUN=$3

echo "[Making PFGtuple] Copying $SKIMPFGTUPLE to /eos/cms/store/user/jaehyeok/PFGtuples_run$RUN/skim/$SKIMPFGTUPLE"
xrdcp $SKIMPFGTUPLE root://eoscms.cern.ch//eos/cms/store/user/jaehyeok/PFGtuples_run$RUN/skim/$SKIMPFGTUPLE
rm -f $SKIMPFGTUPLE 
rm -f $2 
rm -f skim.C 
