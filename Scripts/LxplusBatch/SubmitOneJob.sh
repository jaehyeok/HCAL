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

cmsRun /afs/cern.ch/user/j/jaehyeok/work/HCAL/PFGtuple/CMSSW_7_4_12/src/HCALPFG/HcalTupleMaker/test/analysis_Collision_cfg.py inputFiles=root://eoscms/$1 processEvents=$2

echo "[Making PFGtuple] Check if outpufFile.root has been generated : " 
ls -lrt 

PFGTUPLE=`echo $1 | sed 's/\//_/g' `
PFGTUPLE=`echo $PFGTUPLE | sed 's/_eos/PFGtuple_eos/g' `
RUN=$3

echo "[Making PFGtuple] Changing PFGtuple name from outputFile.root to $PFGTUPLE"
mv outputFile.root $PFGTUPLE 


echo "[Making PFGtuple] Check if outpufFile.root has been successfully converted to $PFGTUPLE : " 
ls -lrt 

echo "[Making PFGtuple] Copying $PFGTUPLE to /eos/cms/store/user/jaehyeok/PFGtuples_run$RUN/$PFGTUPLE"
xrdcp $PFGTUPLE root://eoscms.cern.ch//eos/cms/store/user/jaehyeok/PFGtuples_run$RUN/$PFGTUPLE
rm -f $PFGTUPLE 
